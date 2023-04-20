#include <stdio.h> // for printf and scanf

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
    }
    return 0;
}