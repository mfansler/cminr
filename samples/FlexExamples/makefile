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

# $(LDLIBS) is used for link libraries
LDLIBS   = -lfl

##

# Some convenient pattern rules

%   : %.o
	$(CXX) $(LDFLAGS) $< -o $@ $(LDLIBS)

%.o : %.cc 
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

%.cc : %.l
	flex -o$@ $<

.PHONY: clean
clean :
	-rm -f *.o
