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

		/*
			The Lua thread that will be used by this reference for operations.
		*/
		lua_State* thread;
		
		
		/*
			The Lua registry is used to store references, and this unique pointer is used to identify a reference.
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

		LuaTable new_table(int dict_size=-1, int array_size=-1);
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
		 * @brief Type of values this table can store.
		 * 
		 */
		

		/**
		 * @brief If this handle still points to a table.
		 * 
		 * @return true
		 * @return false 
		 */
		bool is_valid();

		/**
		 * @brief Get the `Type` of the value at the field. Nil is returned if the field does not exist.
		 * also see `get_typeof(int)`.
		 *
		 * @param field 
		 * @return Type 
		 */
		Type get_type(const char* field);

		/**
		 * @brief Similar to `get_typeof(const char*)`.
		 * 
		 * @param index 
		 * @return Type 
		 */
		Type get_type(int index);

		bool get_bool(const char* field);
		void set_bool(const char* field, bool value);

		bool get_bool(int index);
		void set_bool(int index, bool value);

		double get_number(const char* field);
		void set_number(const char* field, double value);

		double get_number(int index);
		void set_number(int index, double value);

		const char* get_string(const char* field);
		void set_string(const char* field, const char* value);

		const char* get_string(int index);
		void set_string(int index, const char* value);
		
		LuaTable get_table(const char* field);
		void set_table(const char* field, LuaTable & value);

		LuaTable get_table(int index);
		void set_table(int index, LuaTable & value);
		/*

		ptr<Lua> get_thread(const char* field);
		ptr<Lua> get_thread(int index);


		void* get_userdata(const char* field);
		void* get_userdata(int index);

		void* get_lightuserdata(const char* field);
		void* get_lightuserdata(int index);

		LuaFunction get_function(const char* field);
		LuaFunction get_function(int index);

		void set_function(const char* field, LuaFunction & value);
		*/

		std::vector<const char*> get_all_fields();
		int array_size();

		constexpr static int default_dict_size = 128;
		constexpr static int default_array_size = 128;

		protected:
		LuaTable(lua_State* th, 
			bool create_table, 
			int table_position, 
			int dict_size=default_dict_size, 
			int array_size=default_array_size
		);

		void add_field();
		void add_index();

		int field_count = 0;
		int index_count = 0;

		lua_State* L;

		private:
		bool is_null = false;



	};

}

#endif