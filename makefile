all: hw5

hw5: mainTest.o
ifeq (${OS}, Windows_NT)
	g++ -o hw5 mainTest.o -lgtest
else
	g++ -o hw5 mainTest.o -lgtest -lpthread
endif
	
mainTest.o: utParser.h term.h atom.h number.h variable.h struct.h list.h scanner.h parser.h
	g++ -std=gnu++0x -c mainTest.cpp
mainMadRace.o: mainMadRace.cpp utMadRace.h
	g++ -std=gnu++0x -c mainMadRace.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw5
endif
