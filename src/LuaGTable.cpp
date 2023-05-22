#include "lua_i.hpp"
#include "../LuaCXX.hpp"

using namespace LuaCXX;

LuaGTable::LuaGTable(Lua* L) : LuaTable(L, 0, 0)
{
	lua_getglobal(this->L->get_rawstate(), "_G");
	this->table_position=lua_gettop(this->L->get_rawstate());
};

LuaGTable::~LuaGTable()
{
	lua_pushvalue(this->L->get_rawstate(), this->table_position);
	lua_setfield(this->L->get_rawstate(),LUA_GLOBALSINDEX,"_G");

}