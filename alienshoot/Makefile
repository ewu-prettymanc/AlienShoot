EXE=game      
CC=g++
CFLAGS=-ggdb -Wall -pedantic -ansi $(shell sdl-config --cflags)
CXXFLAGS=$(CFLAGS)
LFLAGS= $(shell sdl-config --libs) -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer
SRCS:=$(wildcard *.cpp)
OBJS:=$(patsubst %.cpp,%.o,$(SRCS))
DEPS:=$(patsubst %.cpp,%.d,$(SRCS))

$(EXE): $(DEPS) $(OBJS)
	$(CC) -o $(EXE) $(OBJS) $(LFLAGS)

%.d: %.cpp
	$(CC) $(CFLAGS) -M $< > $@
	$(CC) $(CFLAGS) -M $< | sed s/\\.o/.d/ >> $@

clean:
	rm -f $(EXE) $(OBJS) $(DEPS)

val:
	valgrind --tool=memcheck --leak-check=yes ./$(EXE)

gdb:
	gdb ./$(EXE)


-include $(DEPS)
