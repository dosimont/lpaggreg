#!/bin/bash -x
OBJ=benchlpaggreg
DIR=/usr/lib
SLIB=lib${OBJ}.so
VERSION=Bench
cd $VERSION
LSLIB=`ls ${SLIB}*`
cd ..
rm $DIR/$SLIB
cp $VERSION/$LSLIB $DIR
ln -s $DIR/$LSLIB $DIR/$SLIB
mkdir -p /usr/include/$OBJ
cp src/*.h /usr/include/$OBJ
echo "/usr/lib/" > /etc/ld.so.conf.d/$OBJ.conf
ldconfig
exit 0
