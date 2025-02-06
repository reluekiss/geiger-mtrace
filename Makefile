CC = gcc
CFLAGS = -O2 -Wall
LIBFLAGS = -shared -fPIC -ldl -lpthread -lm
RAYLIB = /usr/local/lib/libraylib.so

all: examples/test libgeigermtrace.so

examples: examples/stack examples/stock examples/test

examples/stock: examples/stock.c
	mkdir -p build
	$(CC) $(CFLAGS) $(RAYLIB) -lm examples/stock.c -o build/stock

stock: all
	LD_PRELOAD=./build/libgeigermtrace.so ./build/stock

examples/stack: examples/stack.c
	mkdir -p build
	$(CC) $(CFLAGS) examples/stack.c -o build/stack

stack: all
	LD_PRELOAD=./build/libgeigermtrace.so ./build/stack

examples/test: examples/test.c
	mkdir -p build
	$(CC) $(CFLAGS) examples/test.c -o build/test

test: all
	LD_PRELOAD=./build/libgeigermtrace.so ./build/test

libgeigermtrace.so: geigermtrace.c
	mkdir -p build
	$(CC) $(CFLAGS) $(LIBFLAGS) -o build/libgeigermtrace.so geigermtrace.c $(RAYLIB)

clean:
	rm -rf build
