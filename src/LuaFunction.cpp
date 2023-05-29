#include "LuaCXX.hpp"

using namespace LuaCXX;

LuaFunction::LuaFunction(lua_State* th, int existing_func) : LuaRef(th, existing_func)
{
	// Bind to the LuaRef constructor
}

LuaFunction::LuaFunction(lua_State* th, lua_CFunction func) : LuaRef(th)
{
	lua_pushlightuserdata(this->thread, this->key);
	lua_pushcclosure(this->thread, func, 255);
	lua_settable(this->thread, LUA_REGISTRYINDEX);
}

const LuaTable LuaFunction::collect_stack(lua_State *th)
{
	LuaTable* tb = new LuaTable(th);

	tbq

	return *tb;
}