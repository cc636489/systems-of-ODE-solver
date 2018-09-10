MAINSRCDIR = ./src/main
FUNCSRCDIR = ./src/func
INCDIR = ./header

CFLAGS   = 
CPPFLAGS = -std=c++11 -Wall -Wextra -I $(INCDIR)
LDFLAGS  = -lgsl -lgslcblas -g -DDEBUG 
LIBS     = -I$(TACC_GSL_INC) -L$(TACC_GSL_LIB)
CXX      = g++

vpath %.h $(INCDIR)
vpath %.cpp $(MAINSRCDIR) $(FUNCSRCDIR)

#USERSOURCES = ODEdriver.cpp readinput.cpp solver.cpp solver_explicit_euler.cpp solver_runga_katta.cpp writeoutput.cpp
#USERHEADERS = readinput.h solver.h solver_explicit_euler.h solver_runga_katta.h writeoutput.h
TEST1PRE = test1_solver_explicit_euler.cpp solver_explicit_euler.cpp solver_explicit_euler.h
TEST2PRE = test2_solver_runga_katta.cpp solver_runga_katta.cpp solver_runga_katta.h
OUTPUT  = ODEdriver

all: $(OUTPUT)
.PHONY: all

MAIN  := $(shell find $(MAINSRCDIR) -name ODEdriver.cpp)
TEST1 := $(shell find $(MAINSRCDIR) -name test1_solver_explicit_euler.cpp)
TEST2 := $(shell find $(MAINSRCDIR) -name test2_solver_runga_katta.cpp)
FUNCSOURCES := $(shell find $(FUNCSRCDIR) -name *.cpp) 
HEADERS := $(shell find $(INCDIR) -name *.h)

$(OUTPUT): $(MAIN) $(FUNCSOURCES) $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

test1_solver: $(TEST1) $(FUNCSOURCES) $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)

test2_solver: $(TEST2) $(FUNCSOURCES) $(HEADERS)
	$(CXX) $(CPPFLAGS) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LIBS)


debug: LDFLAGS += -DDEBUG -g
debug: $(OUTPUT)


check: test

test: test1_solver test2_solver
	./test1_solver
	./test2_solver


coverage: CPPFLAGS += --coverage  -fprofile-arcs -ftest-coverage -lgcov -g -O0
coverage: LDFLAGS += -lgcov -g -O0
coverage: LIBS += -lgcov -g -O0
#-prof-gen=srcpos -prof_use
coverage: test1_solver test2_solver
	./test1_solver
	./test2_solver
#	codecov -prj chen_project -spi pgopti.spi -dpi pgopti.dpi

.PHONY: clean
clean:
	rm -f $(OUTPUT) test1_solver test2_solver
