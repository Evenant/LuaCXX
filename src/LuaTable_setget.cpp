#include "lua_i.hpp"
#include "../LuaCXX.hpp"
#include <lua.h>

using namespace LuaCXX;

// To be used in both `get_bool` methods.
#define _get_bool if (lua_toboolean( \
		this->L->get_rawstate(), \
		lua_gettop(this->L->get_rawstate()) \
		)) \
		return true; \
	else \
		return false;

#define _set_bool_conditional if (value) \
		lua_pushboolean(this->L->get_rawstate(), 1); \
	else \
		lua_pushboolean(this->L->get_rawstate(), 0);

bool LuaTable::get_bool(const char* field)
{
	if (this->get_typeof(field) != Boolean)
		return false;
	
	lua_getfield(this->L->get_rawstate(), this->table_position, field);
	_get_bool;
	
}
void LuaTable::set_bool(const char* field, bool value)
{
	_set_bool_conditional;
	
	lua_setfield(this->L->get_rawstate(), this->table_position, field);
}
bool LuaTable::get_bool(int index)
{
	if (this->get_typeof(index) != Boolean)
		return false;
	
	lua_rawgeti(this->L->get_rawstate(), this->table_position, index);
	_get_bool;
}
void LuaTable::set_bool(int index, bool value)
{
	_set_bool_conditional;
	lua_rawseti(this->L->get_rawstate(), 
		this->table_position, 
		lua_gettop(this->L->get_rawstate())
	);
}

double LuaTable::get_number(const char* field)
{
	if (this->get_typeof(field) != Number)
		return 0.0;
	
	lua_getfield(this->L->get_rawstate(), this->table_position, field);
	return lua_tonumber(this->L->get_rawstate(), lua_gettop(this->L->get_rawstate()));
}

void LuaTable::set_number(const char* field, double value)
{
	lua_pushnumber(this->L->get_rawstate(), value);
	lua_setfield(this->L->get_rawstate(), this->table_position, field);
}
double LuaTable::get_number(int index)
{
	if (this->get_typeof(index) != Number)
		return 0.0;
	
	lua_rawgeti(this->L->get_rawstate(), this->table_position, index);
	return lua_tonumber(this->L->get_rawstate(), lua_gettop(this->L->get_rawstate()));
}
void LuaTable::set_number(int index, double value)
{
	lua_pushnumber(this->L->get_rawstate(), value);
	lua_rawseti(this->L->get_rawstate(), this->table_position, index);
}

const char* LuaTable::get_string(const char* field)
{
	if (this->get_typeof(field) != String)
		return 0;
	
	lua_getfield(this->L->get_rawstate(), this->table_position, field);
	return lua_tostring(this->L->get_rawstate(), lua_gettop(this->L->get_rawstate()));
}
void LuaTable::set_string(const char* field, const char* value)
{
	lua_pushstring(this->L->get_rawstate(), value);
	lua_setfield(this->L->get_rawstate(), this->table_position, field);
}

const char* LuaTable::get_string(int index)
{
	if (this->get_typeof(index) != String)
		return 0;
	
	lua_rawgeti(this->L->get_rawstate(), this->table_position, index);
	return lua_tostring(this->L->get_rawstate(), lua_gettop(this->L->get_rawstate()));
}
void LuaTable::set_string(int index, const char* value)
{
	lua_pushstring(this->L->get_rawstate(), value);
	lua_rawseti(this->L->get_rawstate(), this->table_position, index);
}

LuaTable LuaTable::get_table(const char * field)
{
	if (this->get_typeof(field) != Table)
		return LuaTable(nullptr);
	
	LuaTable lt = this->L->new_table();

	
	
}
ptr<LuaTable> LuaTable::get_table(int index)
{

}