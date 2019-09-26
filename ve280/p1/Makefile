all: p1

p1: p1.o
	g++ -o p1 p1.o
p1.o: p1.cpp
	g++ -c p1.cpp -std=c++11
clean: 
	rm -f p1*.o
