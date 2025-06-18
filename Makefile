CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: main

main: main.c libds.c
	$(CC) $(CFLAGS) -o main main.c libds.c

# .PHONY: clean
clean:
	rm main
