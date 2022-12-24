#!/bin/bash

cc=gcc
src=src/*.c
name=libzlibc
nostd=-nostdlib

flags=(
    -std=c89
    -Wall
    -Wextra
    -pedantic
    -Isrc/include
)

opt=(
    -O2
    -fno-stack-protector
)

crt=(
    -nostartfiles
    -e
)

if echo "$OSTYPE" | grep -q "darwin"; then
    libs=(
        -lSystem
    )
    dlib=(
        -dynamiclib
    )
    entry=_start
    suffix=.dylib
elif echo "$OSTYPE" | grep -q "linux"; then
    libs=(
        -lc 
        -lgcc
    )
    dlib=(
        -shared
        -fPIC
    )
    entry=start
    suffix=.so
else
    echo "This OS is not supported by this shell script yet..." && exit
fi

comp() {
    echo "$@" && $@
}

shared() {
    mkdir -p tmp
    comp $cc -c $src ${flags[*]} ${opt[*]} && mv *.o tmp/ || exit
    
    mkdir -p bin
    comp $cc tmp/*.o -o bin/$name$suffix $nostd ${opt[*]} ${libs[*]} ${dlib[*]}
}

exe() {
    comp $cc $1 src/crt/crt0.c ${flags[*]} ${opt[*]} $nostd ${crt[*]} $entry -Lbin -lzlibc ${libs[*]}
}

static() {
    mkdir -p tmp
    comp $cc -c $src ${flags[*]} ${opt[*]} && mv *.o tmp/ || exit
    
    mkdir -p bin
    ar -cr bin/$name.a tmp/*.o
}

cleand() {
    [ -d $1 ] && rm -r $1 && echo "deleted $1"
}

cleanf() {
    [ -f $1 ] && rm $1 && echo "deleted $1"
}

clean() {
    cleanf a.out
    cleand bin
    cleand tmp
    return 0
}

install() {
    [ "$EUID" -ne 0 ] && echo "Run with sudo to install" && exit
    
    make all -j
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

if [[ $# -eq 0 ]]; then
    echo "Run with 'shared' or 'static' to build."
    echo "Use 'install' to build and install in /usr/local."
    echo "Use 'clean' to remove local builds."
    exit
fi

case "$1" in
    "shared")
        shared;;
    "static")
        static;;
    "all")
        static && shared;;
    "make")
        make all -j;;
    "clean")
        clean;;
    "install")
        install;;
    "uninstall")
        uninstall;;
    *)
        for arg in $@
        do
            [ -f $arg ] && exe $arg || echo "File not found '$arg'"
        done;;
esac
