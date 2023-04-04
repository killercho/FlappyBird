OBJS	= pilons.o main.o
SOURCE	= pilons.cpp main.cpp
HEADER	= pilons.hpp constants.hpp
SOURCE_FOLDER = source
HEADER_FOLDER = headers
OBJ_FOLDER = objs
OUT	= game.out
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = -l raylib

.PHONY : all build remove_objs clean

all: build remove_objs

build: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

pilons.o: $(SOURCE_FOLDER)/pilons.cpp
	$(CC) $(FLAGS) $(SOURCE_FOLDER)/pilons.cpp

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

remove_objs:
	rm -f $(OBJS)

clean:
	rm -f $(OUT)
