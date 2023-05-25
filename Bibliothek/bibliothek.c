#include "sync.h"
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

#define ANZAHL_PRIESTER 2
#define AMENOPHIS 0
#define BEMENOPHIS 1
#define KEY_PRIEST 0xfade
#define KEY_BOOKS 0xcafe

#define PRIESTERNAME(x) ((x) == AMENOPHIS ? "Amenophis" : "Bemenophis")

/* Funktionsdeklarationen */
void programmabbruch(int);
int erzeugePriester(int);
void kind(int);
void vater(void);
void heimweg(int priester);

int semid_schriftrollen = 0, semid_priester = 0, vaterpid = 0;
int priester_pids[ANZAHL_PRIESTER];
enum STATUS
{
	LESEN,
	EINTRETEN,
	WARTEN
};
enum BUCH
{
	AUSGELIEHEN,
	VERFUEGBAR
};

int main(void)
{
	int i = 0;

	/* Signalhandler registrieren */
	struct sigaction signal_action;
	signal_action.sa_flags = 0;
	signal_action.sa_handler = &programmabbruch;
	sigemptyset(&signal_action.sa_mask);

	if (sigaction(SIGINT, &signal_action, NULL) == -1)
	{
		perror("set actionhandler");
		exit(EXIT_FAILURE);
	}

	/* Die Kindprozesse erben den Signalhandler, da wir diesen bereits vor
	 * dem fork registrieren.  Damit der Vater (Bibliothek) weiss, dass er
	 * der Vater ist, speichern wir an dieser Stelle seine PID.
	 */
	vaterpid = getpid();

	/* HIER MUSS EUER CODE EINGEFUEGT WERDEN */
	semid_priester = erzeuge_sem(ANZAHL_PRIESTER, KEY_PRIEST);
	init_sem(semid_priester, 3, EINTRETEN);
	
	semid_schriftrollen = erzeuge_sem(2, KEY_BOOKS);
	init_sem(semid_schriftrollen, 2, VERFUEGBAR);

	for (i = 0; i < ANZAHL_PRIESTER; i++)
	{
		priester_pids[i] = erzeugePriester(i);
		sleep(1);
	}

	vater();
	return 0;
}

void vater(void)
{
	printf("\033[0;32mThutmosis (%d): Ich bin Thutmosis, Herrscher ueber das "
		   "Aegyptische Reich, Verwalter der Bibliothek von Hermopolis!\033[0m\n",
		   getpid());

	/* HIER MUSS EUER CODE EINGEFUEGT WERDEN */
}

void kind(int priester)
{
	/* Bemenophis trifft spaeter ein. */
	if (priester == BEMENOPHIS)
	{
		sleep(4);
	}

	printf("%s (%d): Ich bin %s, auf geht's zur Bibliothek nach Hermopolis.\n",
		   PRIESTERNAME(priester), getpid(), PRIESTERNAME(priester));

	/* HIER MUSS EUER CODE EINGEFUEGT WERDEN */
	p(semid_priester, priester);

	/* Wartezeiten:
	 * Lesen der ersten Schriftrolle: sleep(3)
	 * Lesen der zweiten Schriftrolle: sleep(5)
	 *
	 * D.h., ein Priester liest in der ersten genommenen Schriftrolle
	 * kuerzer als in der zweiten.
	 */

	/* HIER MUSS EUER CODE EINGEFUEGT WERDEN */
	p(semid_schriftrollen, 0);
	printf("%s (%d): Ich bin %s, und lese Schriftrolle 1.\n",
		   PRIESTERNAME(priester), getpid(), PRIESTERNAME(priester));
	sleep(3);
	v(semid_schriftrollen, 0);
	p(semid_schriftrollen, 1);
	printf("%s (%d): Ich bin %s, und lese Schriftrolle 2.\n",
		   PRIESTERNAME(priester), getpid(), PRIESTERNAME(priester));
	sleep(5);
	v(semid_schriftrollen, 1);

	/* Hier wird die Zeit des Heimwegs der Priester berechnet. Veraendert
	 * den Inhalt der Funktion besser nicht, sonst bekommt ihr keine
	 * Deadlocks mehr, oder muesst sehr lange darauf warten.
	 */
	heimweg(priester);

	/* HIER MUSS EUER CODE EINGEFUEGT WERDEN */
	v(semid_priester, priester);
}

void heimweg(int priester)
{
	static int j = 0;

	/* Amenophis kommt nach 8 Zeiteinheiten wieder, Bemenophis in immer
	 * schnelleren Abstaenden.  Dadurch wird der Deadlock provoziert.
	 */
	if (priester == AMENOPHIS)
	{
		printf("%s (%d): Das reicht fuers erste. In 8 Tagen komme ich wieder!\n",
			   PRIESTERNAME(priester), getpid());
		sleep(8);
	}
	else
	{
		if ((8 - j) < 0)
		{
			j = 0;
		}
		printf("%s (%d): Das reicht fuer's erste. In %d Tagen komme ich wieder\n",
			   PRIESTERNAME(priester), getpid(), 8 - j);
		sleep(8 - j);
		j += 6;
	}
}

void programmabbruch(int sig)
{
	/* Pruefen, ob wir im Vaterprozess sind */
	if (getpid() == vaterpid)
	{

		/* HIER MUSS EUER CODE EINGEFUEGT WERDEN */
	}
}

int erzeugePriester(int priester)
{
	int pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		kind(priester);
		return 0;
	}
	else
	{
		return pid;
	}
}

void deadlock_observer(void)
{
	int array[2];
	int i;

	for(i=0;i<2;i++){
		array[i] = systemctl(semid_priester, i , GETVAL);
	}
	if(array[i]){

	}
}
