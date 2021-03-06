CC = g++

all: adressbuch.bin

clean:
	rm -rf adressbuch.bin *.o

adressbuch.bin: logic.o adress.cpp
	$(CC) -o adressbuch.bin logic.o adress.cpp -O2 -lfinal

ncurses.bin: logic.o ncurses.cpp
	$(CC) -o ncurses.bin logic.o ncurses.cpp -lncurses -lform

logic.o: logic.hpp logic.cpp
	$(CC) -c -o logic.o logic.cpp 