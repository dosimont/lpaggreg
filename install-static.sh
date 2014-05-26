#!/bin/bash -x
DIR=/usr/lib
ALIB=liblpaggreg.a
cd Static
ALSLIB=`ls ${ALIB}*`
cd ..
rm $DIR/$ALIB
cp Static/$ALSLIB $DIR
ln -s $DIR/$ALSLIB $DIR/$ALIB
mkdir -p /usr/include/lpaggreg
cp src/*.h /usr/include/lpaggreg
echo "/usr/lib/" > /etc/ld.so.conf.d/lpaggreg.conf
ldconfig
exit 0
