#include "../../src/LuaCXX.hpp"
#include "../testing.hpp"
#include <iostream>
#include <cstring>

int main()
{
	using namespace LuaCXX;
	using namespace std;

	TEST_START(2, LuaTable_TESTS, "Setting and Getting Tables.");

	{
		LuaThread luat = LuaThread(L);

		LuaTable car_table = luat.new_table();

		const char* real_wheel = "Wheel";

		const char* carwheels_table_k = "wheels";
		{
			LuaTable carwheels_table = luat.new_table();

			carwheels_table.set(carwheels_table.get_top()+1, real_wheel);
			carwheels_table.set(carwheels_table.get_top()+1, real_wheel);
			carwheels_table.set(carwheels_table.get_top()+1, real_wheel);
			carwheels_table.set(carwheels_table.get_top()+1, real_wheel);

			car_table.set(carwheels_table_k, carwheels_table);
		}

		const bool has_driver = false;
		car_table.set((const char*)"has_driver", has_driver);
		const double km_h = 50.0;
		car_table.set((const char*)"km_h", km_h);

		LuaTable carwheels_table = car_table.get<LuaTable>(carwheels_table_k);

		int wheel_count = 0;

		for (int i = 1;i <= carwheels_table.get_top();i++)
		{
			wheel_count++;
			const char* w = carwheels_table.get<const char*>(i);
			ASSERT((strcmp(w, real_wheel)==0), 45, "There is a wheel that is NOT a wheel.");
		}
		ASSERT(!(wheel_count < 4), 47, "This car does not have enough wheels.");
		ASSERT(!(wheel_count > 4), 48,"This car has too much wheels.");

		ASSERT((!car_table.get<bool>("has_driver")), 50, "HEY THERE IS A THIEF IN THE CAR!");
	}

	TEST_END;
}