CXX=g++
CXXFLAGS= -std=gnu++17

TESTING_HEADER=testing.hpp

EXECUTABLES= \
	setget/main \
	setget_table/main \
	setget_nilify/main \
	pushpop/main

OBJECTS= \
	setget/main.o \
	setget_table/main.o \
	setget_nilify/main.o \
	pushpop/main.o

TESTS= \
	setget \
	setget_table \
	setget_nilify \
	pushpop \

default: ${TESTS}
	@echo 
	@echo "Running tests"
	@echo 
	@$(foreach e, ${EXECUTABLES}, $e &&) echo "Finished running Tests."
	@echo 

setget: setget/main

setget_table: setget_table/main

setget_nilify: setget_nilify/main

pushpop: pushpop/main

clean:
	rm -f ${OBJECTS}
	rm -f ${EXECUTABLES}


.PHONY: default clean ${TESTS}

setget/main: setget/main.o
	${cxx_e}

setget/main.o: setget/main.cpp ${TESTING_HEADER}
	${cxx_o}

setget_table/main: setget_table/main.o
	${cxx_e}

setget_table/main.o: setget_table/main.cpp ${TESTING_HEADER}
	${cxx_o}

setget_nilify/main: setget_nilify/main.o
	${cxx_e}

setget_nilify/main.o: setget_nilify/main.cpp ${TESTING_HEADER}

pushpop/main: pushpop/main.o
	${cxx_e}
pushpop/main.o: pushpop/main.cpp ${TESTING_HEADER}
	${cxx_o}

define cxx_o
	${CXX} -o $@ $< ${CXXFLAGS} -c
endef

define cxx_e
	${CXX} -o $@ $^ ${LIBLUACXX} ${LIBLUA}
endef