#ifndef ADZ_LIB_H
#define ADZ_LIB_H

#define ADZ_LENGTH 40
#include <pthread.h>

// Declarations of the Mutexes and the Shared Variables they Protect
extern pthread_mutex_t adz_mutex;
extern int    adz_updated;
extern char   adz_current_text[];

extern pthread_mutex_t bookz_mutex;
extern int    bookz_done;



// Functions with external linkage
void
display_adz(int fdout);

long
start_adz(char id, int fdout);


#endif
