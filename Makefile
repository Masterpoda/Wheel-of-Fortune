SOURCE = gameboard.cpp \
         game.cpp \
         spinButton.cpp\
         newButton.cpp\
         globals.cpp \
         graphics.cpp \
         guessgrid.cpp \
         loadBMP.cpp \
         main.cpp \
         mouse.cpp \
         tile.cpp \
         util.cpp
OBJS = $(SOURCE:.cpp=.o)

#GNU C/C++ Compiler
GCC = g++

# GNU C/C++ Linker
LINK = g++

# Compiler flags
CFLAGS = -Wall -O -std=c++11 -c
CXXFLAGS = $(CFLAGS)

# Fill in special libraries needed here
LIBS = -lglut -lGLU -lGL -lm

.PHONY: clean

# Targets include all, clean, debug, tar

all : main

main: $(OBJS)
	$(LINK) -o $@ $^ $(LIBS)

clean:
	rm -rf errors.txt *.o *.d *.tgz core main


debug: CXXFLAGS += -DDEBUG -g
debug: main

tar:
	tar cvf - *.cpp *.h Makefile *.dat Letters/ | gzip > main_Tarball.tgz 

help:
	@echo "	make main  - same as make all"
	@echo "	make all   - builds the main target"
	@echo "	make       - same as make all"
	@echo "	make clean - remove .o .d core main"
	@echo "	make debug - make all with -g and -DDEBUG"
	@echo "	make tar   - make a tarball of .cpp and .h files"
	@echo "	make help  - this message"

%.d: %.cpp
	@set -e; /usr/bin/rm -rf $@;$(GCC) -MM $< $(CXXFLAGS) > $@

