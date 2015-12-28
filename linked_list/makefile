CXX = g++

PROG = test_linkedlist.out
CPPFLAGS = -std=c++11 -Wall -g
OBJS = test_linkedlist.o
# HDRS = linkedlist.h
# SRCS = test_linkedlist.cpp

$(PROG) : $(OBJS)
	$(CXX) -o $(PROG) $(OBJS) $(CPPFLAGS)

clean :
	rm $(PROG) $(OBJS)

test_linkedlist.o : test_linkedlist.cpp linkedlist.h
	$(CXX) -c -o test_linkedlist.o test_linkedlist.cpp $(CPPFLAGS)


# single file project
# .cpp:
# 	$(CXX) $(CPPFLAGS) $@.cpp $() -o $@
