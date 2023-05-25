#include "../../LuaCXX.hpp"
#include "../testing.hpp"

void traverse_table(LuaCXX::LuaTable& tb);

int main()
{
	using namespace LuaCXX;
	using namespace std;

	TEST_START(2, 2, "Setting and Getting Tables.");

	{
		LuaThread luat = LuaThread(L);

		LuaTable car_table = luat.new_table();

		{
			LuaTable carwheels_table = luat.new_table(0, 4);

			carwheels_table.set_string(carwheels_table.array_size(), "Wheel1");
			carwheels_table.set_string(carwheels_table.array_size(), "Wheel2");
			carwheels_table.set_string(carwheels_table.array_size(), "Wheel3");
			carwheels_table.set_string(carwheels_table.array_size(), "Wheel4");

			car_table.set_table("wheels", carwheels_table);
			cout << "After set table in wrapper\n";
		}
		cout << "After set table outside wrapper\n";

		car_table.set_bool("has_driver", true);
		car_table.set_number("km_h", 50.0);

		cout << "Before table traverse\n";
		traverse_table(car_table);
		cout << "After table traverse\n";


	}

	TEST_END;
}
void traverse_table(LuaCXX::LuaTable& tb)
{
	auto v = tb.get_all_fields();

	for (auto i = v.cbegin(); i != v.cend();++i)
	{
		std::cout << *i << std::endl;
		if (tb.get_type(*i) == LuaCXX::Type::Table)
		{
			std::cout << "The above is a table\n";
			auto sub_tb = tb.get_table(*i);
			traverse_table(sub_tb);
		}
	}
}