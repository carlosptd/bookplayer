#define ADZ
#include "adz_lib.h"
#include "bookz_lib.h"
#include <fcntl.h>
#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


static void
*adz_player_entry(void *arg)
{
  long  n;
  void *result;
  
  char id = *(char *)arg;
  n = start_adz(id , STDOUT_FILENO);

  result = (void *)n;
  
  return result;
}


int
main(int argc, char *argv[])
{
  char        id;
  char        *message = NULL;
  char        name[] = "?.bookz";
  int         fd, n;
  long        ads_displayed;
  pthread_t   adz_thread;
  void        *result;

  
  if (argc > 1)
    {
      id      = argv[1][0];
      name[0] = id; 
      fd = open(name,  O_RDONLY);
      if (fd >= 0)
	{
	  // Start the adz_thread
	  pthread_create(&adz_thread, NULL, adz_player_entry, (void *)&id);
	  
	  // Display the bookz in the main thread
	  display_all(fd, STDOUT_FILENO);
	  close(fd);

	  // Stop the adz_thread
	  pthread_mutex_lock(&bookz_mutex);   // Start of critical section
	  bookz_done = 1;
	  pthread_mutex_unlock(&bookz_mutex); // End of critical section
	  
	  // Wait for the adz_thread to terminate
	  pthread_join(adz_thread, &result);

	  ads_displayed = (long)result;
	  
	  n = 7 + ((int)log10(lines_read)) + 1 
	    + 7 + ((int)log10(ads_displayed)) + 1 
	    + 2;

	  message = (char *)malloc(n * sizeof(char));
	  sprintf(message, "Lines: %d, Ads: %ld\n", lines_read, ads_displayed);
	  write(STDOUT_FILENO, message, n);
	  free(message);

	  return 0;
	}
    }

  return 1;
}
