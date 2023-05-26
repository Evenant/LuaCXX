#include "../../LuaCXX.hpp"

using namespace LuaCXX;

template <>
LuaTable LuaTable::get(const char* field)
{
	// for cleanup
	const int bf = lua_gettop(this->thread);

	if (!this->push_self()) //  If the value of this reference is on the Lua stack
	{
		//
		lua_pushstring(this->thread, field);
		lua_gettable(this->thread, this->position);
		// this->position[field] 
	}
	else //  If the value of this reference is on the Lua registry
	{
		//
		lua_pushstring(this->thread, field);
		lua_gettable(this->thread, -2);
		// LUA_REGISTRY[this->key][field]
	}

	LuaTable* tb = new LuaTable(this->thread);
	tb->set_self(this->thread);

	// cleanup
	lua_settop(this->thread, bf);

	return *tb;
}

template <>
LuaTable LuaTable::get(int index)
{
	// for cleanup
	const int bf = lua_gettop(this->thread);

	if (!this->push_self()) //  If the value of this reference is on the Lua stack
	{
		//
		lua_pushinteger(this->thread, index);
		lua_gettable(this->thread, this->position);
		// this->position[index]
	}
	else //  If the value of this reference is on the Lua registry
	{
		//
		lua_pushinteger(this->thread, index);
		lua_gettable(this->thread, -2);
		// LUA_REGISTRY[this->key][index]
	}

	LuaTable* tb = new LuaTable(this->thread);
	tb->set_self(this->thread);

	// cleanup
	lua_settop(this->thread, bf);

	return *tb;
}