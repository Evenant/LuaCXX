#include "../LuaCXX.hpp"
#include <iostream>

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
	return LuaTable(this->value_thread, false, LUA_GLOBALSINDEX);
}

LuaTable LuaThread::new_table(int dict_size, int array_size)
{
	if (dict_size < 0)
		dict_size = LuaTable::default_dict_size;
	if (array_size < 0)
		array_size = LuaTable::default_array_size;
	
	return LuaTable(this->value_thread,true,0,dict_size,array_size);
}

LuaThread LuaThread::new_thread()
{
	return LuaThread(this->value_thread, true);
}