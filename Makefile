# zlibc makefile

NAME = libzlibc

CC = gcc
STD = -std=c89
NOSTD = -nostdlib -fno-stack-protector
WFLAGS = -Wall -Wextra -pedantic
OPT = -O2

TESTDIR = tests
SRCDIR = src
TMPDIR = tmp
BINDIR = bin
INCDIR = src/include

LDIR = -Lbin -lzlibc
INC = -I$(INCDIR)
SRC = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(TMPDIR)/%.o,$(SRC))

OS=$(shell uname -s)
ifeq ($(OS),Darwin)
    DLIB = -dynamiclib
    LIBS = -lSystem
    CRT = -nostartfiles -e _start 
    SUFFIX = .dylib
else
    DLIB = -shared -fPIC
    LIBS = -lgcc -lc
    CRT = -nostartfiles -e start
    SUFFIX = .so
endif

SCRIPT = build.sh
CRTFILE = $(SRCDIR)/crt/crt0.c
TARGET = $(BINDIR)/$(NAME)
LIB = $(TARGET)$(SUFFIX)

CFLAGS = $(STD) $(WFLAGS) $(OPT) $(INC)

.PHONY: static shared all clean install uninstall

static: $(TARGET).a

shared: $(LIB)

all: $(LIB) $(TARGET).a

$(TESTDIR)/%.c: $(CRTFILE) $(TARGET).a
	$(CC) $@ $< $(CFLAGS) $(NOSTD) $(LDIR) $(LIBS) $(CRT)

$(LIB): $(BINDIR) $(OBJS)
	$(CC) $(OBJS) -o $@ $(NOSTD) $(LIBS) $(DLIB)

$(TARGET).a: $(BINDIR) $(OBJS)
	ar -cr $@ $(OBJS)

$(TMPDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJS): | $(TMPDIR)

$(TMPDIR):
	mkdir -p $@

$(BINDIR):
	mkdir -p $@

clean: $(SCRIPT)
	./$^ $@

install: $(SCRIPT)
	./$^ $@

uninstall: $(SCRIPT)
	./$^ $@

