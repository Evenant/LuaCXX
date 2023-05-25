
#include "../LuaCXX.hpp"
#include <cstddef>
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

LuaTable::LuaTable(lua_State* thread, bool create_table, int table_position, int dict_size, int array_size) : LuaRef(thread)
{
	if (create_table)
	{
		lua_createtable(this->thread, array_size, dict_size);
		this->position = lua_gettop(this->thread);
		
	}	
	else
	{
		this->position = table_position;
	}
	this->index_count = this->array_size();
	this->field_count = this->get_all_fields().size();
	

}



static Type _get_typeof(lua_State* L)
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

	lua_pop(L, 1);
	return t;
}
Type LuaTable::get_typeof(const char* field)
{
	if (this->is_null)
		return Nil;
	lua_getfield(this->thread, this->position, field);
	return _get_typeof(this->thread);
}
Type LuaTable::get_typeof(int index)
{
	if (this->is_null)
		return Nil;
	lua_rawgeti(this->thread, this->position, index);
	return _get_typeof(this->thread);
}

std::vector<const char*> LuaTable::get_all_fields()
{
	std::vector<const char*> ret;
	/* table is in the stack at index 't' */
    lua_pushnil(this->thread);  /* first key */
    while (lua_next(this->thread, this->position) != 0) {
		constexpr int key = -2;
		constexpr int value = -1;

		if (lua_type(this->thread, key) == LUA_TSTRING)
			ret.push_back(lua_tostring(this->thread, key));
		else
			ret.push_back("");
		
    	lua_pop(this->thread, 1);
    }
	return ret;

}

int LuaTable::array_size()
{
	/*
	int sz = 0;
    lua_pushnil(this->L->get_rawstate()); 
    while (lua_next(this->L->get_rawstate(), this->table_position) != 0) {
		constexpr int key = -2;
		constexpr int value = -1;

		if (lua_type(this->L->get_rawstate(), key) == LUA_TNUMBER)
			sz += 1;
		
    	lua_pop(this->L->get_rawstate(), 1);
    }
	*/
	return lua_objlen(this->thread, this->position);
}

bool LuaTable::is_valid()
{
	if (this->is_null 
	|| !lua_istable(this->thread, this->position)
	)
		return false;
	return true;
}