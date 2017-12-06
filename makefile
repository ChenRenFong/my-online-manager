all: hw7

hw7: mainTest.o term.o struct.o list.o
ifeq (${OS}, Windows_NT)
	g++ -o hw7 mainTest.o term.o struct.o list.o -lgtest
else
	g++ -o hw7 mainTest.o term.o struct.o list.o -lgtest -lpthread
endif
	
mainTest.o: utIterator.h atom.h number.h variable.h scanner.h parser.h node.h iterator.h
	g++ -std=gnu++0x -c mainTest.cpp 
term.o: term.h
	g++ -std=gnu++0x -c term.cpp 
struct.o: struct.h 
	g++ -std=gnu++0x -c struct.cpp 
list.o: list.h 
	g++ -std=gnu++0x -c list.cpp 
mainMadRace.o: mainMadRace.cpp utMadRace.h
	g++ -std=gnu++0x -c mainMadRace.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw7
endif
