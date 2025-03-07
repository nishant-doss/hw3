CXX := g++
CXXFLAGS := -g -Wall --std=c++11
VALGRIND := valgrind --tool=memcheck --leak-check=yes

all: llrec-test stack-test

#-----------------------------------------------------
# Target to build your llrec-test executable
#-----------------------------------------------------
llrec-test: llrec-test.cpp llrec.cpp llrec.h
	$(CXX) $(CXXFLAGS) llrec-test.cpp llrec.cpp -o llrec-test

#-----------------------------------------------------
# Target to build your stack-test executable
#-----------------------------------------------------
stack-test: stack_test.cpp stack.h
	$(CXX) $(CXXFLAGS) stack_test.cpp -o stack-test

clean:
	rm -f *.o rh llrec-test stack-test *~

.PHONY: clean all