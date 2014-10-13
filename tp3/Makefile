# -------------------------------------------
# Makefile to compile the project of PJE.
# The program was written in C++
# The GNU compiler is utilised.
# The OpenCV Library is utilised.
#
# Author: gaetan.deflandre@gmail.com
# Date	: 2014-10-13
# -------------------------------------------

CPPC      = g++
CPPFLAGS  = -Wall -Werror -ansi -pedantic -std=c++11
CPPFLAGS += -D_XOPEN_SOURCE=500
CPPFLAGS += -DDEBUG
CPPFLAGS += -g
CPPFLAGS += `pkg-config opencv --cflags`

LFLAGS = `pkg-config opencv --libs`

BINARIES = lecture ponctuelle
OBJECTS  = lecture.o ponctuelle.o


all 	: $(BINARIES) $(OBJECTS)

# -------------------------------------------
# This line is for Makefly check
check-syntax:
	g++ -o nul -Wall -std=c++0x -S ${CHK_SOURCES} $(CPPFLAGS)
# -------------------------------------------

###------------------------------
### Entries
###------------------------------------------------------------
lecture: lecture.o
	$(CPPC) -o $@ $^ $(LFLAGS)

ponctuelle: ponctuelle.o
	$(CPPC) -o $@ $^ $(LFLAGS)


###------------------------------
### Dependencies
###------------------------------------------------------------
lecture.o: lecture.cpp 
	$(CPPC) -c $^ $(CPPFLAGS)

ponctuelle.o: ponctuelle.cpp 
	$(CPPC) -c $^ $(CPPFLAGS)




###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean
clean:
	$(RM) $(OBJECTS)

realclean: clean 
	$(RM) $(BINARIES) $(TRASHFILES) \#*\# *~ nul *.gch
