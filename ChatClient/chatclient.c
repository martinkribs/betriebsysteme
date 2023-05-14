#include <stdio.h>

#include "chatshm.h"
#include "sync.h"

/* Shared-Memory-ID */
static int shmid = 0;

int main(void)
{
	struct chat_shm *shm = NULL;
	int semid = 0;

	/* Shared Memory einrichten */
	shmid = chat_shm_get();

	/* Shared-Memory-Segment einbinden und initialisieren */
	shm = (struct chat_shm *)chat_shm_attach(shmid);

	/* Erstellung, bzw Aufrufung der Semaphormenge zur benutzung im Programm */
	semid = chat_sem_get();
	
	/* initialisieren der Werte der Semaphoren */
	chat_sem_init(semid);

	/* Nachrichten an Server senden ... */
	while (1)
	{
		/* Verkleinern von sem_frei um 1, ansonsten warten darauf dass sem_belegt größer als 0 wird */
		p(semid, 0);

		if (scanf("%255s", shm->message) < 1) /* Eingabe des Teenamens und Fehlerbehandlung falls ungenügende Eingabe */
		{
			printf("Fehler bei 2 scanf !\n");
			return -1;
		}
		
		/* Vergrößern von sem_belegt um 1 (also Durchgabe an Chatserver dass Nachricht eingelesen wurde, die ausgegeben werden kann) */
		v(semid, 1);
	}

	return 0;
}
