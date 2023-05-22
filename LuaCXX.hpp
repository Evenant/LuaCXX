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

#include <cstddef>
#include <memory>
#include <vector>


namespace LuaCXX
{
	#ifndef lua_h
	typedef struct lua_State lua_State;
	#endif
	
	template<typename T>
	using ptr = std::shared_ptr<T>;

	typedef class Lua Lua;
	typedef class LuaValue LuaValue;
	typedef class LuaTable LuaTable;
	typedef class LuaGTable LuaGTable;
	typedef LuaTable (*LuaFunction)(Lua &, LuaTable &); 

	/**
	 * @brief Represents a Lua thread.
	 * 
	 */
	class Lua
	{
		public:



		bool is_null();

		/**
		 * @brief Construct a new Lua object.
		 * 
		 * @param openlibs Whether to enable the Lua standard library. ( recommended true )
		 */
		Lua(bool openlibs=true);

		~Lua();

		/**
		 * @brief Gets the global table.
		 * 
		 * @return LuaTable 
		 */
		LuaTable globals();

		LuaTable new_table();
		ptr<Lua> new_thread();

		#ifdef lua_h

		operator lua_State*();
		
		/**
		 * @brief Construct a new Lua object from an existing `lua_State`
		 * 
		 * @param state 
		 * @param is_thread 
		 */
		Lua(lua_State *state);
		/**
		 * @brief Get the raw `lua_State*` object.
		 * 
		 * @return lua_State*
		 */
		lua_State* get_rawstate();
		#endif

		private:
		lua_State* state;
		bool is_from_raw_state;
		ptr<LuaTable> _new_table();
		Lua* _new_thread();
		std::vector<ptr<Lua>> sub_threads;

	};
	/**
	 * @brief Represents a handle to an internal Lua table.
	 * 
	 */
	class LuaTable
	{
		public:
		friend class Lua;

		/**
		 * @brief Type of values this table can store.
		 * 
		 */
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
		Type get_typeof(const char* field);

		/**
		 * @brief Similar to `get_typeof(const char*)`.
		 * 
		 * @param index 
		 * @return Type 
		 */
		Type get_typeof(int index);

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

		protected:
		LuaTable(ptr<Lua> L, int fields=0, int indexes=0);
		LuaTable(std::nullptr_t);

		void add_field();
		void add_index();

		int field_count = 0;
		int index_count = 0;

		int table_position;
		ptr<Lua> L;

		private:
		bool is_null = false;

		LuaTable* parent_table;
		~LuaTable();

		int index=0;
		const char* field=nullptr;


	};

	/**
	 * @brief Specifically made to represent the table of globals.
	 * 
	 */
	class LuaGTable: public LuaTable
	{
		friend class Lua;
		protected:
		LuaGTable(Lua* L);
		private:
		~LuaGTable();
	};
}

#endif