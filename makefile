LIB=/usr/lib
INCLUDE=/usr/include

.PHONY: all shared-linux bench-linux static-linux static-linux-x86 static-win64 static-win32 openmp repo install install-bench install-shared install-static install-openmp installd clean

# All Target
all: shared-linux

shared-linux:
	(cd shared-linux; make)

bench-linux:
	(cd bench-linux; make)

static-linux:
	(cd static-linux; make)

static-linux-x86:
	(cd static-linux-x86; make)

static-win64:
	(cd static-win64; make)

static-win32:
	(cd static-win32; make)
	
openmp:
	(cd openmp; make)

repo:
	(cd ${DIR}; make)

install:	install-shared

install-shared:	shared-linux
	./install.sh shared-linux "${LIB}" "${INCLUDE}" ldconfig

install-bench:	bench-linux
	./install.sh bench-linux "${LIB}" "${INCLUDE}" ldconfig

install-static:	static-linux
	./install.sh static-linux "${LIB}" "${INCLUDE}" ldconfig
	
install-openmp: openmp
	./install.sh openmp "${LIB}" "${INCLUDE}" ldconfig

installd:
	./install.sh ${DIR} ${LIB} ${INCLUDE} ldconfig

clean:
	(cd shared-linux; rm *.so*; make clean)
	(cd bench-linux; rm *.so*; make clean)
	(cd static-linux; rm *.a*; make clean)
	(cd static-linux-x86; rm *.a*; make clean)
	(cd static-win64; rm *.a*; make clean)
	(cd static-win32; rm *.a*; make clean)
	(cd openmp; rm *.so*; make clean)

uninstall:
	rm -fr ${INCLUDE}/*lpaggreg*
	rm ${LIB}/*lpaggreg*
