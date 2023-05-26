
# Makefile for building LuaCXX directly.

################################
# USER INTERFACE
################################


OUTPUT=libluacxx.a

CXX=g++
CXX_STD=gnu++17
AR=ar

# Extra flags in addition to the default CXXFLAGS
MYCXXFLAGS=


# directory containing lua include files
INCLUA=/usr/include


################################
# END OF USER INTERFACE
#
# EVERYTHING BELOW IS ONLY TO BE SET BASED ON THE
# SETTINGS ABOVE.
################################


API_HEADER=../LuaCXX.hpp

default: build ${OUTPUT} ${OBJECTS} ${INCLUA} ${LUA_HEADERS} ${API_HEADER}

build: ${OUTPUT} ${OBJECTS} ${INCLUA} ${LUA_HEADERS} ${API_HEADER}

help:
	@cat help.txt
	@echo

clean:
	rm -f ${OBJECTS}
	rm -f ${OUTPUT}
	rm -f ${OUTPUT}

.PHONY: default help clean build

CXXFLAGS= ${MYCXXFLAGS} -std=${CXX_STD} -I${INCLUA}

OBJECTS= LuaThread.o \
	LuaTable.o \
	LuaRef.o \
	LuaTable/bool_get.o \
	LuaTable/bool_set.o \
	LuaTable/number_get.o \
	LuaTable/number_set.o \
	LuaTable/string_get.o \
	LuaTable/string_set.o \
	LuaTable/table_get.o \
	LuaTable/table_set.o
	

LUA_HEADERS= \
	${INCLUA}/lua.h \
	${INCLUA}/lualib.h \
	${INCLUA}/lauxlib.h

${OUTPUT}: ${OBJECTS} ${LUA_HEADERS} *.cpp
	${AR} -rc ${OUTPUT} ${OBJECTS}


LuaThread.o: LuaThread.cpp ${API_HEADER}
	${cxx_o}

LuaTable.o: LuaTable.cpp ${API_HEADER}
	${cxx_o}

LuaRef.o : LuaRef.cpp ${API_HEADER}
	${cxx_o}

LuaTable/bool_get.o: LuaTable/bool_get.cpp ${API_HEADER}
	${cxx_o}
LuaTable/bool_set.o: LuaTable/bool_set.cpp ${API_HEADER}
	${cxx_o}

LuaTable/number_get.o: LuaTable/number_get.cpp ${API_HEADER}
	${cxx_o}
LuaTable/number_set.o: LuaTable/number_set.cpp ${API_HEADER}
	${cxx_o}

LuaTable/string_get.o: LuaTable/string_get.cpp ${API_HEADER}
	${cxx_o}
LuaTable/string_set.o: LuaTable/string_set.cpp ${API_HEADER}
	${cxx_o}

LuaTable/table_get.o: LuaTable/table_get.cpp ${API_HEADER}
	${cxx_o}
LuaTable/table_set.o: LuaTable/table_set.cpp ${API_HEADER}
	${cxx_o}
#LuaTable/_get.o: LuaTable/_get.cpp ${API_HEADER}
#LuaTable/_set.o: LuaTable/_set.cpp ${API_HEADER}

# Custom macro for creating C++ object files
define cxx_o
	${CXX} $< -o $@ ${CXXFLAGS} -c
endef