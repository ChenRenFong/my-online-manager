all: hw3

hw3: mainTest.o
ifeq (${OS}, Windows_NT)
	g++ -o hw3 mainTest.o -lgtest
else
	g++ -o hw3 mainTest.o -lgtest -lpthread
endif
	
mainTest.o: utStruct.h utVariable.h utTerm.h utAtom.h utNumber.h 
	g++ -std=gnu++0x -c mainTest.cpp
mainMadRace.o: mainMadRace.cpp utMadRace.h
	g++ -std=gnu++0x -c mainMadRace.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw3
endif
