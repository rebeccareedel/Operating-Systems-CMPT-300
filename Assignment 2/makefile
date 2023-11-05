CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror

all: build

build:
	gcc $(CFLAGS) main.c receiver.c scanner.c sender.c printer.c shutdownManager.c list.o -lpthread -o s-talk



run: build
	./s-talk


clean:
	rm -f s-talk 