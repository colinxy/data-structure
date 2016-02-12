CXX = g++

PROG     = test_queue.out
CPPFLAGS = -std=c++11 -Wall -Wextra \
           -Wno-sign-compare -Werror=return-type \
           -fsanitize=address -fno-omit-frame-pointer
OBJS     = test_queue.o queue.o

$(PROG) : $(OBJS)
	$(CXX) -o $(PROG) $(OBJS) $(CPPFLAGS)

clean   :
	rm $(PROG) $(OBJS)

test_queue.o : test_queue.cpp queue.h
	$(CXX) -c -o test_queue.o test_queue.cpp $(CPPFLAGS)

queue.o      : queue.cpp queue.h
	$(CXX) -c -o queue.o queue.cpp $(CPPFLAGS)
