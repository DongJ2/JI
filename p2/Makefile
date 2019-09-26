all: main

main: main.o selection.o
	g++ -o main main.o selection.o

main.o: main.cpp
	g++ -c main.cpp -std=c++11

selection.o: selection.cpp
	g++ -c selection.cpp

clean: rm -f main*.o selection*.o

