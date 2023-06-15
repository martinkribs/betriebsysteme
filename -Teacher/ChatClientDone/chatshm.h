#ifndef __PRIMSHM_H__
#define __PRIMSHM_H__

#include <sys/ipc.h>
#include <sys/shm.h>

#define MESSAGE_LENGTH 256

struct chat_shm {
	char message[5][MESSAGE_LENGTH];
	int schreibposition;
	int leseposition;
};

/* Shared-Memory-Operationen */
int chat_shm_get(void);
void *chat_shm_attach(int shmid);

#endif
