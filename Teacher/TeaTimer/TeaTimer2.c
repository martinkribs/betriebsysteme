#include <stdio.h>
#include <unistd.h>

int main(void) 
	{
	int z;
	char tee1[21];
	char bef[41] = {"fortune"};	/* Angabe des Programms das am Ende durch execlp
					ausgefuehrt werden soll */
	while(1)
		{
		printf( "Bitte geben Sie die Ziehzeit in Sekunden ein: \n" );
		if(scanf( "%d", &z )<1)	/* Eingabe der Ziehzeit und Fehlerbehandlung falls ungenÃ¼gende Eingabe */
  			{
   			printf("Fehler 1 bei scanf!\n");
   			return 1;
  			} 
		if(z <= 0)			/* Fehlerbehandlung falls inkorrekte Ziehzeit eingegeben wurde */
  			{
   			printf( "Fehler: nicht positive Zeit!\n" );
  			}
		else 	{
			printf("Teenamen eingeben:\n");
			while(scanf("%20s", tee1)< 1) 	/* Eingabe des Teenamens und Fehlerbehandlung falls ungenügende Eingabe */
				{
				printf("Fehler 2 bei scanf!\n");
				return 1;
				}
			
			sleep(z);
			printf("%20s ist fertig!\n", tee1);
			execlp(bef, bef, NULL);	/* Aufruf des Programms fortune (oder beliebiges
						Programm eingegeben in "bef") */
			return 1;
			}
		}
	return 1;
	}
		

