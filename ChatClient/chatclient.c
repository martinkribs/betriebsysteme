#include <stdio.h>

#include "chatshm.h"
#include "sync.h"

/* Shared-Memory-ID */
static int shmid = 0;

int main(void)
{
	struct chat_shm *shm = NULL;

	/* Shared Memory einrichten */
	shmid = chat_shm_get();

	/* Shared-Memory-Segment einbinden und initialisieren */
	shm = (struct chat_shm *)chat_shm_attach(shmid);

	/* Nachrichten an Server senden ... */
	while (1)
	{
		if (scanf("%255s", shm->message) < 1) /* Eingabe des Teenamens und Fehlerbehandlung falls ungenügende Eingabe */
		{
			printf("Fehler bei 2 scanf !\n");
			return 1;
		}
	}

	return 0;
}
