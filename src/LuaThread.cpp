#include "../LuaCXX.hpp"
#include <iostream>

using namespace LuaCXX;

LuaThread::LuaThread(lua_State* th, bool create_new_thread) : LuaRef(th)
{
	lua_pushlightuserdata(this->thread, this->key);

	if (create_new_thread)
		this->value_thread = lua_newthread(th);
	else
		this->value_thread = lua_tothread(th, -2);

	lua_settable(this->thread, LUA_REGISTRYINDEX);



}

LuaThread::operator lua_State *()
{
	return this->get_lua();
}

lua_State* LuaThread::get_lua()
{
	return this->value_thread;
}


LuaTable LuaThread::globals()
{
	return LuaTable(this->value_thread, LUA_GLOBALSINDEX);
}

LuaTable LuaThread::registry()
{
	return LuaTable(this->value_thread, LUA_REGISTRYINDEX);
}

LuaTable LuaThread::new_table()
{
	
	return LuaTable(this->value_thread);
}

LuaThread LuaThread::new_thread()
{
	return LuaThread(this->value_thread, true);
}