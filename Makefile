
OUTPUT=${PWD}/libluacxx.a

# Full path to lua library, only needed for running tests.
LIBLUA=/usr/lib/liblua.a

default: build

build: ${OUTPUT}

test: ${OUTPUT} ${LIBLUA} 
	cd tests && $(MAKE) \
		OUTPUT=${OUTPUT} \
		LIBLUA=${LIBLUA}

.PHONY: default build test

${OUTPUT}:
	cd src && $(MAKE) \
		OUTPUT=${OUTPUT}

