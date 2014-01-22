#!/bin/sh -x
LIB=liblpaggreg.so
cd Release
LSLIB=`ls ${LIB}*`
cd ..
DIR=/usr/lib
rm $DIR/$LIB
cp Release/$LSLIB $DIR
ln -s $DIR/$LSLIB $DIR/$LIB
cp src/*.h /usr/include/
exit 0
