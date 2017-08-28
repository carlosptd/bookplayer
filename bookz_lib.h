#ifndef BOOKZ_LIB_H
#define BOOKZ_LIB_H

#define BOOKZ_LENGTH 80

/**
 * bookz_lib contains library functions for reading bookz (e.g., from the
 * file system) and displaying them to the user (e.g., on a terminal).
 */

extern int lines_read;

/**
 * Display all of the "lines" in a bookz.
 *
 * @param fdin   The file descriptor to get the "line" from
 * @param fdout  The file descriptor for the output
 */
void
display_all(int fdin, int fdout);


#endif
