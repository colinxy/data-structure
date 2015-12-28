CXX = g++

PROG     = test_heap.out
CPPFLAGS = -std=c++11 -g
OBJS 	 = test_heap.o

$(PROG) : $(OBJS)
	$(CXX) -o $(PROG) $(OBJS) $(CPPFLAGS)

clean   :
	rm $(PROG) $(OBJS)

test_heap.o : test_heap.cpp minheap.h maxheap.h
	$(CXX) -c -o test_heap.o test_heap.cpp $(CPPFLAGS)
