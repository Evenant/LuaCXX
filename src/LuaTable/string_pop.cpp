#include "../LuaCXX.hpp"

using namespace LuaCXX;

template<>
const char* LuaTable::pop(int index)
{
	const char* b = this->get<const char*>(index);
	this->move_down(index);
	return b;
}
