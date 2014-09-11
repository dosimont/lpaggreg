#!/bin/bash -x
DIR=/usr/lib
OBJ=lpaggreg
ALIB=lib${OBJ}.a
VERSION=Static
cd $VERSION
ALSLIB=`ls ${ALIB}*`
cd ..
rm $DIR/$ALIB
cp $VERSION/$ALSLIB $DIR
ln -s $DIR/$ALSLIB $DIR/$ALIB
mkdir -p /usr/include/$OBJ
cp src/*.h /usr/include/$OBJ
echo "/usr/lib/" > /etc/ld.so.conf.d/$OBJ.conf
ldconfig
exit 0
