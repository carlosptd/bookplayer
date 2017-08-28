//#ifdef ADZ
#include "adz_lib.h"
//#endif
#include "bookz_lib.h"
#include <stdio.h>  // For FILE
#include <time.h>
#include <unistd.h> // For ssize_t

// Variables with file-scope and external linkage
int lines_read = 0;

// The following functions have internal linkage (and are not exposed
// in the .h file)

/**
 * Get the next "line" in a bookz.
 *
 * @param fdin   The file descriptor to get the "line" from
 * @param buffer The buffer that will hold the result
 * @return       The size of the line (or -1)
 */
static ssize_t
get_line(int fdin, char *buffer)
{
  ssize_t result = read(fdin, buffer, BOOKZ_LENGTH);
  return result;
}

/**
 * Display the next "line" in a bookz.
 *
 * @param fdin   The file descriptor to get the "line" from
 * @param fdout  The file descriptor for the output
 * @return       The size of the line (or -1)
 */
static ssize_t 
display_line(int fdin, int fdout)
{
  char  line[BOOKZ_LENGTH+2];
  ssize_t result = get_line(fdin, line);

  if (result == BOOKZ_LENGTH)
    {
      line[BOOKZ_LENGTH] = '\n';
      line[BOOKZ_LENGTH+1] = '\0';
      write(fdout, line, BOOKZ_LENGTH+1);
    }

  // PA8
  //#ifdef ADZ
  pthread_mutex_lock(&adz_mutex);   // Start of critical section
  int should_display = adz_updated;
  pthread_mutex_unlock(&adz_mutex); // End of the critical section
  if (should_display) display_adz(fdout);
  //#endif
  
  return result;
}

// The following functions have external linkage (and are exposed in the
// .h file)

void 
display_all(int fdin, int fdout)
{
  lines_read = 0;
  while (display_line(fdin, fdout) == BOOKZ_LENGTH)
    {
      lines_read++;
      sleep(1);
    }
}

