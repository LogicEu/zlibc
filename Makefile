# zlibc makefile

STD=-std=c89 -nostdlib -fno-stack-protector
WFLAGS=-Wall -Wextra
OPT=-O2
IDIR=-Isrc/include
CC=gcc
NAME=libzlibc
SRC=src/*.c

OS=$(shell uname -s)

ifeq ($(OS),Darwin)
	OSFLAGS=-dynamiclib -lSystem
	LIB=$(NAME).dylib
else
	OSFLAGS=-shared -fPIC
	LIB=$(NAME).so
endif

CFLAGS=$(STD) $(WFLAGS) $(OPT) $(IDIR)

$(NAME).a: $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) && ar -cr $(NAME).a *.o && rm *.o

shared: $(SRC)
	$(CC) -o $(LIB) $(SRC) $(CFLAGS) $(OSFLAGS)

clean: build.sh
	./$^ $@

install: build.sh
	./$^ $@

uninstall: build.sh
	./$^ $@
