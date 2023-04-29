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
	shm = (struct chat_shm *) chat_shm_attach(shmid);
	shm->message[0] = 0;

	return 0;
}
