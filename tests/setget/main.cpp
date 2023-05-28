extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include <string.h>

#include "../../src/LuaCXX.hpp"
#include "../testing.hpp"

int main(int argc, char **argv)
{
	using namespace LuaCXX;
	using namespace std;
	TEST_START(1, LuaTable_TESTS, "Setting and Getting Lua's global table and registry table");

	{ // Globals table
		LuaThread luat = LuaThread(L);

		LuaTable gtable = luat.globals();
		{ // Number
			constexpr const char* keynum = "greater_than_5";
			const double gt_than_5 = 7.5;
			gtable.set(keynum, gt_than_5);

			ASSERT((gtable.get_type(keynum) == LuaType::Number), 28, "The key \""<< keynum << "\" should be a number")

			double vn = gtable.get<double>(keynum);
			ASSERT((vn > 5), 31, "The Lua global table key \"" << keynum << "\" is not greater than 5.");
		} // Number

		{// Boolean
			constexpr const char* keybool = "should_be_true";
			const bool shld_be_true = true;
			gtable.set(keybool, shld_be_true);

			ASSERT((gtable.get_type(keybool) == LuaType::Boolean), 39, "The key \"" << keybool << "\" should be a boolean");

			bool vb = gtable.get<bool>(keybool);
			ASSERT((vb == true), 42, "The Lua global table key \"" << keybool << "\" is not true.");
		} // Boolean

		{// String
			constexpr const char* keystring = "carcolor";
			const char* curr_carcolor = "Red";
			const char* wanted_carcolor = "Yellow";
			gtable.set(keystring, curr_carcolor);

			ASSERT((gtable.get_type(keystring) == LuaType::String), 51, "The key \"" << keystring << "\" should be a string")

			const char* vs = gtable.get<const char*>(keystring);
			ASSERT((strcmp(vs, wanted_carcolor)), 54, "I WANTED A \"" << wanted_carcolor << "\" CAR MOM! NOT A \"" << vs << "\"");
		} // String
		
		{ // Table
			constexpr const char* keytable = "organs";

			LuaTable tb = luat.new_table();
			const char* v1 = "Heart";
			tb.push(v1, tb.get_top()+1); // tb[1] = "Heart"

			const char* v2 = "Lungs";
			tb.push(v2, tb.get_top()+1); // tb[2] = "Lungs"

			const char* v3 = "Liver";
			tb.push(v3, tb.get_top()+1); // tb[3] = "Liver"

			gtable.set(keytable, tb);

			ASSERT((gtable.get_type(keytable) == LuaType::Table), 72, "The key \"" << keytable << "\" should be a table")

			LuaTable tb_ = gtable.get<LuaTable>(keytable);

			ASSERT((strcmp(tb_.get<const char*>(1), "Heart") == 0), 76, "tb_[1] is supposed to be \"Heart\"");
			ASSERT((strcmp(tb_.get<const char*>(2), "Lungs") == 0), 77, "tb_[2] is supposed to be \"Lungs\"");
			ASSERT((strcmp(tb_.get<const char*>(3), "Liver") == 0), 78, "tb_[3] is supposed to be \"Liver\"");

		} // Table
	} // Globals table
	
	{ // Registry table
		LuaThread luat = LuaThread(L);

		LuaTable gtable = luat.globals();
		{ // Number
			constexpr const char* keynum = "greater_than_5";
			const double gt_than_5 = 7.5;
			gtable.set(keynum, gt_than_5);

			ASSERT((gtable.get_type(keynum) == LuaType::Number), 92, "The key \""<< keynum << "\" should be a number")

			double vn = gtable.get<double>(keynum);
			ASSERT((vn > 5), 95, "The Lua global table key \"" << keynum << "\" is not greater than 5.");
		} // Number

		{// Boolean
			constexpr const char* keybool = "should_be_true";
			const bool shld_be_true = true;
			gtable.set(keybool, shld_be_true);

			ASSERT((gtable.get_type(keybool) == LuaType::Boolean), 103, "The key \"" << keybool << "\" should be a boolean");

			bool vb = gtable.get<bool>(keybool);
			ASSERT((vb == true), 106, "The Lua global table key \"" << keybool << "\" is not true.");
		} // Boolean

		{// String
			constexpr const char* keystring = "carcolor";
			const char* curr_carcolor = "Red";
			const char* wanted_carcolor = "Yellow";
			gtable.set(keystring, curr_carcolor);

			ASSERT((gtable.get_type(keystring) == LuaType::String), 115, "The key \"" << keystring << "\" should be a string")

			const char* vs = gtable.get<const char*>(keystring);
			ASSERT((strcmp(vs, wanted_carcolor)), 118, "I WANTED A \"" << wanted_carcolor << "\" CAR MOM! NOT A \"" << vs << "\"");
		} // String
		
		{ // Table
			constexpr const char* keytable = "organs";

			LuaTable tb = luat.new_table();
			const char* v1 = "Heart";
			tb.push(v1, tb.get_top()+1); // tb[1] = "Heart"

			const char* v2 = "Lungs";
			tb.push(v2, tb.get_top()+1); // tb[2] = "Lungs"

			const char* v3 = "Liver";
			tb.push(v3, tb.get_top()+1); // tb[3] = "Liver"

			gtable.set(keytable, tb);

			ASSERT((gtable.get_type(keytable) == LuaType::Table), 136, "The key \"" << keytable << "\" should be a table")

			LuaTable tb_ = gtable.get<LuaTable>(keytable);

			ASSERT((strcmp(tb_.get<const char*>(1), "Heart") == 0), 140, "tb_[1] is supposed to be \"Heart\"");
			ASSERT((strcmp(tb_.get<const char*>(2), "Lungs") == 0), 141, "tb_[2] is supposed to be \"Lungs\"");
			ASSERT((strcmp(tb_.get<const char*>(3), "Liver") == 0), 142, "tb_[3] is supposed to be \"Liver\"");

		} // Table
	} // Registry table

	TEST_END;
}