#include "../LuaCXX.hpp"

using namespace LuaCXX;

template<>
bool LuaTable::pop(int index)
{
	bool b = this->get<bool>(index);
	this->move_down(index);
	return b;
}
