CC = gcc
CFLAGS = -O2 -Wall
LIBFLAGS = -shared -fPIC -ldl -lpthread -lm
RAYLIB = /usr/local/lib/libraylib.so

all: test libgeigermtrace.so

test: test.c
	$(CC) $(CFLAGS) test.c -o test

libgeigermtrace.so: geigermtrace.c
	$(CC) $(CFLAGS) $(LIBFLAGS) -o libgeigermtrace.so geigermtrace.c $(RAYLIB)

run: all
	LD_PRELOAD=./libgeigermtrace.so ./test

clean:
	rm -f test libgeigermtrace.so
