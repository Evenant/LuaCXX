#include "../LuaCXX.hpp"

using namespace LuaCXX;

template<>
void LuaTable::push(const double& value, int index)
{
	this->move_up(index);
	this->set(index, value);
}

