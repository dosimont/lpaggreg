
# All Target
all:
	(cd Release; make)

install:
	./install.sh
clean:
	(cd Release; rm *.so*; make clean)

