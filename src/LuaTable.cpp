
#include "../LuaCXX.hpp"
#include <cstddef>
#include <cstdlib>
#include <vector>

using namespace LuaCXX;

static Type _get_type(lua_State* L);



LuaTable::LuaTable(lua_State* thread) : LuaRef(thread)
{
	lua_pushlightuserdata(this->thread, this->key);
	lua_createtable(this->thread, 0, 0);
	lua_settable(this->thread, LUA_REGISTRYINDEX);
}

LuaTable::LuaTable(lua_State* thread, int position) : LuaRef(thread, position)
{

}

int LuaTable::get_top()
{
	int bf = lua_gettop(this->thread);

	size_t l;
	if (!this->push_self())
	{
		l = lua_objlen(this->thread, this->position);
	}
	else
	{
		l = lua_objlen(this->thread, -1);
	}

	lua_settop(this->thread, bf);
	return l;
}

std::vector<const char*> LuaTable::get_all_fields()
{
	int bf = lua_gettop(this->thread);

	int tp;
	if (!this->push_self())
	{
		tp = this->position;
	}
	else 
	{
		tp = lua_gettop(this->thread);
	}
	
	std::vector<const char*> v;

	lua_pushnil(this->thread);
	while (lua_next(this->thread, tp))
	{
		constexpr int value = -1;
		constexpr int key = -2;

		// Remove value, now key is on -1
		lua_pop(this->thread, 1);

		if (_get_type(this->thread) == Type::String)
			v.push_back(lua_tostring(this->thread, -1));
		
	}

	lua_settop(this->thread, bf);

	return v;
}

void LuaTable::set_self(lua_State *state)
{
	if (this->key)
	{
		lua_pushlightuserdata(this->thread, this->key);
		lua_insert(this->thread, -2);

		lua_settable(this->thread, LUA_REGISTRYINDEX);
	}
	else
	{
		if (this->position != LUA_REGISTRYINDEX
		&& this->position != LUA_GLOBALSINDEX
		&& this->position != LUA_ENVIRONINDEX)
			lua_replace(this->thread, this->position);

	}

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