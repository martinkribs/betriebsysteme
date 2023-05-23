#include <stdio.h>
#include <unistd.h>

#include "chatshm.h"
#include "sync.h"

int main()
{
	unsigned msg_count = 0;
	int semid = 0;

	/* Shared Memory einrichten */
	int shmid = chat_shm_get();
	struct chat_shm *shm = NULL;
	shm = (struct chat_shm *)chat_shm_attach(shmid);

	/* semaphore bekommen */
	semid = chat_sem_get();

	/* initialisieren der Werte der Semaphoren */
	chat_sem_init(semid);

	/* eingehende Nachrichten ausgeben ... */
	while (1)
	{
		/* kritischer Abschnitt */
		p(semid,1);

		/* code */
		printf("chatserver (%u): %s\n", ++msg_count, shm->message);
		shm->message[0] = 0;

		/* Kritischer Abschnitt wird verlassen, sem_frei um eins erhöht */
		v(semid,0);
		
		/* ein bisschen schlafenlegen ... */
		/*sleep(2);*/
	}

	return 0;
}
