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

#include <cstddef>
#include <memory>
#include <vector>


namespace LuaCXX
{

	typedef class LuaRef LuaRef;
	typedef class LuaTable LuaTable;
	typedef class LuaThread LuaThread;

	enum Type
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

	/**
	 * Basic reference to a Lua value.
	 * 
	 */
	class LuaRef
	{
		public:

		void move_into(lua_State* thread);

		~LuaRef();

		protected:
		LuaRef(lua_State* th);
		LuaRef(lua_State* th, int existing_value);

		/*
			The Lua thread that will be used by this reference for operations.
		*/
		lua_State* thread;
		
		/*
			If a reference is used as way to perform operations on a lua value that
			already exists in the stack, then this should be the position of that value in the stack.
		*/
		int position;

		/*
			The Lua registry is used to store references,
			and this unique pointer is used to identify a reference.
		*/
		void* key;
	};

	class LuaThread: public LuaRef
	{
		public:
		/**
		 * Create a thread ( or coroutine ) from an existing Lua state.
		 * If `create_new_thread` is true, then `lua_newthread` is called directly to create
		 * a new thread, otherwise it is assumed that there is already a thread on the top of the 
		 * stack, and takes that instead.
		 */
		LuaThread(lua_State* th, bool create_new_thread=true);
		operator lua_State*();
		lua_State* get_lua();

		LuaTable globals();
		LuaTable registry();

		LuaTable new_table();
		LuaThread new_thread();
		protected:

		lua_State* value_thread;
	};
	/**
	 * @brief Represents a handle to an internal Lua table.
	 * 
	 */
	class LuaTable : public LuaRef
	{
		public:
		friend LuaThread;

		/**
		 * @brief If this handle still points to a table.
		 * 
		 * @return true
		 * @return false 
		 */
		bool is_valid();

		template<class SetValue, class SetSymbol>
		void set(SetSymbol symbol, SetValue& value);

		template<class GetValue, class GetSymbol>
		GetValue get(GetSymbol symbol);

		template<class GetSymbol>
		Type get_type(GetSymbol value);

		int get_top();
		std::vector<const char*> get_all_fields();

		/*
			Assumes that the value on index -1 is a table.
		*/
		void set_self(lua_State* state);

		protected:
		LuaTable(lua_State* th, 
			int table_position
		);

		LuaTable(lua_State* th);
		
		bool push_self();

		/*
		void add_field();
		void add_index();
		*/

		private:



	};

}

#endif