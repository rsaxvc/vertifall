extern "C" {
#include "lua5.1/lua.h"
#include "lua5.1/lualib.h"
#include "lua5.1/lauxlib.h"
}

int main()
{
    int s=0;

    lua_State *L = lua_open();

    // load the libs
    luaL_openlibs(L);

    //run a Lua scrip here
    luaL_dofile(L,"foo.lua");

    printf("\nI am done with Lua in C++.\n");

    lua_close(L);

    return 0;
}

