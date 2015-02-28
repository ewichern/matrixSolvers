OUTPUTNAME=matrixSolver
CPPS=IterativeSolvers.cpp directSolvers.cpp matrixGenerator.cpp
TESTS=googleTestsMain.cc test_denseMatrix.cc test_matrixGenerator.cc \
	 test_iterativeSolvers.cc \
	 test_directSolvers.cc \
	test_matrixSolver.cc \
	./gtest/gtest-all.cc \
	# test_sparseMatrix.cc
#DIR=$(PWD)
DISTR=Unix
#INCLUDES=/home/erik/libraries/
TARGET=$(OUTPUTNAME)
DEBUGTARGET=testMatrixSolver

#
#	Macro Definitions:
#

CPPFLAGS=-std=c++0x -I$(INCLUDES) -O3 -g3 -Wall -Wextra -fmessage-length=0
CFLAGS=-g

LINK=g++ $(LFLAGS)
LFLAGS=-lpthread

#
# Implicit Rules
#
.SUFFIXES: .d .o .h .c .cc .C .cpp
.cc.o:
	$(CC) $(CPPFLAGS) -MMD -o $@ -c $<
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
	$(CPP) $(CPPFLAGS) -MMD -o $@ -c $*.cc


#
#	Targets:
#
all: debug release

$(TARGET): $(OBJS) solversDriver.o
	$(LINK) -o $(TARGET) $(OBJS) solversDriver.o $(LFLAGS)

$(DEBUGTARGET): $(TESTOBJS) $(OBJS) 
	$(LINK) -o $(DEBUGTARGET) $(TESTOBJS) $(OBJS) $(LFLAGS)

release: $(TARGET)
	
debug: $(DEBUGTARGET) 

solversDriver.o: matrixSolver.cpp
	$(CPP) $(CPPFLAGS) -MMD -o $@ -c solversDriver.cpp

matrixSolver.cpp:
	echo "Do nothing directly to matrixSolver.cpp"

clean:
	-rm -f $(TARGET) $(OBJS) $(DEPENDENCIES) make.dep 
	-rm -f $(DEBUGTARGET) $(TESTOBJS) $(TESTDEPENDENCIES) tests.dep
	-rm -f solversDriver.o solversDriver.d

make.dep: $(DEPENDENCIES)
	-cat $(DEPENDENCIES) > $@
	
tests.dep: $(TESTDEPENDENCIES)
	-cat $(TESTDEPENDENCIES) > $@

include make.dep
include tests.dep
