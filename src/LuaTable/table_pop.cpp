#include "../LuaCXX.hpp"

using namespace LuaCXX;

template<>
LuaTable LuaTable::pop(int index)
{
	LuaTable* tb;
	*tb = this->get<LuaTable>(index);
	this->move_down(index);
	return *tb;
}
