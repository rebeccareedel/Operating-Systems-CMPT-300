CFLAGS = -g -std=c99 -D _POSIX_C_SOURCE=200809L 

all: build

build:
	gcc $(CFLAGS) dssimul.c -o DSSimul

run: build
	./DSSimul


clean:
	rm -f DSSimul
