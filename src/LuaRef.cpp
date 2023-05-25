#include "../LuaCXX.hpp"
#include <cstdlib>

using namespace LuaCXX;

LuaRef::LuaRef(lua_State* th)
{
	this->thread = th;
	this->key = malloc(1);
}

LuaRef::LuaRef(lua_State* th, int existing_value)
{
	this->thread = th;
	this->position = existing_value;
}

LuaRef::~LuaRef()
{
	if (key)
	{
		lua_pushlightuserdata(this->thread, this->key);
		lua_pushnil(this->thread);
		lua_settable(this->thread, LUA_REGISTRYINDEX);
		free(this->key);

	}

}

void LuaRef::move_into(lua_State *into)
{
	if (key)
	{
		lua_pushlightuserdata(this->thread, this->key);
		lua_gettable(this->thread, LUA_REGISTRYINDEX);
		lua_xmove(this->thread, into, -1);

		lua_pushlightuserdata(this->thread, this->key);
		lua_pushnil(this->thread);
		lua_settable(this->thread, LUA_REGISTRYINDEX);
	}
	else 
	{
		lua_xmove(this->thread, into, this->position);
	}
}