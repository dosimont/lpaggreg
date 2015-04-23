
# All Target
all: shared

shared:
	(cd Shared; make)

bench:
	(cd Bench; make)

static:
	(cd Static; make)

static32:
	(cd Static32; make)

install: install-shared

install-shared:
	./install-shared.sh

install-bench:
	./install-bench.sh

install-static:
	./install-static.sh

install-static32:
	./install-static32.sh

clean:
	(cd Shared; rm *.so*; make clean)
	(cd Bench; rm *.so*; make clean)
	(cd Static; rm *.a*; make clean)
	(cd Static32; rm *.a*; make clean)
