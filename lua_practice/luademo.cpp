//http://gamedevgeek.com/tutorials/calling-c-functions-from-lua/
//http://cc.byexamples.com/2008/06/07/how-to-embed-lua-51-in-c/
//http://csl.sublevel3.org/lua/

#include <cstdio>

extern "C"
	{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
	}

static int average( lua_State * L )
{
	/* get number of arguments */
	int n = lua_gettop(L);
	double sum = 0;
	int i;

	/* loop through each argument */
	for (i = 1; i <= n; i++)
	{
		/* total the arguments */
		sum += lua_tonumber(L, i);
	}

	/* push the average */
	lua_pushnumber(L, sum / n);

	/* push the sum */
	lua_pushnumber(L, sum);

	/* return the number of results */
	return 2;
}

int main()
{
    lua_State *L = lua_open();
    luaL_openlibs(L);
	lua_register(L, "average", average);

    luaL_dofile(L,"foo.lua");

    lua_close(L);
    return 0;
}
