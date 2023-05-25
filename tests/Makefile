CXX=g++
CXXFLAGS= -std=gnu++17

TESTING_HEADER=testing.hpp

EXECUTABLES= \
	setget/main

OBJECTS= \
	setget/main.o

default: setget setget_table

setget: setget/main
	setget/main

setget_table: setget_table/main
	setget_table/main

clean:
	rm -f ${OBJECTS}
	rm -f ${EXECUTABLES}


.PHONY: default setget clean setget_table

setget/main: setget/main.o
	${cxx_e}

setget/main.o: setget/main.cpp ${TESTING_HEADER}
	${cxx_o}

setget_table/main: setget_table/main.o
	${cxx_e}

setget_table/main.o: setget_table/main.cpp ${TESTING_HEADER}
	${cxx_o}

define cxx_o
	${CXX} -o $@ $< ${CXXFLAGS} -c
endef

define cxx_e
	${CXX} -o $@ $^ ${LIBLUACXX} ${LIBLUA}
endef