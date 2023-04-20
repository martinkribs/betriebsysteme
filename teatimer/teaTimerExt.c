#include <stdio.h>  // for printf and scanf
#include <stdlib.h> // for external Programm calls
#include <unistd.h> //for fork

int main()
{
    int time;
    char teaName[64];
    while (1)
    {
        printf("Enter the time in seconds: ");
        scanf("%d", &time);
        printf("Enter your Tea name: ");
        scanf("%s", teaName);
        sleep(time);
        printf("Your %s is ready :)\n", teaName);
        system("fortune"); // external Programm call
        execlp("fortune", "fortune", NULL, NULL);
    }
    return 0;
}

// explanation:
// "fortune": the name of the program to run
// "fortune": the first argument to the program (which is usually the name of the program itself)
// NULL: the second argument to the program, indicating that we want to list files in long format
// NULL: a sentinel value indicating the end of the argument list