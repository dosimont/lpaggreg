#!/bin/bash -x
LIB=liblpaggreg.so
cd Release
LSLIB=`ls ${LIB}*`
cd ..
DIR=/usr/lib
rm $DIR/$LIB
cp Release/$LSLIB $DIR
ln -s $DIR/$LSLIB $DIR/$LIB
mkdir -p /usr/include/lpaggreg
cp src/*.h /usr/include/lpaggreg
echo "/usr/lib/" > /etc/ld.so.conf.d/lpaggreg.conf
ldconfig
exit 0
