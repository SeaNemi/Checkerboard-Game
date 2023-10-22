CXX = g++
CXXFLAGS = -Wall -g
IODIR =../../proj0_IO/

proj0: checkers.o mytest.cpp
	$(CXX) $(CXXFLAGS) checkers.o mytest.cpp -o proj0

checkers.o: checkers.h checkers.cpp
	$(CXX) $(CXXFLAGS) -c checkers.cpp

clean:
	rm *.o*
	rm *~

run:
	./proj0

val:
	valgrind ./proj0