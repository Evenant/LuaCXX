#include "../LuaCXX.hpp"

using namespace LuaCXX;

void LuaTable::move_up(int index)
{
	for (int i = this->get_top(); i >= index; i--)
	{
		const LuaType t = this->get_type(i);
		if (t == LuaType::Number)
		{
			const double v = this->get<double>(i);
			this->set(i+1, v);
		}
		else if (t == LuaType::String)
		{
			const char* v = this->get<const char*>(i);
			this->set(i+1, v);
		}
		else if (t == LuaType::Boolean)
		{
			bool v = this->get<bool>(i);
			this->set(i+1, v);
		}
		/* TODO
			Implement a way for tables to set a LuaThread via `LuaTable::set`, and then
			come back here and use it here
		
		else if (t == LuaType::Thread)
		{
		}
		*/
		else if (t == LuaType::Table)
		{
			LuaTable v = this->get<LuaTable>(i);
			this->set(i+1, v);
		}
		/* TODO
			Implement a way to create Userdata objects from a C++ class.

			after that:

			Implement a way for tables to set a Userdata via `LuaTable::set`, and then
			come back here and use it here.

		else if (t == LuaType::Userdata)
		{
		}
		*/
		/* TODO
			Implement a way for tables to set a void* pointer ( aka a Lua light userdata ) via `LuaTable::set`, and then
			come back here and use it here

		else if (t == LuaType::LightUserdata)
		{
		}
		*/
		/* TODO
			Implement a way for LuaCXX to create functions that function similarly to Lua C Functions

			after that:

			Implement a way for tables to set a LuaCXX Lua function via `LuaTable::set`, and then
			come back here and use it here

		else if (t == LuaType::Function)
		{

		}
		*/
		else
		{
			this->set_nil(i+1);
		}

	}
}

void LuaTable::move_down(int index)
{
	// for cleanup
	int bf = lua_gettop(this->thread);

	// cleanup
	lua_settop(this->thread, bf);
}