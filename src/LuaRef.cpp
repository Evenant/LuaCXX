#include "lua_i.hpp"
#include "../LuaCXX.hpp"

using namespace LuaCXX;

LuaRef::LuaRef(lua_State* th)
{
	this->thread = th;
}

LuaRef::~LuaRef()
{
	if (this->position == LUA_GLOBALSINDEX) return;
	lua_remove(this->thread, this->position);
}

void LuaRef::move_into(lua_State *into)
{
	lua_xmove(this->thread, into, this->position);
	this->position = 0;
	delete this;
}