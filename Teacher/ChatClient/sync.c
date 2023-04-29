#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "sync.h"

/* Semaphor-Operationen */

/* Semaphore anlegen bzw. weiterverwenden */
int chat_sem_get()
{
	int semid = 0;

	return semid;
}

/* Semaphoren mit Initialwerten versehen */
void chat_sem_init(int semid)
{
}

/* Implementierung von P/V */
void p(int semid, int sem_num)
{
}

void v(int semid, int sem_num)
{
}
