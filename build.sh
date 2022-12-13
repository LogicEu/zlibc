#!/bin/bash

cc=gcc
src=src/*.c
name=libzlibc

flags=(
    -std=c89
    -nostdlib
    -fno-stack-protector
    -Wall
    -Wextra
    -pedantic
    -O2
    -Isrc/include
)

comp() {
    echo "$@" && $@
}

shared() {
    if echo "$OSTYPE" | grep -q "darwin"; then
        comp $cc ${flags[*]} -dynamiclib -lSystem $src -o $name.dylib
    elif echo "$OSTYPE" | grep -q "linux"; then
        comp $cc -shared ${flags[*]} -fPIC $src -o $name.so 
    else
        echo "This OS is not supported by this shell script yet..." && exit
    fi
}

static() {
    comp $cc ${flags[*]} $arg ${inc[*]} -c $src && ar -cr $name.a *.o && rm *.o
}

cleanf() {
    [ -f $1 ] && rm $1 && echo "deleted $1"
}

clean() {
    cleanf $name.a
    cleanf $name.so
    cleanf $name.dylib
    return 0
}

install() {
    [ "$EUID" -ne 0 ] && echo "Run with sudo to install" && exit
    
    shared && static
    cp utopia.h /usr/local/include

    [ -f $name.a ] && mv $name.a /usr/local/lib
    [ -f $name.so ] && mv $name.so /usr/local/lib
    [ -f $name.dylib ] && mv $name.dylib /usr/local/lib
    
    echo "Successfully installed $name"
    return 0
}

uninstall() {
    [ "$EUID" -ne 0 ] && echo "Run with sudo to uninstall" && exit

    cleanf /usr/local/include/utopia.h
    cleanf /usr/local/lib/$name.a
    cleanf /usr/local/lib/$name.so
    cleanf /usr/local/lib/$name.dylib

    echo "Successfully uninstalled $name."
    return 0
}

case "$1" in
    "shared")
        shared;;
    "static")
        static;;
    "clean")
        clean;;
    "install")
        install;;
    "uninstall")
        uninstall;;
    *)
        echo "Run with 'shared' or 'static' to build."
        echo "Use 'install' to build and install in /usr/local."
        echo "Use 'clean' to remove local builds."
esac
