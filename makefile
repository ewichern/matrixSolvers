OUTPUTNAME=matrixSolver
TARGET=$(OUTPUTNAME)
DEBUGTARGET=testMatrixSolver

CPPS=IterativeSolvers.cpp directSolvers.cpp matrixGenerator.cpp \
	rootSolvers.cpp monomial.cpp
TESTS=googleTestsMain.cc test_denseMatrix.cc test_matrixGenerator.cc \
	 test_iterativeSolvers.cc \
	 test_directSolvers.cc \
	 test_rootSolvers.cc \
	 test_monomial.cc \
	test_matrixSolver.cc \
	./gtest/gtest-all.cc \
	# test_sparseMatrix.cc
#DIR=$(PWD)
DISTR=Unix
#INCLUDES=/home/erik/libraries/

#
#	Macro Definitions:
#

CPPFLAGS=-std=c++0x -I$(INCLUDES) -Wall -Wextra -fmessage-length=0
CCFLAGS=-std=c++0x -I$(INCLUDES) -Og -ggdb3 -Wall -Wextra -fmessage-length=0
CFLAGS=-g

LINK=g++ $(LFLAGS)
LFLAGS=-lpthread

#
# Implicit Rules
#
.SUFFIXES: .d .o .h .c .cc .C .cpp
.cc.o:
	$(CC) $(CCFLAGS) -MMD -o $@ -c $<
.cpp.o:
	$(CPP) $(CPPFLAGS) -MMD -o $@ -c $<

CC=g++
CPP=g++

OBJS=$(CPPS:%.cpp=%.o)
DEPENDENCIES=$(CPPS:%.cpp=%.d)

%.d: %.cpp
	touch $@
	
%.o: %.cpp
	$(CPP) $(CPPFLAGS) -MMD -o $@ -c $*.cpp

TESTOBJS=$(TESTS:%.cc=%.o)
TESTDEPENDENCIES=$(TESTS:%.cc=%.d)

%.d: %.cc
	touch $@
	
%.o: %.cc
	$(CPP) $(CCFLAGS) -MMD -o $@ -c $*.cc


#
#	Targets:
#
all: clean release

$(TARGET): $(OBJS) solversDriver.o
	$(LINK) -o $(TARGET) $(OBJS) solversDriver.o $(LFLAGS)

$(DEBUGTARGET): $(TESTOBJS) $(OBJS)
	$(LINK) -o $(DEBUGTARGET) $(TESTOBJS) $(OBJS) $(LFLAGS)

release: CPPFLAGS += -O3 -g0
release: $(TARGET)

debug: CPPFLAGS += -Og -ggdb3
debug: $(DEBUGTARGET) 

gcov: CPPFLAGS += -fprofile-arcs -ftest-coverage
gcov: LFLAGS += -lgcov -coverage
gcov: debug

solversDriver.o: matrixSolver.cpp
	$(CPP) $(CPPFLAGS) -MMD -o $@ -c solversDriver.cpp

matrixSolver.cpp:
	echo "Do nothing directly to matrixSolver.cpp"

clean:
	-rm -f $(TARGET) $(OBJS) $(DEPENDENCIES) make.dep 
	-rm -f $(DEBUGTARGET) $(TESTOBJS) $(TESTDEPENDENCIES) tests.dep
	-rm -f solversDriver.o solversDriver.d
	-rm -f unitTest*
	-rm -f *.gcov
	-rm -f *.gcda
	-rm -f *.gcno

test: test.o matrixGenerator.o rootSolvers.o monomial.o
	$(LINK) -o $@ test.o matrixGenerator.o rootSolvers.o monomial.o

test.o: test.cpp
	$(CPP) $(CPPFLAGS) -MMD -o $@ -c test.cpp

make.dep: $(DEPENDENCIES)
	-cat $(DEPENDENCIES) > $@
	
tests.dep: $(TESTDEPENDENCIES)
	-cat $(TESTDEPENDENCIES) > $@

include make.dep
include tests.dep
