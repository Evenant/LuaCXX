#include "../LuaCXX.hpp"
#include <cstdlib>

using namespace LuaCXX;

LuaRef::LuaRef(lua_State* th)
{
	this->thread = th;
	this->key = malloc(1);
}

LuaRef::~LuaRef()
{
	lua_pushlightuserdata(this->thread, this->key);
	lua_pushnil(this->thread);
	lua_settable(this->thread, LUA_REGISTRYINDEX);
	free(this->key);

}

void LuaRef::move_into(lua_State *into)
{
	lua_pushlightuserdata(this->thread, this->key);
	lua_gettable(this->thread, LUA_REGISTRYINDEX);
	lua_xmove(this->thread, into, -1);
	delete this;
}