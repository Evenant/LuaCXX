#include "../LuaCXX.hpp"

using namespace LuaCXX;

template <>
double LuaTable::get(const char* field)
{
	// for cleanup
	const int bf = lua_gettop(this->thread);

	if (!this->push_self()) // If the value of this reference is on the Lua stack
	{
		//
		lua_pushstring(this->thread, field);
		lua_gettable(this->thread, this->position);
		// this->position[field]
	}
	else // If the value of this reference is in the Lua registry
	{
		//
		lua_pushstring(this->thread, field);
		lua_gettable(this->thread, -2);
		// LUA_REGISTRY[this->key][field]
	}

	// get the number
	double n = lua_tonumber(this->thread, -1);

	// cleanup
	lua_settop(this->thread, bf);

	return n;
}

template <>
double LuaTable::get(int index)
{
	// for cleanup
	const int bf = lua_gettop(this->thread);

	if (!this->push_self()) // If the value of this reference is on the Lua stack
	{
		//
		lua_pushinteger(this->thread, index);
		lua_gettable(this->thread, this->position);
		// this->positions[index]
	}
	else // If the value of this reference is in the Lua registry
	{
		//
		lua_pushinteger(this->thread, index);
		lua_gettable(this->thread, -2);
		// LUA_REGISTRY[this->key][index]
	}

	// get the number
	double n = lua_tonumber(this->thread, -1);

	// cleanup
	lua_settop(this->thread, bf);

	return n;
}