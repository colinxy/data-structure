CXX = g++

PROG 	 = test_seg_tree.out
CPPFLAGS = -std=c++11 -g
OBJS	 = test_seg_tree.o seg_tree.o

$(PROG) : $(OBJS)
	$(CXX) -o $(PROG) $(OBJS) $(CPPFLAGS)

clean   :
	rm $(PROG) $(OBJS)

test_seg_tree.o : test_seg_tree.cpp seg_tree.h
	$(CXX) -c -o test_seg_tree.o test_seg_tree.cpp $(CPPFLAGS)

seg_tree.o		: seg_tree.cpp seg_tree.h
	$(CXX) -c -o seg_tree.o seg_tree.cpp $(CPPFLAGS)
