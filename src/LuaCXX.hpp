/**
 * @file LuaCXX.hpp
 * @author Evenant (https://github.com/Evenant)
 * @brief The header file for all of LuaCXX
 * @version 0.1
 * @date 2023-05-22
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef LUACXX_HPP
#define LUACXX_HPP

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include <vector>


namespace LuaCXX
{
	/*
		Reference for a value in Lua ( either on the Lua stack or in the Lua registry ).
	*/
	typedef class LuaRef LuaRef;

	/*
		Reference to a Lua table.
	*/
	typedef class LuaTable LuaTable;

	/*
		Reference to a Lua thread.
	*/
	typedef class LuaThread LuaThread;

	/*
		A struct specifically for representing a Lua nil value.
	*/
	typedef struct LuaNil {} LuaNil;

	/*
		Types of Lua values
	*/
	enum LuaType
	{
		Nil,
		Number,
		String,
		Boolean,
		Thread,
		None,
		Table,
		Userdata,
		LightUserdata,
		Function
	};

	class LuaRef
	{
		public:

		void move_into(lua_State* thread);

		~LuaRef();

		protected:
		LuaRef(lua_State* th);
		LuaRef(lua_State* th, int existing_value);

		/*
			Push this reference's value onto the stack, returns false if this is actually a reference to a value that
			already exists on the stack.
		*/
		bool push_self();

		/*
			The Lua thread that will be used by this reference for operations.
		*/
		lua_State* thread;
		
		/*
			If a reference is used as way to perform operations on a Lua value that
			already exists in the stack, then this should be the position of that value in the stack.
		*/
		int position;

		/*
			If a reference is used as a way to perform operations on a Lua value that exists in the
			Lua registry, this should be the key of the value in the registry.
		*/
		void* key;
	};

	class LuaThread: public LuaRef
	{
		public:
		/*
			Create a thread ( or coroutine ) from an existing Lua state.
		*/
		LuaThread(lua_State* th);

		operator lua_State*();
		lua_State* get_lua();

		/*
			Lua's globals table, used for storing data accessible to all of Lua.
		*/
		LuaTable globals();

		/*
			Lua's registry, used for storing data that only meant to be used by external libraries and not Lua itself.
		*/
		LuaTable registry();

		LuaTable new_table();
		LuaThread new_thread();
		protected:

		lua_State* value_thread;
	};
	
	class LuaTable : public LuaRef
	{
		public:
		friend LuaThread;

		/*
			Set a value
		*/
		template<class SetValue, class SetSymbol>
		void set(SetSymbol symbol, SetValue& value);

		template<class SetSymbol>
		void set_nil(SetSymbol symbol);


		/*
			Get a value
		*/
		template<class GetValue, class GetSymbol>
		GetValue get(GetSymbol symbol);

		/*
			Get the type of the value
		*/
		template<class GetSymbol>
		LuaType get_type(GetSymbol value);

		/*
			Push and Pop operations, as if this table were an array.
		*/

		/*
			Push `value` into `index`.
			Moves elements in and above `index` upwards.
		*/
		template <class Value>
		void push(Value value, int index);

		/*
			Pop `value` from `index` and returns it.
			Moves elements above `index` downwards.
		*/
		template <class Value>
		Value pop(int index);

		protected:

		/*
			Move values in and above `index` upwards by 1 index.
			Leaving the value at `index` as nil.
		*/
		void move_up(int index);
		
		/*
			Move values above `index` downwards by 1 index.
			Replaces the value at `index` with the value above `index`.
		*/
		void move_down(int index);

		public:

		/*
			Get the top of this table ( or its length ),
			take this and add 1 to get the next index to add a value to via `LuaTable::set`
		*/
		int get_top();

		/*
			Get all the fields of this table.
		*/
		std::vector<const char*> get_all_fields();

		/*
			Sets this table to the table on index -1;
			Assumes that the value on index -1 is a table.
		*/
		void set_self(lua_State* state);

		protected:
		LuaTable(lua_State* th, 
			int table_position
		);

		LuaTable(lua_State* th);
		
		

	};

}

#endif
