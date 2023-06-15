#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#include "sync.h"
#define KEY 0x6f6e616e
/* Semaphor-Operationen */

/* Semaphore anlegen bzw. weiterverwenden */
int chat_sem_get()
{
	int semid = 0;
	
	/* erstellung eines Schlüssels */
	/*key_t KEY = ftok(".", 42);*/
	semid = semget(KEY,2,0);
	printf("semid: %d\n",semid);
	if (semid<0){
		printf("create new semaphore\n");
		semid = semget(KEY,2, IPC_EXCL|IPC_CREAT|0600);
	}
	printf("semid: %d\n",semid);
	return semid;
}

/* Semaphoren mit Initialwerten versehen */
void chat_sem_init(int semid)
{
	int retval = 0;
	/*key_t KEY = ftok(".", 42);*/
	semid = semget(KEY, 0, 0);
	if(semid>=0){
		retval = semctl(semid,0,SETVAL,(int) 5);
		retval = semctl(semid,0,GETVAL);
		printf("Semaphore 0 hat Wert %d\n",retval);
		retval = semctl(semid,1,SETVAL, (int) 0);
		retval = semctl(semid,1,GETVAL);
		printf("Semaphore 1 hat Wert %d\n\n",retval);
		/*semctl(semid,0,IPC_RMID);*/
		
	}
}

/* Implementierung von P/V */
void p(int semid, int sem_num)
{
	int retval = 0;
	struct sembuf sop;
	sop.sem_num = sem_num;
	sop.sem_op = -1;
	sop.sem_flg = 0;
	semop(semid,&sop,1);
	retval = semctl(semid,sem_num,GETVAL);
	printf("Semaphore %i hat Wert %d\n\n",sem_num, retval);
}

void v(int semid, int sem_num)
{
	int retval = 0;
	struct sembuf sop;
	sop.sem_num = sem_num;
	sop.sem_op = 1;
	semop(semid,&sop,1);
	retval = semctl(semid,sem_num,GETVAL);
	printf("Semaphore %i hat Wert %d\n",sem_num, retval);
}
