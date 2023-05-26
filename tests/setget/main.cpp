extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include <string.h>

#include "../../LuaCXX.hpp"
#include "../testing.hpp"

int main(int argc, char **argv)
{
	using namespace LuaCXX;
	using namespace std;
	TEST_START(1, 2, "SetGet Global Table");

	{
		LuaThread luat = LuaThread(L);

		LuaTable gtable = luat.globals();

		// Number
		constexpr const char* keynum = "greater_than_5";
		const double gt_than_5 = 7.5;
		gtable.set(keynum, gt_than_5);
		double vn = gtable.get<double>(keynum);

		ASSERT((vn > 5), "The Lua global table key \"" << keynum << "\" is not greater than 5.");
		
		// Boolean
		constexpr const char* keybool = "should_be_true";
		const bool shld_be_true = true;

		gtable.set(keybool, shld_be_true);
		bool vb = gtable.get<bool>(keybool);

		ASSERT((vb == true), "The Lua global table key \"" << keybool << "\" is not true.");

		// String
		constexpr const char* keystring = "carcolor";
		const char* curr_carcolor = "Red";
		const char* wanted_carcolor = "Yellow";

		gtable.set(keystring, curr_carcolor);
		const char* vs = gtable.get<const char*>(keystring);

		ASSERT((strcmp(vs, wanted_carcolor)), "I WANTED A \"" << wanted_carcolor << "\" CAR MOM! NOT A \"" << vs << "\"");

	}

	TEST_END;
}