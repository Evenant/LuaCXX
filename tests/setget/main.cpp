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
	TEST_START(1, 1, "SetGet Global Table");

	lua_State* L = luaL_newstate();
	{
		LuaThread luat = LuaThread(L, true);

		LuaTable gtable = luat.globals();

		// Number
		constexpr const char* keynum = "greater_than_5";

		gtable.set_number(keynum, 7.5);
		double vn = gtable.get_number(keynum);

		ASSERT((vn > 5), "The Lua global table key \"" << keynum << "\" is not greater than 5.");
		
		// Boolean
		constexpr const char* keybool = "should_be_true";

		gtable.set_bool(keybool, true);
		bool vb = gtable.get_bool(keybool);

		ASSERT((vb == true), "The Lua global table key \"" << keybool << "\" is not true.");

		// String
		constexpr const char* keystring = "carcolor";
		constexpr const char* curr_carcolor = "Red";
		constexpr const char* wanted_carcolor = "Yellow";

		gtable.set_string(keystring, curr_carcolor);
		const char* vs = gtable.get_string(keystring);

		ASSERT((strcmp(vs, wanted_carcolor)), "I WANTED A \"" << wanted_carcolor << "\" CAR MOM! NOT A \"" << vs << "\"");

	}

	lua_close(L);

	TEST_END;
	return 0;
}