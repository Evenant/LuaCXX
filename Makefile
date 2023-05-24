
OUTPUT=${PWD}/libluacxx.a

# Full path to lua library, only needed for running tests.
LIBLUA=/usr/lib/liblua.a
INCLUA=/usr/include

default: build

build: 
	cd src && $(MAKE) build \
		OUTPUT=${OUTPUT} \
		INCLUA=${INCLUA} \

test: build ${LIBLUA} 
	cd tests && $(MAKE) \
		OUTPUT=${OUTPUT} \
		LIBLUA=${LIBLUA} \
		LIBLUACXX=${OUTPUT}

clean:
	cd src && $(MAKE) clean
	cd tests && $(MAKE) clean

.PHONY: default build test

	

