#include "../LuaCXX.hpp"

using namespace LuaCXX;

template <>
void LuaTable::set(const char* field, const char*& value)
{
	// for cleanup
	const int bf = lua_gettop(this->thread);

	if (!this->push_self())// If the value of this reference is on the Lua stack
	{
		//
		lua_pushstring(this->thread, field);
		lua_pushstring(this->thread, value);
		lua_settable(this->thread, this->position);
		// this->position[field] = value
	}
	else // If the value of this reference is on the Lua registry
	{
		//
		lua_pushstring(this->thread, field);
		lua_pushstring(this->thread, value);
		lua_settable(this->thread, -3);
		// LUA_REGISTRY[this->key][field] = value
	}

	// cleanup
	lua_settop(this->thread, bf);
}

template <>
void LuaTable::set(int index, const char*& value)
{
	// for cleanup
	const int bf = lua_gettop(this->thread);

	if (!this->push_self()) // If the value of this reference is on the Lua stack
	{
		//
		lua_pushinteger(this->thread, index);
		lua_pushstring(this->thread, value);
		lua_settable(this->thread, this->position);
		// this->position[index] = value
	}
	else // If the value of this reference is on the Lua registry
	{
		//
		lua_pushinteger(this->thread, index);
		lua_pushstring(this->thread, value);
		lua_settable(this->thread, -3);
		// LUA_REGISTRY[this->key][index] = value
	}

	// cleanup
	lua_settop(this->thread, bf);
}