CXX_FLAG = --std=c++11 -g
CC = g++

project3.out: avlTree.cpp project3.cpp
	g++ avlTree.cpp project3.cpp -o project3.out

project3.o: project3.cpp
	g++ -c $(CXX_FLAG) project3.cpp

avlTree.o: avlTree.cpp	
	g++ -c $(CXX_FLAG) avlTree.cpp avlTree.h

clean: 
	rm -f project3 avlTree *.o *.out *.gch