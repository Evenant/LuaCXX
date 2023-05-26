#include "../../LuaCXX.hpp"
#include "../testing.hpp"
#include <iostream>

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

			const char * Wheel1_k = "Wheel1";
			carwheels_table.set(carwheels_table.get_top()+1, Wheel1_k);

			const char * Wheel2_k = "Wheel2";
			carwheels_table.set(carwheels_table.get_top()+1, Wheel2_k);

			const char * Wheel3_k = "Wheel3";
			carwheels_table.set(carwheels_table.get_top()+1, Wheel3_k);

			const char * Wheel4_k = "Wheel4";
			carwheels_table.set(carwheels_table.get_top()+1, Wheel4_k);

			car_table.set(carwheels_table_k, carwheels_table);
		}

		const bool has_driver = false;
		car_table.set((const char*)"has_driver", has_driver);
		const double km_h = 50.0;
		car_table.set((const char*)"km_h", km_h);

		LuaTable carwheels_table = car_table.get<LuaTable>(carwheels_table_k);

		for (int i = 1;i <= carwheels_table.get_top();i++)
		{
			std::cout << carwheels_table.get<const char*>(i) << std::endl;
		}

		std::cout << "this car goes at " << car_table.get<double>("km_h") << " kilometers per hour." << std::endl;

		ASSERT((!car_table.get<bool>("has_driver")), "HEY THERE IS A THIEF IN THE CAR!");
	}

	TEST_END;
}