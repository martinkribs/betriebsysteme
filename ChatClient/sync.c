#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "sync.h"
#define KEY 0xcaffee /* ein Schlüssel zur Suche nach Sem.-Mengen*/
#define RIGHTS 0600	 /* volle Zugriffsrechte für den Benutzer*/

/* Semaphor-Operationen */

/* Semaphore anlegen bzw. weiterverwenden */
int chat_sem_get()
{
	int semid = 0;
	/* gibt es schon eine Semaphorenmenge zu diesem SChlüssel?*/
	semid = semget(KEY, 0, 0);
	if (semid < 0)
	{
		printf("create new semaphore\n");
		semid = semget(KEY, 1, IPC_EXCL | IPC_CREAT | RIGHTS);
		if (semid < 0)
		{
			perror("semget");
			return -1;
		}
	}
	return semid;
}

/* Semaphoren mit Initialwerten versehen */
void chat_sem_init(int semid)
{
	int retval = 0;
	if (semid > 0)
	{
		retval = semctl(semid, 0, SETVAL, 1);
		if (retval < 0)
		{
			perror("semctl SET");
		}
		retval = semctl(semid, 0, GETVAL);
		if (retval < 0)
		{
			perror("semctl GET");
		}
		printf("Semaphore hat den Wert %d\n",retval);
	}
}

/* Implementierung von P/V */
void p(int semid, int sem_num)
{
	struct sembuf semaphor_operation;
	semaphor_operation.sem_num = sem_num;
	/* hier ist das erniedrigen */
	semaphor_operation.sem_op = -1;
	semaphor_operation.sem_flg = 0;

	if (semop(semid, &semaphor_operation, 1))
	{
		perror("p");
	}
}

void v(int semid, int sem_num)
{
	struct sembuf semaphor_operation;
	semaphor_operation.sem_num = sem_num;
	/* hier ist das erhöhen */
	semaphor_operation.sem_op = 1;
	semaphor_operation.sem_flg = 0;

	if (semop(semid, &semaphor_operation, 1))
	{
		perror("v");
	}
}
