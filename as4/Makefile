########################################################
# MMF: Assignment 4 Makefile
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

PascalDriver : PascalDriver.o PascalLexer.o
CMinLexerDriver : CMinLexerDriver.o CMinParser.o

#############################################################

.PHONY : clean
clean :
	$(RM) a.out core
	$(RM) *.o *.d *~
	$(RM) LineCount PascalDriver Username \
		WordCount WordCount1Line WordCountOrig \
		CMinParser CMinLexerDriver

#############################################################
