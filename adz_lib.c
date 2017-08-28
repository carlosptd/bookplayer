#include "adz_lib.h"
#include <stdio.h> 
#include <fcntl.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// PA8
// Definitions of the Mutexes and the Shared Variables they Protect
pthread_mutex_t adz_mutex   = PTHREAD_MUTEX_INITIALIZER;
int    adz_updated = 0;
char   adz_current_text[ADZ_LENGTH];

pthread_mutex_t bookz_mutex = PTHREAD_MUTEX_INITIALIZER;
int    bookz_done = 0;



// The following functions have external linkage (and are exposed in the
// .h file)


void
display_adz(int fdout)
{
  char text[ADZ_LENGTH];

  pthread_mutex_lock(&adz_mutex);   // Start of the critical section
  strncpy(text, adz_current_text, ADZ_LENGTH);
  adz_updated = 0;
  pthread_mutex_unlock(&adz_mutex); // End of the critical section

  write(fdout, "\n",   1);
  write(fdout, text,   ADZ_LENGTH);
  write(fdout, "\n\n", 2);
}



long
start_adz(char id, int fdout)
{
  char        name[] = "?.adz";
  char        delay_field[3], line[ADZ_LENGTH];
  int         delay, fdin, keep_going;
  long        count;
  ssize_t     n;
  count = 0;
  name[0] = id;
  fdin = open(name,  O_RDONLY);
  if (fdin >= 0)
    {
      keep_going = 1; // PA8 (Assumes one ad is always displayed)
      while (keep_going &&  // PA8
	     ((n = read(fdin, line, ADZ_LENGTH)) == ADZ_LENGTH))
	{
	  delay_field[0] = line[0];
	  delay_field[1] = line[1];
	  delay_field[2] = '\0';
	  delay = atoi(delay_field);
	  printf("delay %d\n",delay); 
	  // PA8
	  pthread_mutex_lock(&adz_mutex);   // Start of the critical section
	  strncpy(adz_current_text, line+2, ADZ_LENGTH-2);
	  adz_updated = 1;
	  pthread_mutex_unlock(&adz_mutex); // End of the critical section
	  
	  ++count;
	  sleep(delay);

	  // PA8
	  pthread_mutex_lock(&bookz_mutex);   // Start of critical section
	  keep_going = !bookz_done;
	  pthread_mutex_unlock(&bookz_mutex); // End of critical section
	}

    }else printf("unable to open file\n"); 

  close(fdin);

  return count;
}
