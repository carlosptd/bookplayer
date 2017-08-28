#
# Simple Makefile
# This work complies with the JMU Honor Code.
#

FREE_BOOKZ= free_bookz_player
BOOKZ_MODS= bookz_lib.o adz_lib.o
FREE_BOOKZ_MODS= bookz_lib.o adz_lib.o
default: $(FREE_BOOKZ)

# compiler/linker settings

CC=gcc
CFLAGS = -pedantic -pedantic-errors -Wall -std=c99
LDFLAGS=-g -O0
MTH = -lm -pthread


# build targets

$(FREE_BOOKZ): free_bookz_player.o $(FREE_BOOKZ_MODS)
	$(CC) $(LDFLAGS) -o $(FREE_BOOKZ) $^ $(MTH) -D ADZ

%.o: %.c
	$(CC) -c $(CFLAGS) $< $(MTH)

clean:
	rm *.o; 
	rm free_bookz_player
.PHONY: default clean
