#include "../LuaCXX.hpp"

using namespace LuaCXX;

template <>
bool LuaTable::get(const char* field) const
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

	// Get the boolean
	bool b = lua_toboolean(this->thread, -1);

	// cleanup
	lua_settop(this->thread, bf);

	return b;
}

template <>
bool LuaTable::get(int index) const
{
	// for cleanup
	const int bf = lua_gettop(this->thread);

	if (!this->push_self()) // If the value of this reference is on the Lua stack
	{
		//
		lua_pushinteger(this->thread, index);
		lua_gettable(this->thread, this->position);
		// this->position[index]
	}
	else // If the value of this reference is in the Lua registry
	{
		//
		lua_pushinteger(this->thread, index);
		lua_gettable(this->thread, -2);
		// LUA_REGISTRY[this->key][index]
	}

	// get the boolean
	bool b = lua_toboolean(this->thread, -1);

	// cleanup
	lua_settop(this->thread, bf);

	return b;
}