parser: main.o lexical.o
	g++ -Wall -fexceptions -g -std=c++11 -o parser main.o lexical.o
	rm *.o

main.o: lexical_analyser.h lexical.o
	g++ -Wall -fexceptions -g -std=c++11 -c main.cpp

lexical.o: lexical_analyser.h lexical_analyser.cpp
	g++ -Wall -fexceptions -g -std=c++11 -o lexical.o -c lexical_analyser.cpp

clean:
	rm *.o parser