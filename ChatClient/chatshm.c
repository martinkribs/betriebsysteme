#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#include "chatshm.h"

/* Shared-Memory-Operationen */
int chat_shm_get(void)
{
	int shmid = 0;
	key_t key = ftok(".", 42);
	shmid = shmget(key, 0, 0);

	if (shmid == -1) {
		shmid = shmget(key, sizeof(struct chat_shm), IPC_EXCL|IPC_CREAT|0600);
		if (shmid == -1) {
			perror("create shared memory");
			exit(1);
		}
	}

	return shmid;
}

void *chat_shm_attach(int shmid)
{
	void *pmem = NULL;

	pmem = shmat(shmid, NULL, 0);
	if (pmem == (void *) -1) {
		perror("shmat");
		exit (1);
	}

	return pmem;
}
