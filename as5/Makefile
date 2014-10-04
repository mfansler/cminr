#######################OA###################A##############
#  Filename    : Makefile
#  Author      : Merv Fansler
#  Course      : CSCI 435
#  Assignment  : Assignment 5, C- Parser_1
#  Description : Build and clean commands for C- parser
#  Reference   : Modeled after example from G. Zoppetti 
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

CMinParser : CMinParser.o ../as4/CMinLexer.o

#############################################################

.PHONY : clean
clean :
	$(RM) a.out core
	$(RM) *.o *.d *~
	$(RM) CMinParser

#############################################################
