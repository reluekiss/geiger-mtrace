CC = gcc
CFLAGS = -O2 -Wall
LIBFLAGS = -shared -fPIC -ldl -lpthread -lm
RAYLIB = /usr/local/lib/libraylib.so

all: examples/stack libgeigermtrace.so

examples: libgeigermtrace.so examples/stack examples/stock examples/test

examples/stock: build examples/stock.c
	$(CC) $(CFLAGS) $(RAYLIB) -lm examples/stock.c -o build/stock

stock: examples/stock 
	LD_PRELOAD=./build/libgeigermtrace.so ./build/stock

examples/stack: build examples/stack.c
	$(CC) $(CFLAGS) examples/stack.c -o build/stack

stack: examples/stack
	LD_PRELOAD=./build/libgeigermtrace.so ./build/stack

examples/test: build examples/test.c
	$(CC) $(CFLAGS) examples/test.c -o build/test

test: examples/test
	LD_PRELOAD=./build/libgeigermtrace.so ./build/test

libgeigermtrace.so: build geigermtrace.c
	$(CC) $(CFLAGS) $(LIBFLAGS) -o build/libgeigermtrace.so geigermtrace.c $(RAYLIB)

build:
	mkdir -p build

clean:
	rm -rf build
