#include "../LuaCXX.hpp"

using namespace LuaCXX;

template<>
double LuaTable::pop(int index)
{
	double b = this->get<double>(index);
	this->move_down(index);
	return b;
}
