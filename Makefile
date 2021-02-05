CC = g++

all: adressbuch.bin

clean:
	rm -rf adressbuch.bin *.o

adressbuch.bin: logic.o list.cpp
	$(CC) -o adressbuch.bin logic.o list.cpp -lncurses -lform

list.o: list.cpp
	$(CC) -c -o list.o list.cpp -lncurses -lform

logic.o: logic.hpp logic.cpp
	$(CC) -c -o logic.o logic.cpp 
