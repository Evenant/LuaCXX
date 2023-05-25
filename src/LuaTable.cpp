
#include "../LuaCXX.hpp"
#include <cstddef>
#include <cstdlib>
#include <vector>

using namespace LuaCXX;

static void clone_values(lua_State* L, int from, int to)
{
	lua_pushnil(L);  /* first key */
    while (lua_next(L, from) != 0) {
		constexpr int key = -2;
		constexpr int value = -1;



		if (lua_isstring(L, key))
		{
			const char* key_s = lua_tostring(L, key);
			lua_getfield(L, from, key_s);
			lua_setfield(L, to, key_s);

			lua_pushstring(L, key_s);
			lua_insert(L, key);

		}
		
    	lua_pop(L, 1);
    }

	for (int i = 0; i < lua_objlen(L, from);i++)
	{
		lua_rawgeti(L, from, i+1);
		lua_rawseti(L, to, i+1);
	}
}
/*
void LuaTable::add_field()
{
	this->field_count++;
	lua_createtable(this->thread, this->index_count, this->field_count);

	int new_table = lua_gettop(this->thread);

	clone_values(this->thread, this->position, new_table);

	lua_insert(this->thread, this->position);
	lua_settop(this->thread, this->position);

}

void LuaTable::add_index()
{
	this->index_count++;
	lua_createtable(this->thread, this->index_count, this->field_count);

	int new_table = lua_gettop(this->L);

	clone_values(this->thread, this->position, new_table);

	lua_insert(this->thread, this->position);
	lua_settop(this->thread, this->position);
}
*/
LuaTable::LuaTable(lua_State* thread) : LuaRef(thread)
{
	lua_pushlightuserdata(this->thread, this->key);
	lua_createtable(this->thread, 0, 0);
	lua_settable(this->thread, LUA_REGISTRYINDEX);
}



static Type _get_type(lua_State* L)
{
	Type t;

	switch (lua_type(L, -1)) 
	{
		case (LUA_TBOOLEAN):
			t = Type::Boolean;
			break;
		case (LUA_TFUNCTION):
			t = Type::Function;
			break;
		case (LUA_TLIGHTUSERDATA):
			t = Type::LightUserdata;
			break;
		case (LUA_TUSERDATA):
			t = Type::Userdata;
			break;
		case (LUA_TNIL):
			t = Type::Nil;
			break;
		case (LUA_TNONE):
			t = Type::None;
			break;
		case (LUA_TNUMBER):
			t = Type::Number;
			break;
		case (LUA_TSTRING):
			t = Type::String;
			break;
		case (LUA_TTABLE):
			t = Type::Table;
			break;
		case (LUA_TTHREAD):
			t = Type::Thread;
			break;
		default:
			t = Type::Nil;
			break;
	}

	return t;
}

bool LuaTable::push_self()
{
	if (key)
	{
		lua_pushlightuserdata(this->thread, this->key);
		lua_gettable(this->thread, LUA_REGISTRYINDEX);

		return true;
	}
	return false;
}

template<>
Type LuaTable::get_type(const char* field)
{
	if (!this->push_self())
	{
		lua_pushstring(this->thread, field);
		lua_gettable(this->thread, this->position);
	}
	
	Type t = _get_type(this->thread);

	lua_pop(this->thread, -1);

	return t;

}

template<>
Type LuaTable::get_type(int index)
{
	if (!this->push_self())
	{
		lua_pushinteger(this->thread, index);
		lua_gettable(this->thread, this->position);
	}
	
	Type t = _get_type(this->thread);

	lua_pop(this->thread, -1);

	return t;
}