CXX = g++

PROG     = test_sort.out
CPPFLAGS = -std=c++11 -Wall -Wextra \
           -Wno-sign-compare -Werror=return-type \
           -fsanitize=address -fno-omit-frame-pointer
OBJS     = test_sort.o

$(PROG) : $(OBJS)
	$(CXX) -o $(PROG) $(OBJS) $(CPPFLAGS)

clean   :
	rm $(PROG) $(OBJS)

test_sort.o : test_sort.cpp sort.h
	$(CXX) -c -o test_sort.o test_sort.cpp $(CPPFLAGS)
