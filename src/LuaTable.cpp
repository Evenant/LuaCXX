#include "lua_i.hpp"
#include "../LuaCXX.hpp"
#include <cstddef>
#include <vector>

using namespace LuaCXX;

void LuaTable::add_field()
{
	this->field_count++;
	lua_createtable(*this->L, this->index_count, this->field_count);



}

void LuaTable::add_index()
{

}

LuaTable::LuaTable(ptr<Lua> L, int fields, int indexes)
{
	this->L = L;
	
	lua_createtable(*this->L, indexes, fields);

	this->table_position = lua_gettop(*this->L);
	this->index_count = indexes;
	this->field_count = fields;
}

LuaTable::LuaTable(std::nullptr_t n)
{
	this->is_null = true;
}

LuaTable::~LuaTable()
{

}

static LuaTable::Type _get_typeof(lua_State* L)
{
	typedef LuaTable::Type Type;
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
LuaTable::Type LuaTable::get_typeof(const char* field)
{
	if (this->is_null)
		return Nil;
	lua_getfield(this->L->get_rawstate(), this->table_position, field);
	return _get_typeof(this->L->get_rawstate());
}
LuaTable::Type LuaTable::get_typeof(int index)
{
	if (this->is_null)
		return Nil;
	lua_rawgeti(this->L->get_rawstate(), this->table_position, index);
	return _get_typeof(this->L->get_rawstate());
}

std::vector<const char*> LuaTable::get_all_fields()
{
	std::vector<const char*> ret;
	/* table is in the stack at index 't' */
    lua_pushnil(this->L->get_rawstate());  /* first key */
    while (lua_next(this->L->get_rawstate(), this->table_position) != 0) {
		constexpr int key = -2;
		constexpr int value = -1;

		if (lua_type(this->L->get_rawstate(), key) == LUA_TSTRING)
			ret.push_back(lua_tostring(this->L->get_rawstate(), key));
		
    	lua_pop(this->L->get_rawstate(), 1);
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
	return lua_objlen(this->L->get_rawstate(), this->table_position);
}

bool LuaTable::is_valid()
{
	if (this->is_null 
	|| !lua_istable(this->L->get_rawstate(), this->table_position)
	)
		return false;
	return true;
}