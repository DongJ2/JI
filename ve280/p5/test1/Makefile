all: calc call test
	rm -f result
	./calc < test-1 > output-1
	./test 1 >> result
	./call < test-2 > output-2
	./test 2 >> result
	./call < test-3 > output-3
	./test 3 >> result
	./call < test-4 > output-4
	./test 4 >> result
	./call < test-5 > output-5
	./test 5 >> result
	./call < test-6 > output-6
	./test 6 >> result
	./call < test-7 > output-7
	./test 7 >> result
	./call < test-8 > output-8
	./test 8 >> result
	./call < test-9 > output-9
	./test 9 >> result
	./call < test-10 > output-10
	./test 10 >> result
	./call < test-11 > output-11
	./test 11 >> result
	./call < test-12 > output-12
	./test 12 >> result
	./call < test-13 > output-13
	./test 13 >> result
	./call < test-14 > output-14
	./test 14 >> result
	./call < test-15 > output-15
	./test 15 >> result
	./calc < test-16 > output-16
	./test 16 >> result
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
