#include "../LuaCXX.hpp"

using namespace LuaCXX;

void LuaTable::move_up(int index)
{
	
	for (int i = this->get_top(); i >= index; i--)
	{
		const LuaType t = this->get_type(i);
		if (t == LuaType::Nil)
		{
			this->set_nil(i+1);
		}
		else if (t == LuaType::Number)
		{

		}
		else if (t == LuaType::String)
		{

		}
		else if (t == LuaType::Boolean)
		{

		}
		else if (t == LuaType::Thread)
		{

		}
		else if (t == LuaType::None)
		{
			
		}
		else if (t == LuaType::Table)
		{

		}
		else if (t == LuaType::Userdata)
		{

		}
		else if (t == LuaType::LightUserdata)
		{

		}
		else if (t == LuaType::Function)
		{

		}

	}

	return; // dont run the code after this
			// Essentially im saving the code below incase it is useful.
	
	// for cleanup
	int bf = lua_gettop(this->thread);

	// position of the table we are working with
	int tb = 0;

	if (!this->push_self()) // If the value of this reference is on the Lua stack
	{
		tb = this->position;
	}
	else // If the value of this reference is on the Lua registry
	{
		// The table just pushed itself to the top of the stack
		// so do this
		tb = lua_gettop(this->thread);
	}

	
	
	// cleanup
	lua_settop(this->thread, bf);
}

void LuaTable::move_down(int index)
{
	// for cleanup
	int bf = lua_gettop(this->thread);

	// cleanup
	lua_settop(this->thread, bf);
}