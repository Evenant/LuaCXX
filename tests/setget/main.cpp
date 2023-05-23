extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

#include "../../LuaCXX.hpp"
#include "../testing.hpp"

int main(int argc, char **argv)
{
	using namespace LuaCXX;
	using namespace std;
	TEST_START(1, 1, "Set global");

	{
		Lua lua = Lua(true);

		LuaTable lua_globals = lua.globals();


		lua_globals.set_number("greater_than_5", 7.5);



		printf("Set the key \"greater_than_5\" in the global table to %f\n", 7.5);
		double v = lua_globals.get_number("greater_than_5");

		printf("Checking if the value of \"greater_than_5\" ( which is %f ) is greater than 5\n", v);
		ASSERT((v > 5), "The Lua value is not greater than 5!");

		printf("It is greater than 5!\n");

	}


	TEST_END;

	/*
		TODO: Stack Smashing Error occurs for here some reason, fix it.
	*/
	return 0;
}