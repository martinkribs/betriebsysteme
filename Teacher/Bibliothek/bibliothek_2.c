#include "sync.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>

#define ANZAHL_PRIESTER 2
#define AMENOPHIS 0
#define BEMENOPHIS 1

#define PRIESTERNAME(x) ((x) == AMENOPHIS ? "Amenophis" : "Bemenophis")

/* Funktionsdeklarationen */
void programmabbruch(int);
int erzeugePriester(int);
void kind(int);
void vater(void);
void heimweg(int priester);

int semid_schriftrollen = 0, semid_priester = 0, vaterpid = 0;
int priester_pids[ANZAHL_PRIESTER];
enum STATUS {LESEN, EINTRETEN, WARTEN};

void deadlock_observer(void);

int main(void)
{
	int i = 0;

	/* Signalhandler registrieren */
	struct sigaction aktion;
	aktion.sa_flags = 0;
	aktion.sa_handler = &programmabbruch;
	sigemptyset(&aktion.sa_mask);

	if (sigaction(SIGINT, &aktion, NULL) == -1) {
		perror("set actionhandler");
		exit(EXIT_FAILURE);
	}
 
	/* Die Kindprozesse erben den Signalhandler, da wir diesen bereits vor
	 * dem fork registrieren.  Damit der Vater (Bibliothek) weiss, dass er
	 * der Vater ist, speichern wir an dieser Stelle seine PID.
	 */
	vaterpid = getpid();


	/* Erzeugen der Semaphormengen für die Priester und die Schriftrollen. */
	semid_schriftrollen = erzeuge_sem(1, 0xcaee);
	semid_priester = erzeuge_sem(2, 0xcaffee);
	init_sem(semid_schriftrollen, 1, 2);
	init_sem(semid_priester, 2, 0);


	for (i = 0; i < ANZAHL_PRIESTER; i++) {
		priester_pids[i] = erzeugePriester(i);
		sleep(1);
	}

	vater();
	return 0;
}

void vater(void)
{
	while(1) {	
	printf("\033[0;32mThutmosis (%d): Ich bin Thutmosis, Herrscher ueber das "
	       "Aegyptische Reich, Verwalter der Bibliothek von Hermopolis!\033[0m\n",
	       (int) getpid());

		
	deadlock_observer();

	}
	
}

void kind(int priester)
{
	/* Bemenophis trifft spaeter ein. */
	if (priester == BEMENOPHIS) {
		sleep(4);
	}
	while(1) {
		printf("%s (%d): Ich bin %s, auf geht's zur Bibliothek nach Hermopolis.\n", 
		       PRIESTERNAME(priester), (int) getpid(), PRIESTERNAME(priester));


	
		/* Wartezeiten:
		 * Lesen der ersten Schriftrolle: sleep(3)
		 * Lesen der zweiten Schriftrolle: sleep(5)
		 * 
		 * D.h., ein Priester liest in der ersten genommenen Schriftrolle
		 * kuerzer als in der zweiten.
		 */

		
		/* Priester benutzt erste Schriftrolle, also ausfuehren von p() auf Semaphor der Schriftrollen */
		p(semid_schriftrollen, 0);
		/* Priester wechselt in den nächsten Status, also ausfuehren von v() auf den Semaphor des Priesters */
		v(semid_priester, priester);
		printf("%s (%d): Ich bin %s, Ich lese nun die erste Schriftrolle.\n", 
		       PRIESTERNAME(priester), (int) getpid(), PRIESTERNAME(priester));
		sleep(3);
	
		/* Priester benutzt beide Schriftrolle, also erneutes ausfuehren von p() auf Semaphor der Schriftrollen */
		p(semid_schriftrollen, 0);
		/* Priester wechselt in den nächsten Status, also ausfuehren von v() auf den Semaphor des Priesters */
		v(semid_priester, priester);
		printf("%s (%d): Ich bin %s, Ich lese nun beide Schriftrollen.\n", 
		       PRIESTERNAME(priester), (int) getpid(), PRIESTERNAME(priester));
		sleep(5);
			
		printf("%s (%d): Ich bin %s, Ich gebe nun beide Schriftrollen zurueck.\n", 
		       PRIESTERNAME(priester), (int) getpid(), PRIESTERNAME(priester));
		/* priester hat beide Schriftrollen freigegeben, also Setzen des Werts des Semaphor der Schriftrollen auf 2 */
		set_sem(semid_schriftrollen, 0, 2);
	
	
	
		/* Hier wird die Zeit des Heimwegs der Priester berechnet. Veraendert
		 * den Inhalt der Funktion besser nicht, sonst bekommt ihr keine
		 * Deadlocks mehr, oder muesst sehr lange darauf warten.
		 */

		/* Priester hat nun wieder den Ausgangsstatus "Eintreten", bzw. 0. */
		set_sem(semid_priester, priester, 0);
		heimweg(priester);
		}
}

void heimweg(int priester)
{
	static int j = 0;

	/* Amenophis kommt nach 8 Zeiteinheiten wieder, Bemenophis in immer
	 * schnelleren Abstaenden.  Dadurch wird der Deadlock provoziert.
	 */
	if (priester == AMENOPHIS) {
		printf("%s (%d): Das reicht fuers erste. In 8 Tagen komme ich wieder!\n",
		       PRIESTERNAME(priester), (int) getpid());
		sleep(8);
	} else {
		if ((8 - j) < 0) {
			j = 0;
		}
		printf("%s (%d): Das reicht fuer's erste. In %d Tagen komme ich wieder\n",
		       PRIESTERNAME(priester), (int) getpid(), 8 - j);
		sleep(8 - j);
		j += 6;
	}
}

void programmabbruch(int sig)
{
	/* Pruefen, ob wir im Vaterprozess sind */
	if (getpid() == vaterpid) {
		int i;

		/* Terminierung der Priester und entfernen der Zombies */
		for (i = 0; i < ANZAHL_PRIESTER; i++) {
			kill(priester_pids[i], SIGTERM);
			pid_t res;
			res = waitpid(priester_pids[i], NULL, WNOHANG);
			if(res == -1) {
				if(errno != ECHILD) {
					perror("waitpid");
					exit(EXIT_FAILURE);
					}
				}
			}
		/* Freigabe der Semaphormengen für Priester und Schriftrollen */
		semctl(semid_priester, 0, IPC_RMID);
		semctl(semid_schriftrollen, 0, IPC_RMID);
		/* Beenden des Vaterprocesses */
		exit(0);
		

	}
}

int erzeugePriester(int priester)
{
	int pid = fork();
	if (pid == -1) {
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0) {
		kind(priester);
		return 0;
	} else {
		return pid;
	}
}

void deadlock_observer(void) {
	if (getpid() == vaterpid) {
		int array[2];
		int i;

		/* Aufrufen des Status fuer die Beiden Priester und Speichern in array */
		for(i = 0; i < 2; i++) {
			array[i] = semctl(semid_priester, i, GETVAL);
			}
		/* Ueberpruefung, ob beide Priester gleichzeitig im Status "Warten", also 1, sind. */
		if((array[0] == 1) & (array[1] == 1)) {
			printf("\033[0;32mBeide Priester warten und streiten sich bald um die zweite Schriftrolle.\033[0m\n");
			}
		else printf("\033[0;32mEs gibt kein Problem in meiner Bibliotheek.\033[0m\n");

		sleep(12);

		}
	}
