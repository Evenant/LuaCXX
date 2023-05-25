#include "../../LuaCXX.hpp"

using namespace LuaCXX;

template <>
const char* LuaTable::get(const char* field)
{
	const int bf = lua_gettop(this->thread);

	if (!this->push_self())
	{
		lua_pushstring(this->thread, field);
		lua_gettable(this->thread, this->position);
	}
	else
	{
		lua_pushstring(this->thread, field);
		lua_gettable(this->thread, -2);
	}

	const char* s = lua_tostring(this->thread, -1);

	lua_settop(this->thread, bf);

	return s;
}

template <>
const char* LuaTable::get(int index)
{
	const int bf = lua_gettop(this->thread);

	if (!this->push_self())
	{
		lua_pushinteger(this->thread, index);
		lua_gettable(this->thread, this->position);
	}
	else 
	{
		lua_pushinteger(this->thread, index);
		lua_gettable(this->thread, -2);
	}

	const char* s = lua_tostring(this->thread, -1);

	lua_settop(this->thread, bf);

	return s;
}