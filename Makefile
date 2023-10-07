CC=gcc
CFLAGS=-Os -pipe -Wall -pedantic -Werror
LIBS=-lgdi32
OUT=test.exe

all: test.c wingame.h
	$(CC) $(CFLAGS) -o $(OUT) $< $(LIBS)
	strip $(OUT)

clean:
	rm $(OUT)
