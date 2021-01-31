CC = g++

all: programm.bin

clean:
	rm -rf programm.bin *.o

programm.bin: logic.o ncurses.cpp
	$(CC)  -o programm.bin logic.o ncurses.cpp -lncurses -lform

ncurses.o: ncurses.cpp
	$(CC) -c -o ncurses.o ncurses.cpp -lncurses -lform

lgic.o: logic.hpp logic.cpp
	$(CC) -c -o logic.o logic.cpp 
