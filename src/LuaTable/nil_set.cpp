#include "../LuaCXX.hpp"

using namespace LuaCXX;

template<>
void LuaTable::set_nil(int index)
{
	// for cleanup
	int bf = lua_gettop(this->thread);

	if (!this->push_self()) // If the value of this reference is on the Lua stack
	{
		//
		lua_pushinteger(this->thread, index);
		lua_pushnil(this->thread);
		lua_settable(this->thread, this->position);
		// this->position[index] = nil
	}
	else
	{
		// 
		lua_pushinteger(this->thread, index);
		lua_pushnil(this->thread);
		lua_settable(this->thread, -3);
		// LUA_REGISTRY[this->key][index] = nil

	}

	//cleanup
	lua_settop(this->thread, bf);
}

template<>
void LuaTable::set_nil(const char* field)
{
	// for cleanup
	int bf = lua_gettop(this->thread);

	if (!this->push_self()) // If the value of this reference is on the Lua stack
	{
		//
		lua_pushstring(this->thread, field);
		lua_pushnil(this->thread);
		lua_settable(this->thread, this->position);
		// this->position[field] = nil
	}
	else
	{
		// 
		lua_pushstring(this->thread, field);
		lua_pushnil(this->thread);
		lua_settable(this->thread, -3);
		// LUA_REGISTRY[this->key][field] = nil

	}

	//cleanup
	lua_settop(this->thread, bf);
}
