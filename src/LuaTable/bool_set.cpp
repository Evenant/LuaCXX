#include "../../LuaCXX.hpp"

using namespace LuaCXX;

template <>
void LuaTable::set(const char* field, const bool& value)
{
	const int bf = lua_gettop(this->thread);

	if (!this->push_self())
	{
		lua_pushstring(this->thread, field);
		lua_pushboolean(this->thread, value);
		lua_settable(this->thread, this->position);
	}
	else 
	{
		lua_pushstring(this->thread, field);
		lua_pushboolean(this->thread, value);
		lua_settable(this->thread, -3);
	}

	lua_settop(this->thread, bf);
}

template <>
void LuaTable::set(int index, const bool& value)
{
	const int bf = lua_gettop(this->thread);

	if (!this->push_self())
	{
		lua_pushinteger(this->thread, index);
		lua_pushboolean(this->thread, value);
		lua_settable(this->thread, this->position);
	}
	else 
	{
		lua_pushinteger(this->thread, index);
		lua_pushboolean(this->thread, value);
		lua_settable(this->thread, -3);
	}

	lua_settop(this->thread, bf);
}