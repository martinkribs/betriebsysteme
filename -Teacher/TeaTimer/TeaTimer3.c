#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>

#include<sys/wait.h>
#include<errno.h>

int main()
{
 while( 1 )
 {
  char name[21];
  int sek ;
  printf( "Bitte geben Sie die Ziehzeit in Sekunden ein: \n" );
  if( scanf( "%d", &sek )<1 )		/* Eingabe der Ziehzeit und Fehlerbehandlung falls ungenügende Eingabe */
  {
   printf( "Fehler 1 bei scanf!\n" );
   return 1;
  }
  if( sek <=0 )		/* Fehlerbehandlung falls inkorrekte Ziehzeit eingegeben wurde */
  {
   printf( "Fehler: nicht positive Zeit !\n" );
   return 1;
  }
  printf( "Bitte geben Sie den Namen des Tee ein: \n" );
  if( scanf( "%20s", name )<1 )		/* Eingabe des Teenamens und Fehlerbehandlung falls ungenügende Eingabe */
  {
   printf( "Fehler bei 2 scanf !\n" );
   return 1;
  }

  int pid=fork();	/* Erzeugung des Kindprocesses */
  
  if( pid==0 )		/* Programmteil der durch den Kindprocess ausgeführt wird */
  {
   printf( "Ich bin ein Kind mit PID: %d \n", (int)getpid() );
   sleep( sek );
   printf( "%s ist fertig.\n", name );
   exit(0);  
   return 0;
  }

  if( pid>0 )		/* Programmteil der durch den Vaterprocess ausgeführt wird */
  {
   printf("Im Vater Neues Kind erzeugt PID des Kindes: %d \n", pid );
   pid_t res;
   while(( res=waitpid(-1, NULL, WNOHANG )) > 0 )	/* Suche und Entfernung der Zombies */
   {
    printf("Kind mit PID: %d has terminiert \n", (int)res);
   } 
   if( res== -1 )	/* Fehlerbehandlung für Fehler bei der Entfernung der Zombies */
      if( errno!=ECHILD )
      {
       printf(" Fehler bei waitpid \n");
       exit( EXIT_FAILURE );
      } 
  }


  if( pid<0 )	/* Fehlerbehandlung für Fehler bei fork() */
  {
   printf( "Fehler bei fork()!\n" );
   return 1;
  } 

 } 

 return 0;
} 


