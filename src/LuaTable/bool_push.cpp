#include "../LuaCXX.hpp"

using namespace LuaCXX;

template<>
void LuaTable::push(const bool& value, int index)
{
	this->move_up(index);
	this->set(index, value);
}

