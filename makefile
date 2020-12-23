CXX = g++
CXXFLAGS = -Wall

driver: driver.cpp wordTree.o bookTree.o bNode.o
	$(CXX) $(CXXFLAGS) driver.cpp wordTree.o bookTree.o bNode.o -o driver
	./driver

mytest: mytest.cpp wordTree.o bookTree.o bNode.o
	$(CXX) $(CXXFLAGS) mytest.cpp wordTree.o bookTree.o bNode.o -o mytest
	./mytest

clean:
	rm *.o