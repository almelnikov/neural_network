CC = g++
CFLAGS = -g

.PHONY: clean

all: test xor digits digits_hop

test: nnetwork.o test.cpp
	$(CC) $(CFLAGS) test.cpp nnetwork.o -o test

xor: nnetwork.o xor.cpp
	$(CC) $(CFLAGS) xor.cpp nnetwork.o -o xor

digits: digitops.o nnetwork.o digits.cpp
	$(CC) $(CFLAGS) digits.cpp nnetwork.o digitops.o -o digits

digits_hop: digitops.o hopfield.o digits_hop.cpp
	$(CC) $(CFLAGS) digits_hop.cpp hopfield.o digitops.o -o digits_hop

nnetwork.o: nnetwork.cpp
	$(CC) $(CFLAGS) -c nnetwork.cpp

hopfield.o: hopfield.cpp
	$(CC) $(CFLAGS) -c hopfield.cpp

digitops.o: digitops.cpp
	$(CC) $(CFLAGS) -c digitops.cpp

clean:
	rm -f *.o test xor digits
