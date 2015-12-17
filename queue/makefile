CXX = g++

PROG     = test_queue
CPPFLAGS = -std=c++11 -g
OBJS     = test_queue.o queue.o

$(PROG) : $(OBJS)
	$(CXX) -o $(PROG) $(OBJS) $(CPPFLAGS)

clean   :
	rm $(PROG) $(OBJS)

test_queue.o : test_queue.cpp queue.h
	$(CXX) -c -o test_queue.o test_queue.cpp $(CPPFLAGS)

queue.o      : queue.cpp queue.h
	$(CXX) -c -o queue.o queue.cpp $(CPPFLAGS)
