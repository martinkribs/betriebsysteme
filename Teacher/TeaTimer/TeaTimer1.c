#include<unistd.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>

int
main ()
{
  while (1)
    {
      char name_1[21];

      int sek;
      printf ("Bitte geben Sie die Ziehzeit Sekunden ein \n");
      if (scanf ("%d", &sek) < 1)	/* Eingabe der Ziehzeit und Fehlerbehandlung falls ungenC<gende Eingabe */
    	{
    	  printf ("Fehler 1 bei scanf!\n");
    	  return 1;
    	}
      if (sek <= 0)		/* Fehlerbehandlung falls inkorrekte Ziehzeit eingegeben wurde */
    	{
    	  printf ("Fehler: nicht positive Zeit!\n");
    	}
          else
    	{
    	  printf ("Bitte geben Sie den Namen des Tee ein ");
    	  if (scanf ("%20s", name_1) < 1)	/* Eingabe des Teenamens und Fehlerbehandlung falls ungenügende Eingabe */
    	    {
    	      printf ("Fehler 2 bei scanf!\n");
    	      return 1;
    	    }
    	  sleep (sek);
    	  printf ("%s  ist fertig.\n", name_1);
	    }
    }

  return 0;
}

