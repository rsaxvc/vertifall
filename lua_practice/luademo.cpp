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

static int my_name( lua_State * L )
{
lua_pushstring(L,"frank");
return 1;
}

static int my_location( lua_State * L )
{
lua_pushnumber(L, (lua_Number)1. );
lua_pushnumber(L, (lua_Number)2. );
return 2;
}

#define STRINGIZE_2(_x) #_x
#define STRINGIZE(_x) STRINGIZE_2(_x)

#define FUNC_TABLE_ENTRY( _name ) { STRINGIZE( _name ), (_name) }
struct
	{
	const char * name;
	const lua_CFunction func;
	}
const lua_funcs[]=
	{
	FUNC_TABLE_ENTRY( my_location ),
	FUNC_TABLE_ENTRY( my_name ),
	};

static void register_functions( lua_State * L )
{
size_t i;
for( i = 0; i < sizeof( lua_funcs ) / sizeof( lua_funcs[0] ); ++i )
	{
	lua_register( L, lua_funcs[i].name, lua_funcs[i].func );
	}
}

int main()
{
    lua_State *L = lua_open();
    luaL_openlibs(L);
	register_functions(L);

    luaL_dofile(L,"foo.lua");

    lua_close(L);
    return 0;
}
