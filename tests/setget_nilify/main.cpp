#include "../../src/LuaCXX.hpp"
#include "../testing.hpp"


int main()
{
	TEST_START(3, LuaTable_TESTS, "Nilifying a table property");

	{
		using namespace LuaCXX;

		const char* main_key = "my_value";
		int main_index = 1;
		const double v = 12.0;

		LuaThread lthread = LuaThread(L);

		LuaTable tb = lthread.new_table();

		ASSERT((tb.get_type(main_key) == LuaType::Nil), 20,"The table key \"" << main_key << "\" is not supposed to have a non-nil value yet.");

		tb.set(main_key, v);
		ASSERT((tb.get_type(main_key) != LuaType::Nil), 23, "The table key \"" << main_key << "\" is supposed to be have non-nil value by now.");

		tb.set_nil(main_key);
		ASSERT((tb.get_type(main_key) == LuaType::Nil), 26, "The table key \"" << main_key << "\" is supposed to have a nil value by now.");

		ASSERT((tb.get_type(main_index) == LuaType::Nil), 28, "The table index " << main_index << " is not supposed to have a non-nil value yet.")

		tb.set(main_index, v);
		ASSERT((tb.get_type(main_index) != LuaType::Nil), 31, "The table index " << main_index << " is supposed to have a non-nil value by now.")

		tb.set_nil(main_index);
		ASSERT((tb.get_type(main_index) == LuaType::Nil), 34, "The table index " << main_index << " is supposed to have a nil value by now");
	}

	TEST_END;

}

