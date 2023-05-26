#include "../LuaCXX.hpp"
#include <cstdlib>

using namespace LuaCXX;

LuaRef::LuaRef(lua_State* th)
{
	this->thread = th;

	/*
		malloc will always return a pointer that has a different value than
		anything else in a running program.
	*/
	this->key = malloc(1);
}

LuaRef::LuaRef(lua_State* th, int existing_value)
{
	this->thread = th;
	this->position = existing_value;
}

LuaRef::~LuaRef()
{
	/*
		Only if this reference was initialized on its own, not from a pre-existing
		value on the stack.
	*/
	if (key)
	{
		//
		lua_pushlightuserdata(this->thread, this->key);
		lua_pushnil(this->thread);
		lua_settable(this->thread, LUA_REGISTRYINDEX);
		// LUA_REGISTRY[this->thread] = nil

		// Also free the single byte that was allocated.
		free(this->key);

	}

}

void LuaRef::move_into(lua_State *into)
{
	if (key) // If the value of this reference is on the Lua registry
	{
		//
		lua_pushlightuserdata(this->thread, this->key);
		lua_gettable(this->thread, LUA_REGISTRYINDEX);
		// LUA_REGISTRY[this->key]

		// Move it to the other thread
		lua_xmove(this->thread, into, -1);

		/*
			Now nilify the value on the registry.
		*/
		//
		lua_pushlightuserdata(this->thread, this->key);
		lua_pushnil(this->thread);
		lua_settable(this->thread, LUA_REGISTRYINDEX);
		// LUA-REGISTRY[this->key] = nil
	}
	else // If the value of this reference is on the stack
	{
		lua_xmove(this->thread, into, this->position);
	}
}