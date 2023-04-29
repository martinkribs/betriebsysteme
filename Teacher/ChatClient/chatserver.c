#include <stdio.h>
#include <unistd.h>

#include "chatshm.h"
#include "sync.h"

int main()
{
	unsigned msg_count = 0;

	/* Shared Memory einrichten */
	int shmid = chat_shm_get();

	struct chat_shm *shm = NULL;
	shm = (struct chat_shm *) chat_shm_attach(shmid);

	/* eingehende Nachrichten ausgeben ... */
	while (1) {
		printf("chatserver (%u): %s\n", ++msg_count, shm->message);

		/* ein bisschen schlafenlegen ... */
		sleep(2);
	}

	return 0;
}
