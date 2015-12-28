CXX = g++

PROG     = test_stack.out
CPPFLAGS = -std=c++11 -g
OBJS     = stack.o test_stack.o

$(PROG) : $(OBJS)
	$(CXX) -o $(PROG) $(OBJS) $(CPPFLAGS)

clean  :
	rm $(PROG) $(OBJS)

test_stack.o : test_stack.cpp stack.h
	$(CXX) -c -o test_stack.o test_stack.cpp $(CPPFLAGS)

stack.o      : stack.cpp stack.h
	$(CXX) -c -o stack.o stack.cpp $(CPPFLAGS)
