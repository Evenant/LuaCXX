#include "../../src/LuaCXX.hpp"
#include "../testing.hpp"
#include <iostream>
#include <cstring>

int main()
{
	using namespace LuaCXX;
	using namespace std;

	TEST_START(2, 2, "Setting and Getting Tables.");

	{
		LuaThread luat = LuaThread(L);

		LuaTable car_table = luat.new_table();

		const char* carwheels_table_k = "wheels";
		{
			LuaTable carwheels_table = luat.new_table();

			const char * Wheel1_v = "Wheel";
			carwheels_table.set(carwheels_table.get_top()+1, Wheel1_v);

			const char * Wheel2_v = "Wheel";
			carwheels_table.set(carwheels_table.get_top()+1, Wheel2_v);

			const char * Wheel3_v = "Wheel";
			carwheels_table.set(carwheels_table.get_top()+1, Wheel3_v);

			const char * Wheel4_v = "Wheel";
			carwheels_table.set(carwheels_table.get_top()+1, Wheel4_v);

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
			ASSERT((strcmp(carwheels_table.get<const char*>(i), "Wheel")), "There is a wheel that is NOT a wheel.");
		}
		ASSERT(!(wheel_count < 4), "This car does not have enough wheels.");
		ASSERT(!(wheel_count > 4), "This car has too much wheels.");

		ASSERT((!car_table.get<bool>("has_driver")), "HEY THERE IS A THIEF IN THE CAR!");
	}

	TEST_END;
}