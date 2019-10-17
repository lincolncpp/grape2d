OBJS = $(wildcard *.cpp)
INCLUDES = $(wildcard *.h)
CC = g++
CFLAGS=-Wall -std=c++11
OBJ_NAME = test

ifeq ($(OS),Windows_NT)
	CFLAGS += -Wl,-subsystem,windows
	LINKER_FLAGS = -lmingw32 -lgrape2d -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
	INCLUDE_PATHS = -I$(LOCALAPPDATA)\grape2d\include
	LIBRARY_PATHS = -L$(LOCALAPPDATA)\grape2d\lib
else
	LINKER_FLAGS = -lgrape2d -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
	INCLUDE_PATHS = -I\usr\local\include
	LIBRARY_PATHS = -L\usr\local\lib
endif

all : $(OBJS) $(INCLUDES)
	$(CC) $(OBJS) $(LIBRARY_PATHS) $(INCLUDE_PATHS) $(CFLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
