#D Fouche
#UCT CS3
#FCHDYL001

CC = g++
FLAGS = -std=c++11
INC = -I include -I src

SRCDIR = src
TESTDIR = test
BUILDDIR = build
BINDIR = bin

#the name of our target executable
EXE = samp
#the name of our test source file
TESTSRC = tests
#the name of the file where we have our main method
DRIVER = driver

SOURCES = $(shell find $(SRCDIR) -type f -name *.cpp)
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cpp=.o))
TESTOBJECTS = $(filter-out $(BUILDDIR)/$(DRIVER).o,$(OBJECTS))

#rule for linking
$(EXE): $(OBJECTS)
	$(CC) $^ -o $(BINDIR)/$(EXE)

#rule for compiling
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(FLAGS) $(INC) -c $< -o $@

#delete all object files
clean:
	rm -f $(BUILDDIR)/*.o

#deletes all object files and executables
nuke:
	rm -f $(BINDIR)/$(EXE)
	rm -f $(BINDIR)/$(TESTSRC)
	rm -f $(BUILDDIR)/*.o

#run the driver executable
run:
	./$(BINDIR)/$(EXE) $(ARGV)

#run test cases
test:	FORCE
	$(CC) $(FLAGS) $(INC) -c $(TESTDIR)/$(TESTSRC).cpp -o $(BUILDDIR)/$(TESTSRC).o -w
	$(CC) $(FLAGS)  $(BUILDDIR)/$(TESTSRC).o $(TESTOBJECTS) -o $(BINDIR)/$(TESTSRC)
	rm -f ./$(BUILDDIR)/$(TESTSRC).o
	./$(BINDIR)/$(TESTSRC)

FORCE:
