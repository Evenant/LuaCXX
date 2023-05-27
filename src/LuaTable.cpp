
#include "LuaCXX.hpp"
#include <cstddef>
#include <cstdlib>
#include <vector>

using namespace LuaCXX;

static LuaType _get_type(lua_State* L);



LuaTable::LuaTable(lua_State* thread) : LuaRef(thread)
{
	//
	lua_pushlightuserdata(this->thread, this->key);
	lua_createtable(this->thread, 0, 0);
	lua_settable(this->thread, LUA_REGISTRYINDEX);
	// LUA_REGISTRY[this->key] = {}
}

LuaTable::LuaTable(lua_State* thread, int position) : LuaRef(thread, position)
{
	// Just a handle to the other LuaRef constructor.
}

int LuaTable::get_top()
{
	int bf = lua_gettop(this->thread);

	size_t l;
	if (!this->push_self())
	{
		l = lua_objlen(this->thread, this->position);
	}
	else
	{
		l = lua_objlen(this->thread, -1);
	}

	lua_settop(this->thread, bf);
	return l;
}

std::vector<const char*> LuaTable::get_all_fields()
{
	int bf = lua_gettop(this->thread);

	int tp;
	if (!this->push_self())
	{
		tp = this->position;
	}
	else 
	{
		tp = lua_gettop(this->thread);
	}
	
	std::vector<const char*> v;

	lua_pushnil(this->thread);
	while (lua_next(this->thread, tp))
	{
		constexpr int value = -1;
		constexpr int key = -2;

		// Remove value, now key is on -1
		lua_pop(this->thread, 1);

		if (_get_type(this->thread) == LuaType::String)
			v.push_back(lua_tostring(this->thread, -1));
		
	}

	lua_settop(this->thread, bf);

	return v;
}

void LuaTable::set_self(lua_State *state)
{
	if (this->key)
	{
		lua_pushlightuserdata(this->thread, this->key);
		lua_insert(this->thread, -2);

		lua_settable(this->thread, LUA_REGISTRYINDEX);
	}
	else
	{
		if (this->position != LUA_REGISTRYINDEX
		&& this->position != LUA_GLOBALSINDEX
		&& this->position != LUA_ENVIRONINDEX)
			lua_replace(this->thread, this->position);

	}

}

static LuaType _get_type(lua_State* L)
{
	typedef LuaType Type;
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

	return t;
}

template<>
LuaType LuaTable::get_type(const char* field)
{
	if (!this->push_self())
	{
		lua_pushstring(this->thread, field);
		lua_gettable(this->thread, this->position);
	}
	
	LuaType t = _get_type(this->thread);

	lua_pop(this->thread, -1);

	return t;

}

template<>
LuaType LuaTable::get_type(int index)
{
	if (!this->push_self())
	{
		lua_pushinteger(this->thread, index);
		lua_gettable(this->thread, this->position);
	}
	
	LuaType t = _get_type(this->thread);

	lua_pop(this->thread, -1);

	return t;
}

void LuaTable::move_up(int index)
{
	
	for (int i = this->get_top(); i >= index; i--)
	{
		const LuaType t = this->get_type(i);
		if (t == LuaType::Nil)
		{
			this->set(i+1, void);
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

		switch (this->get_type(i))
		{
			case Nil:
				const LuaNil ln;
				this->set(i+1, ln);
				break;

			case Number:
				const double v = this->get<double>(i);
				this->set(i+1, (double&)this->get<double>(i));
				break;

			case String:
				break;

			case Boolean:
				break;

			case Thread:
				break;

			case None:
				break;

			case Table:
				break;

			case Userdata:
				break;

			case LightUserdata:
				break;

			case Function:
				break;


		}
		this->set(i+1, this->get(i));
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

