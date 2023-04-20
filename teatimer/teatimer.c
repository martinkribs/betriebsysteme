#include <stdio.h>     // for printf and scanf
#include <unistd.h>    //for fork
#include <sys/types.h> // for type pid_t
#include <stdlib.h>    // for external Programm calls
#include <sys/wait.h>  // for wait
#include <errno.h>     // for perror
#include <string.h>     // for string compare

void teaTimer(int *time, char *teaName);
void printProcessList();
void user_question(int *time, char *teaName);

int main()
{
    while (1)
    {
        int time;
        char teaName[64];
        pid_t pid, finished_pid;
        user_question(&time, teaName);
        // duplicate process
        pid = fork();
        switch (pid)
        {
        case -1:
            perror("fork");
            exit(1);
        case 0:
            printf("I'm the child");
            printf("--------------------\n");
            printf("Die ID des Elternprozesses ist %d\n", getppid());
            printf("Die ID des Kindprozesses ist %d\n", getpid());
            printf("--------------------\n");
            sleep(time);
            printf("Your %s is ready :)\n", teaName);
            exit(0);
        default:
            printf("I'm the parent");
            finished_pid = waitpid(pid, NULL, 0);
            printf("Prozess-ID des dahingeschiedenen Kindes ist: %d .\n", finished_pid);
        }
    }
    return 0;
}

void printProcessList()
{
    printf("--------------------\n");
    execlp("ps", "ps", "-l", NULL);
    printf("--------------------\n");
}

void user_question(int *time, char *teaName)
{
    printf("Enter the time in seconds: ");
    scanf("%d", &time);
    printf("Enter your Tea name (or 'exit' to exit)");
    scanf("%s", &teaName);
    if (strcmp(teaName, "exit") == 0)
    {
        exit(0);
    }
}