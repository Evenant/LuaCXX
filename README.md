# LuaCXX

LuaCXX is a library that makes it easier to use Lua in C++ by providing classes that do most of the heavy lifting behind the scenes.
LuaCXX was also designed to be used in existing C++ projects that still use the raw Lua C API.

## Supported Lua versions
Lua 5.1.* and LuaJIT : Yes
Lua 5.2.* : Not tested
Lua 5.3.* : Not tested
Lua 5.4.* : Not tested

## Building
Run `make` or `make build` to build LuaCXX with default settings.

The LuaCXX library only needs the 3 Lua header files to build: `lua.h`, `lualib.h` and `lauxlib.h`.
By default, LuaCXX will search for these headers in `/usr/include`, you can override this default by setting `INCLUA`.
```sh
# NOTE: it must be a full path
make build ... INCLUA="/path/to/lua-headers"
```

### Running Tests
The tests are here to make sure that LuaCXX does not have problems.
Run `make test` to build and run the tests with default settings.

Unlike the LuaCXX library, the LuaCXX tests need a precompiled Lua library in addition to Lua headers to build.
By default, LuaCXX will use `/usr/lib/liblua.a` as the lua library, you can override this default by setting `LIBLUA`.
```sh
# NOTE: it must be a full path
make test ... LIBLUA="/path/to/liblua.a"
```

When all the tests pass, you can be sure that LuaCXX will work properly.

## Usage

`LuaThread` is the main way that you will use LuaCXX.
```cpp
...
	{ // It is recommended to wrap a LuaThread in braces so that it does not delete itself before previous threads
		using namespace LuaCXX;
		LuaThread lthread = LuaThread(L);

		// Do something
	}
...
```

Creating and manipulating tables.
```cpp
...
	{
		using namespace LuaCXX;
		LuaThread lthread = LuaThread(L);

		LuaTable human = lthread.new_table();

		human.set((const char*)"name", (const char*)"Andrew Tate");
		human.set((const char*)"age", 36.0);
		human.set((const char*)"is_alpha_male", true);

		const char* human_name = human.get<const char*>("name");
		double human_age = human.get<double>("age");
		bool human_is_alpha_male = human.get<bool>("is_alpha_male");

		// Do whatever you want with the Top G now.

	}
...
```

## License
This project is licensed under [GNU Lesser General Public License v3](LICENSE).