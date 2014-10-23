########################################################
# GMZ: Generic Makefile
########################################################
# Variables

# C++ compiler
#CXX      := clang++
CXX      := g++

# C++ compiler flags
CXXFLAGS := -g -Wall -std=c++11

# Linker; for C++ should be $(CXX)
LINK     := $(CXX)

# Linker flags
LDFLAGS  := 

# Libraries we're using, prefaced with "-l"
LDLIBS   := -lfl

#############################################################
# Rules

% : %.o
	$(LINK) $(LDFLAGS) $^ -o $@ $(LDLIBS)

%.o : %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

%.cc : %.l
	flex --nounput -o $@ $<

%.cc : %.yy
	bison -dv $< -o $@

CMinDriver : CMinDriver.o CMinParser.o CMinLexer.o

#############################################################

.PHONY : clean
clean :
	$(RM) a.out core
	$(RM) *.o *.d *~ *.hh *.output
	$(RM) CMinParser.cc CMinDriver

#############################################################
