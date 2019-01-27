# Makefile for Linux
PREFIX=/usr/local
CC=g++
CFLAGS=-I. -Wall
LIBNAME=libgrape2d.a
INCLUDE=grape2d.h

SRC=$(wildcard src/*.cpp)
OBJ=$(patsubst src/%.cpp, build/%.o, $(SRC))

# Targets
all: prereqs $(LIBNAME)
	@rm build/*.o

prereqs:
	@mkdir -p build

$(LIBNAME): $(OBJ)
	@ar rcs build/$@ $^
	@echo "> $(LIBNAME) was generated!"

build/%.o: src/%.cpp include/$(INCLUDE)
	@$(CC) -o $@ -c $< $(CFLAGS)
	@echo "> Build: $@"

.PHONY: clean install uninstall rebuild
clean:
	@rm -rf build/*
	@echo "> Cleaned!"

install:
	@mkdir -p $(PREFIX)/include/
	@mkdir -p $(PREFIX)/lib/
	@cp include/$(INCLUDE)  $(PREFIX)/include/
	@cp build/$(LIBNAME) $(PREFIX)/lib/
	@echo "> Grape2D has been installed!"

uninstall:
	@rm -f $(PREFIX)/include/$(INCLUDE)
	@rm -f $(PREFIX)/lib/$(LIBNAME)
	@echo "> Uninstalled!"

rebuild: uninstall clean all install
