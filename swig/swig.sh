#!/bin/sh -x
cp lpaggreg.i ../src/
cd ../src
swig -c++ -java -package com.inria.soctrace.tools.paje.lpaggreg.jni -outdir /home/dosimont/Documents/forge/generoso/soctrace/source/trunk/workspace/com.inria.soctrace.tools.paje.lpaggreg/src/com/inria/soctrace/tools/paje/lpaggreg/jni  lpaggreg.i
cd -
mv ../src/*.i .

exit 0
