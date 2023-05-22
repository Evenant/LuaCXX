
#include "lua_i.hpp"
#include "../LuaCXX.hpp"
#include <lua.h>

using namespace LuaCXX;

LuaTable Lua::globals()
{
	LuaTable *gt = new LuaTable(this->new_thread());
	return *gt;
}

Lua::Lua(bool openlibs)
{
	this->state = luaL_newstate();
	this->is_from_raw_state = false;
	if (openlibs)
	{
		luaL_openlibs(this->state);
	}
}

Lua::Lua(lua_State* L)
{
	this->state = L;
	this->is_from_raw_state = true;

}

Lua::~Lua()
{
	if (!this->is_from_raw_state)
		lua_close(this->state);
}

Lua::operator lua_State *()
{
	return this->state;
}


lua_State* Lua::get_rawstate()
{
	return this->state;
}

bool Lua::is_null()
{
	if (this->state)
		return false;
	else
		return true;
}

ptr<Lua> Lua::new_thread()
{
	ptr<Lua> th(this->_new_thread());
	this->sub_threads.push_back(th);
	return th;
}

LuaTable Lua::new_table()
{
	ptr<Lua> lua = this->new_thread();
	
	LuaTable *table = new LuaTable(lua);



	return *table;
}
Lua* Lua::_new_thread()
{
	lua_State* a = lua_newthread(this->state);
	Lua *th = new Lua(a);
	th->is_from_raw_state = false;
	return th;


}

