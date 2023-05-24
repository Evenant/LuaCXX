CXX=g++
CXXFLAGS= -std=gnu++17

TESTING_HEADER=testing.hpp

EXECUTABLES= \
	setget/main

OBJECTS= \
	setget/main.o

default: setget

setget: setget/main
	setget/main

clean:
	rm -f ${OBJECTS}
	rm -f ${EXECUTABLES}


.PHONY: default setget clean

setget/main: setget/main.o
	${cxx_e}

setget/main.o: setget/main.cpp ${TESTING_HEADER}
	${cxx_o}

define cxx_o
	${CXX} -o $@ $< ${CXXFLAGS} -c
endef

define cxx_e
	${CXX} -o $@ $^ ${LIBLUACXX} ${LIBLUA}
endef