
# All Target
all: shared

shared:
	(cd Shared; make)

bench:
	(cd Bench; make)

static:
	(cd Static; make)

install: install-shared

install-shared:
	./install-shared.sh

install-bench:
	./install-bench.sh

install-static:
	./install-static.sh

clean:
	(cd Shared; rm *.so*; make clean)
	(cd Bench; rm *.so*; make clean)
	(cd Static; rm *.a*; make clean)
