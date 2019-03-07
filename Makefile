# Makefile for Linux and Windows (MingW)
CC=g++
CFLAGS=-Wall -std=c++11
LIBNAME=libgrape2d.a
INCLUDE=grape2d.h

# Detecting OS
ifeq ($(OS), Windows_NT)
	PLATFORM=MingW
	PREFIX=$(LOCALAPPDATA)\grape2d
else
	PLATFORM=$(shell uname -s)
	PREFIX=/usr/local
endif

SRC=$(wildcard src/*.cpp)
OBJ=$(patsubst src/%.cpp, build/%.o, $(SRC))

define proc
	@printf "[\x1b[1;33mGrape2D\033[0m]\x1b[1;37m $(1)\033[0m\n"
endef

# Targets
all: prereqs $(LIBNAME)
	@rm build/*.o

prereqs:
	$(call proc,Building objetcs ...)
	@mkdir -p build

$(LIBNAME): $(OBJ)
	$(call proc,Compiling library ...)
	ar rcs build/$@ $^
	$(call proc,$(LIBNAME) has been generated!)

build/%.o: src/%.cpp include/$(INCLUDE)
	$(CC) -o $@ -c $< $(CFLAGS)

.PHONY: clean install uninstall rebuild
clean:
	@rm -rf build/*
	$(call proc,Cleaned!)

install:
	@mkdir -p $(PREFIX)/include/
	@mkdir -p $(PREFIX)/lib/
	@cp include/$(INCLUDE)  $(PREFIX)/include/
	@cp build/$(LIBNAME) $(PREFIX)/lib/
	$(call proc,Grape2D has been installed!)
ifeq ($(PLATFORM),MingW)
	$(call proc,Include path: \x1b[1;32m$(PREFIX)\include)
	$(call proc,Library path: \x1b[1;32m$(PREFIX)\lib)
endif

uninstall:
	@rm -f $(PREFIX)/include/$(INCLUDE)
	@rm -f $(PREFIX)/lib/$(LIBNAME)
	$(call proc,Uninstalled!)

rebuild: uninstall clean all install
