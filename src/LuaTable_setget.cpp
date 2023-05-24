
#include "lua_i.hpp"
#include "../LuaCXX.hpp"

using namespace LuaCXX;

// To be used in both `get_bool` methods.
#define _get_bool if (lua_toboolean( \
		this->L, \
		lua_gettop(this->L) \
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
	
	lua_getfield(this->thread, this->position, field);
	return lua_toboolean(this->thread, lua_gettop(this->thread));
	
}
void LuaTable::set_bool(const char* field, bool value)
{
	if (value)
		lua_pushboolean(this->thread, 1);
	else
		lua_pushboolean(this->thread, 0);
	
	lua_setfield(this->thread, this->position, field);
}
bool LuaTable::get_bool(int index)
{
	if (this->get_typeof(index) != Boolean)
		return false;
	
	lua_rawgeti(this->thread, this->position, index);
	return lua_toboolean(this->thread, lua_gettop(this->thread));
}
void LuaTable::set_bool(int index, bool value)
{
	if (value)
		lua_pushboolean(this->thread, 1);
	else
		lua_pushboolean(this->thread, 0);
	lua_rawseti(this->thread, 
		this->position, 
		lua_gettop(this->thread)
	);
}

double LuaTable::get_number(const char* field)
{
	if (this->get_typeof(field) != Number)
		return 0.0;
	
	lua_getfield(this->thread, this->position, field);
	return lua_tonumber(this->thread, lua_gettop(this->thread));
}

void LuaTable::set_number(const char* field, double value)
{
	lua_pushnumber(this->thread, value);
	lua_setfield(this->thread, this->position, field);
}
double LuaTable::get_number(int index)
{
	if (this->get_typeof(index) != Number)
		return 0.0;
	
	lua_rawgeti(this->thread, this->position, index);
	return lua_tonumber(this->thread, lua_gettop(this->thread));
}
void LuaTable::set_number(int index, double value)
{
	lua_pushnumber(this->thread, value);
	lua_rawseti(this->thread, this->position, index);
}

const char* LuaTable::get_string(const char* field)
{
	if (this->get_typeof(field) != String)
		return 0;
	
	lua_getfield(this->thread, this->position, field);
	return lua_tostring(this->thread, lua_gettop(this->thread));
}
void LuaTable::set_string(const char* field, const char* value)
{
	lua_pushstring(this->thread, value);
	lua_setfield(this->thread, this->position, field);
}

const char* LuaTable::get_string(int index)
{
	if (this->get_typeof(index) != String)
		return 0;
	
	lua_rawgeti(this->thread, this->position, index);
	return lua_tostring(this->thread, lua_gettop(this->thread));
}
void LuaTable::set_string(int index, const char* value)
{
	lua_pushstring(this->thread, value);
	lua_rawseti(this->thread, this->position, index);
}

/* TODO: Finish this
LuaTable LuaTable::get_table(const char * field)
{
	if (this->get_typeof(field) != Table)
		return LuaTable(nullptr);
	
	LuaTable lt = this->L->new_table();

	
	
}
ptr<LuaTable> LuaTable::get_table(int index)
{

}
*/	