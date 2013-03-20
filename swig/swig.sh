#!/bin/sh -x
PACKAGE=com.inria.soctrace.tools.paje.lpaggreg.jni 
OUTDIR=/home/dosimont/Documents/forge/generoso/soctrace/source/trunk/workspace/com.inria.soctrace.tools.paje.lpaggreg/src/com/inria/soctrace/tools/paje/lpaggreg/jni
cp lpaggreg.i ../src/
cd ../src
swig -c++ -java -package $PACKAGE -outdir $OUTDIR lpaggreg.i
cd -
mv ../src/lpaggreg.i .

exit 0
