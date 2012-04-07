//http://csl.sublevel3.org/lua/

#include <cstdio>

extern "C"
	{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
	}
int main()
{
    lua_State *L = lua_open();

    luaL_openlibs(L);

    luaL_dofile(L,"foo.lua");

    lua_close(L);
    return 0;
}
