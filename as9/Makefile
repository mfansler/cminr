#######################OA###################A##############
#  Filename    : Makefile
#  Author      : Merv Fansler
#  Course      : CSCI 435
#  Assignment  : Assignment 8, C- Parser_2
#  Description : Build and clean commands for C- parser
#  Reference   : Modeled after example from G. Zoppetti 
########################################################
# Variables

# C++ compiler
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

CMinDriver : CMinDriver.o CMinParser.o CMinLexer.o CMinusAst.or

#############################################################

.PHONY : cleanC
clean :
	$(RM) a.out core
	$(RM) *.o *.d *~ *.hh *.output
	$(RM) CMinParser.cc CMinDriver


#############################################################
