all: calc call test
	rm -f result
	./calc < test-1 > output-1
	./test 1 >> result
	./call < test-2 > output-2
	./test 2 >> result
	rm -f calc call test *.o
	cat result

test: test.cpp
	g++ -o test test.cpp

calc: calc.cpp
	g++ -o calc calc.cpp

call: call.cpp
	g++ -o call call.cpp

clean:
	rm -f calc call test *.o output-* dlist.cpp calc.cpp call.cpp result
