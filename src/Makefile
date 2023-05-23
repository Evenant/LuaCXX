
# Makefile for building LuaCXX directly.

OUTPUT=libluacxx.a

OBJECTS= \
	Lua.o \
	LuaTable.o \
	LuaTable_setget.o 

CXX=g++
CXX_STD=gnu++17
CXXFLAGS= -std=${CXX_STD} -I${INCLUA}

AR=ar

# directory containing lua include files
INCLUA=/usr/include

LUA_HEADERS= \
	${INCLUA}/lua.h \
	${INCLUA}/lualib.h \
	${INCLUA}/lauxlib.h


default: ${OUTPUT}

${OUTPUT}: ${OBJECTS} ${LUA_HEADERS}
	${AR} -rc ${OUTPUT} ${OBJECTS}


help:
	@cat help.txt
	@echo

clean:
	rm -f ${OBJECTS}
	rm -f ${OUTPUT}

.PHONY: default help clean

Lua.o: Lua.cpp
	${cxx_o}

LuaTable.o: LuaTable.cpp
	${cxx_o}

LuaTable_setget.o: LuaTable_setget.cpp
	${cxx_o}

# Custom macro for creating C++ object files
define cxx_o
	${CXX} $< -o $@ ${CXXFLAGS} -c
endef