#!/bin/sh

# Just some compiler flags for compiling own Rivet analyses
CFLAGS=$(echo $(${ROOTSYS}/bin/root-config --cflags) )
CFLAGS+=" -fPIC -Wall -Wno-reorder"
LIBS=$(echo $(${ROOTSYS}/bin/root-config --libs) )
LIBS+=" -lTreePlayer -lmapDict -lvectorDict"

# Compile your own Rivet analysis
if [ $1 = 'build' ]
    then 
    rivet-buildplugin Rivet${2}.so ${2}.cc -m64 ${CFLAGS} ${LIBS}
fi

# Run over data samples
if [ $1 = 'run' ]
    then
    athena.py $2
fi
