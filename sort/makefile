CXX = g++

PROG     = test_sort
CPPFLAGS = -std=c++11 -g
OBJS     = test_sort.o

$(PROG) : $(OBJS)
	$(CXX) -o $(PROG) $(OBJS) $(CPPFLAGS)

clean   :
	rm $(PROG) $(OBJS)

test_sort.o : test_sort.cpp sort.h
	$(CXX) -c -o test_sort.o test_sort.cpp $(CPPFLAGS)
