#include <stdio.h>
#include <unistd.h>

#include "chatshm.h"
#include "sync.h"
int semid=0;
int main()
{
	unsigned msg_count = 0;
	/* Shared Memory einrichten */
	int shmid = chat_shm_get();
	struct chat_shm *shm = NULL;
	shm = (struct chat_shm *) chat_shm_attach(shmid);
	semid = chat_sem_get();
	shm->leseposition=0;
	/* eingehende Nachrichten ausgeben ... */
	while (1) {
		/* Kritischer Abschnitt wird betreten, sem_belegt um eins erniedrigt */
		p(semid,1);
		printf("chatserver (%u): %s", ++msg_count, shm->message[(shm->leseposition)%5]);
		shm->leseposition = shm->leseposition+1;
		/* Degubausgaben: */
		printf("memory: [%.1s, %.1s, %.1s, %.1s, %.1s]\n", shm->message[0], shm->message[1], shm->message[2], shm->message[3], shm->message[4]);
		printf("schreibposition: %i\n", shm->schreibposition);
		printf("leseposition: %i\n\n", shm->leseposition);
		/* Kritischer Abschnitt wird verlassen, sem_frei um eins erhöht */
		v(semid,0);
		/* ein bisschen schlafenlegen ... */
		sleep(1);
	}

	return 0;
}
