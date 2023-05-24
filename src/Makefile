
# Makefile for building LuaCXX directly.

################################
# USER INTERFACE
################################


OUTPUT=libluacxx.a

CXX=g++
CXX_STD=gnu++17

# Extra flags in addition to the default CXXFLAGS
MYCXXFLAGS=

# Internal function calls are printed to the standard output, used for debugging.
# Set to 1 to enable
ENABLE_DEBUG_INTERNAL_FUNCCALLS=

# Enables settings for development.
# Set to 1 to enable.
ENABLE_DEVELOPER_MODE=


AR=ar

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

ifeq (${ENABLE_DEVELOPER_MODE},1)

ENABLE_DEBUG_INTERNAL_FUNCCALLS+=1

endif

ifeq (${ENABLE_DEBUG_INTERNAL_FUNCCALLS},1)

CXXFLAGS+= -DINTERNAL_FUNCCALLS

endif

OBJECTS= LuaThread.o \
	LuaTable.o \
	LuaTable_setget.o \
	LuaRef.o

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

LuaTable_setget.o: LuaTable_setget.cpp ${API_HEADER}
	${cxx_o}

LuaRef.o : LuaRef.cpp ${API_HEADER}
	${cxx_o}

# Custom macro for creating C++ object files
define cxx_o
	${CXX} $< -o $@ ${CXXFLAGS} -c
endef