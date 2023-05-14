#ifndef __PRIMSHM_H__
#define __PRIMSHM_H__

#include <sys/ipc.h>
#include <sys/shm.h>

#define MESSAGE_LENGTH 256

struct chat_shm {
	char message[MESSAGE_LENGTH];
};

/* Shared-Memory-Operationen */
int chat_shm_get(void);
void *chat_shm_attach(int shmid);

#endif
