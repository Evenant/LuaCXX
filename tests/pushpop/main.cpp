#include "../../src/LuaCXX.hpp"
#include "../testing.hpp"

int main()
{
	using namespace LuaCXX;
	TEST_START(4, LuaTable_TESTS, "Pushing and Popping values in a Table");

	{
		LuaThread lthread = LuaThread(L);

		LuaTable tb = lthread.new_table();

		{
			//
			LuaTable stb = lthread.new_table();
			tb.push(stb, tb.get_top()+1);
			// tb[1] = stb
		}

		{
			//
			const double n = 1.0;
			tb.push(n, tb.get_top()+1);
			// tb[2] = 1.0
		}

		{
			//
			const bool b = false;
			tb.push(b, tb.get_top()+1);
			// tb[3] = false
		}

		{
			//
			const char* s = "Hello World";
			tb.push(s, tb.get_top()+1);
			// tb[4] = "Hello World"
		}

		ASSERT((tb.get_type(1) == LuaType::Table), 42, "tb[1] is supposed to be a table");
		ASSERT((tb.get_type(2) == LuaType::Number), 43, "tb[2] is supposed to be a number");
		ASSERT((tb.get_type(3) == LuaType::Boolean), 44, "tb[3] is supposed to be a boolean");
		ASSERT((tb.get_type(4) == LuaType::String), 45, "tb[4] is supposed to be a string");

	}

	TEST_END;
}