C = gcc
CFLAGS = -g -std=gnu99 -Wall -pedantic

%:  %.c
	$(CC) $(CFLAGS) $< -o $@.x

#removes (cleans) executables
clean:
	rm *.x