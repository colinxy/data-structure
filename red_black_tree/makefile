CXX = g++

PROG     = test_tree.out
CPPFLAGS = -std=c++11 -Wall -g
OBJS     = test_tree.o

$(PROG) : $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(PROG) $(OBJS)

clean :
	rm *.o *.out

test_tree.o : test_tree.cpp red_black_tree.h
	$(CXX) $(CPPFLAGS) -c -o test_tree.o test_tree.cpp
