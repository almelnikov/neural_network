CC = g++
CFLAGS = -g

.PHONY: clean

all: test xor digits

test: nnetwork.o test.cpp
	$(CC) $(CFLAGS) test.cpp nnetwork.o -o test

xor: nnetwork.o xor.cpp
	$(CC) $(CFLAGS) xor.cpp nnetwork.o -o xor

digits: nnetwork.o digits.cpp
	$(CC) $(CFLAGS) digits.cpp nnetwork.o -o digits

nnetwork.o: nnetwork.cpp
	$(CC) $(CFLAGS) -c nnetwork.cpp

clean:
	rm -f *.o test xor digits