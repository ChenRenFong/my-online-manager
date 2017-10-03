all: hw2

hw2: mainTerm.o 
ifeq (${OS}, Windows_NT)
	g++ -o hw2 mainTerm.o -lgtest
else
	g++ -o hw2 mainTerm.o -lgtest -lpthread
endif
	
mainTerm.o: mainTerm.cpp utTerm.h
	g++ -std=gnu++0x -c mainTerm.cpp
mainVariable.o: mainVariable.cpp utVariable.h
	g++ -std=gnu++0x -c mainVariable.cpp
mainAtom.o: mainAtom.cpp utAtom.h
	g++ -std=gnu++0x -c mainAtom.cpp
mainMadRace.o: mainMadRace.cpp utMadRace.h
	g++ -std=gnu++0x -c mainMadRace.cpp

clean:	
ifeq (${OS}, Windows_NT)
	del *.o *.exe
else
	rm -f *.o hw2
endif
