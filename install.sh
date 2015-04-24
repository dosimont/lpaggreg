#!/bin/bash -x
OBJ=lpaggreg
DIR=$2
if [ ! -d $1 ] 
then
echo "No procedure found to install this library".
exit 3
elif [[ "$1" =~ "win" ]]
then
echo "Windows library installation is not supported. Please install it manually".
exit 1
elif [[ "$1" =~ "static" ]]
then
LIB=lib${OBJ}.a
elif [[ "$1" =~ "shared" ]]
then
LIB=lib${OBJ}.so
else
echo "No procedure found to install this library".
exit 2
fi
VERSION=$1
cd $VERSION
LSLIB=`ls ${LIB}*`
cd ..
rm $DIR/$LIB
cp $VERSION/$LSLIB $DIR
ln -s $DIR/$LSLIB $DIR/$LIB
mkdir -p $3/$OBJ
cp src/*.h $3/$OBJ
if [[ "$4" =~ "ldconfig" ]]
then
echo $2 > /etc/ld.so.conf.d/$OBJ.conf
ldconfig
fi
exit 0
