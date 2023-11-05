CFLAGS = -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -Werror

all: build

build:
	gcc $(CFLAGS) mem_test.c my_malloc.c list.o -o mem_test

run: build
	./mem_test


clean:
	rm -f mem_test
