#!/bin/sh -x
PACKAGE=com.inria.soctrace.tools.paje.lpaggreg.core.jni 
OUTDIR=/home/dosimont/Documents/forge/generoso/soctrace/source/trunk/workspace/com.inria.soctrace.tools.paje.lpaggreg.core/src/com/inria/soctrace/tools/paje/lpaggreg/core/jni
cp lpaggreg.i ../src/
cd ../src
swig -c++ -java -package $PACKAGE -outdir $OUTDIR lpaggreg.i
cd -
mv ../src/lpaggreg.i .

exit 0
