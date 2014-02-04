#!/bin/bash -x
LIB=liblpaggreg.so
cd Release
LSLIB=`ls ${LIB}*`
cd ..
DIR=/usr/lib
rm $DIR/$LIB
cp Release/$LSLIB $DIR
ln -s $DIR/$LSLIB $DIR/$LIB
mkdir /usr/include/lpaggreg
cp src/*.h /usr/include/lpaggreg
ldconfig -n /usr/lib
exit 0
