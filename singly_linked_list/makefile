CXX = g++

PROG 	 = test_linked.out
CPPFLAGS = -std=c++11 -g
OBJS 	 = test_linked.o

$(PROG) : $(OBJS)
	$(CXX) -o $(PROG) $(OBJS) $(CPPFLAGS)

clean :
	rm $(PROG) $(OBJS)

test_linked.o : test_linked.cpp singly_linked.h
	$(CXX) -c -o test_linked.o test_linked.cpp $(CPPFLAGS)
