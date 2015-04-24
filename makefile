$(LIB)="/usr/lib/"
$(INCLUDE)="/usr/include/"


# All Target
all: shared-linux

shared-linux:
	$(eval DIR := share-linux)
	(cd ${DIR}; make)

bench-linux:
	$(eval DIR := bench-linux)
	(cd ${DIR}; make)

static-linux:
	$(eval DIR := static-linux)
	(cd ${DIR}; make)

static-linux-x86:
	$(eval DIR := static-linux-x86)
	(cd ${DIR}; make)

static-win64:
	$(eval DIR := share-win64)
	(cd ${DIR}; make)

static-win32:
	$(eval DIR := share-win32)
	(cd ${DIR}; make)

install:
	./install.sh ${DIR} ${LIB} ${INCLUDE} ldconfig

clean:
	(for i in *; if -d [ $i ]; cd $i; rm *.so* *.a*; make clean; cd -)
