C = gcc
CFLAGS = -g -std=gnu99 -Wall -pedantic

#creates .x binaries of .c files
%:  %.c
	$(CC) $(CFLAGS) $< -o $@.x

#removes (cleans) executables
clean:
	rm *.x