#include "lua_i.hpp"
#include "../LuaCXX.hpp"
#include <iostream>
#include <lua.h>

using namespace LuaCXX;

LuaThread::LuaThread(lua_State* th, bool create_new_thread) : LuaRef(th)
{
	if (create_new_thread)
		this->value_thread = lua_newthread(th);
	else
		this->value_thread = lua_tothread(th, -1);

	this->position = lua_gettop(th);

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
	std::cout << "Before getting global table\n";
	lua_getglobal(this->value_thread, "_G");
	std::cout << "After getting global table\n";
	return LuaTable(this->value_thread, false, LUA_GLOBALSINDEX);
}