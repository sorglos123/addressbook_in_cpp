CC = g++

all: adressbuch.bin

clean:
	rm -rf adressbuch.bin *.o

adressbuch.bin: logic.o adress.cpp
	$(CC) -g -o adressbuch.bin logic.o adress.cpp -O2 -lfinal

ncurses.bin: logic.o ncurses.cpp
	$(CC) -g -o ncurses.bin logic.o ncurses.cpp -lncurses -lform

logic.o: logic.hpp logic.cpp
	$(CC) -g -c -o logic.o logic.cpp 