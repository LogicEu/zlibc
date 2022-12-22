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

CRT = -Lbin -lzlibc
INC = -I$(INCDIR)
SRC = $(wildcard $(SRCDIR)/*.c)
OBJS = $(patsubst $(SRCDIR)/%.c,$(TMPDIR)/%.o,$(SRC))

OS=$(shell uname -s)
ifeq ($(OS),Darwin)
    DLIB = -dynamiclib
    LIBS = -lSystem
    CRT += -e _start 
    SUFFIX = .dylib
else
    DLIB = -shared -fPIC -lgcc -lc
    LIBS = -lgcc -lc
    CRT += -e start
    SUFFIX = .so
endif

CRTFILE = $(SRCDIR)/crt/crt0.c
SCRIPT = build.sh
TARGET = $(BINDIR)/$(NAME)
LIB = $(TARGET)$(SUFFIX)

CFLAGS = $(STD) $(WFLAGS) $(OPT) $(INC)

$(TARGET).a: $(BINDIR) $(OBJS)
	ar -cr $@ $(OBJS)

.PHONY: shared all clean install uninstall

$(TESTDIR)/%.c: $(CRTFILE) $(LIB)
	$(CC) $(CFLAGS) $(NOSTD) $(LIBS) $(CRT) $@ $<

shared: $(LIB)

all: $(LIB) $(TARGET).a

$(LIB): $(BINDIR) $(OBJS)
	$(CC) $(NOSTD) $(LIBS) $(DLIB) -o $@ $(OBJS)

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

