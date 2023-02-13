# Compiler
C = gcc
CFLAGS = -g -std=gnu99 -Wall -pedantic

# Single target to run complie and get all binaries
shell: mytree.x mytime.x mymtimes.x

# Compiles and produces individual binary file
%.x:  %.c
	$(CC) $(CFLAGS) $< -o $@

# Removes (cleans) all binaries with .x extension
clean:
	rm -rf *.x