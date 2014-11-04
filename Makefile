CC = g++
CFLAGS = -g

.PHONY: clean

all: test xor digits

test: nnetwork.o
	$(CC) $(CFLAGS) test.cpp nnetwork.o -o test

xor: nnetwork.o
	$(CC) $(CFLAGS) xor.cpp nnetwork.o -o xor

digits: nnetwork.o
	$(CC) $(CFLAGS) digits.cpp nnetwork.o -o digits

nnetwork.o:
	$(CC) $(CFLAGS) -c nnetwork.cpp

clean:
	rm -f *.o test xor digits