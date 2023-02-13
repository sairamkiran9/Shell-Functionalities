# Compiler
C = gcc
CFLAGS = -g -std=gnu99 -Wall -pedantic

# Single target to run complie and get all binaries
shell: 
	$(CC) $(CFLAGS) mytree.c -o mytree.x
	$(CC) $(CFLAGS) mytime.c -o mytime.x
	$(CC) $(CFLAGS) mymtimes.c -o mymtimes.x

# command to get and individual binary file
%:  %.c
	$(CC) $(CFLAGS) $< -o $@.x

# removes (cleans) executables
clean:
	rm -rf *.x