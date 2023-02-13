# Compiler
C = gcc
CFLAGS = -g -std=gnu99 -Wall -pedantic

# Single target to run complie and get all binaries
shell: 
	$(CC) $(CFLAGS) mytree.c -o mytree.x
	$(CC) $(CFLAGS) mytime.c -o mytime.x
	$(CC) $(CFLAGS) mymtimes.c -o mymtimes.x

# Compiles and produces individual binary file
%:  %.c
	$(CC) $(CFLAGS) $< -o $@.x

# Removes (cleans) all binaries with .x extension
clean:
	rm -rf *.x