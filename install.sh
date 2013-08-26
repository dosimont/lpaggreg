#!/bin/sh -x
LIB=liblpaggreg.so
cd Release
LSLIB=`ls ${LIB}*`
cd ..
DIR=/usr/lib
sudo rm $DIR/$LIB
sudo cp Release/$LSLIB $DIR
sudo ln -s $DIR/$LSLIB $DIR/$LIB
sudo cp src/*.h /usr/include/
exit 0
