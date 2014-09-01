##
# Dr. Zoppetti
# Makefile
##

# Compiler
CXX      = g++44      

# Extra flags for C++ compiler
CXXFLAGS = -g  

# $(CC) is used for linking
CC       = g++44 

##

WordCount : WordCount.cc -lfl

WordCount.cc : WordCount.l
	flex -o$@ $<

PascalDriver : PascalDriver.o PascalLexer.o -lfl

PascalLexer.cc : PascalLexer.l
	flex -o$@ $<

##

# Return source dir. to clean slate (remove generated files)
.PHONY: clean
clean:
	-rm WordCount WordCount.cc PascalDriver PascalLexer.cc
