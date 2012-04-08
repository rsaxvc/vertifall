//http://gamedevgeek.com/tutorials/calling-c-functions-from-lua/
//http://cc.byexamples.com/2008/06/07/how-to-embed-lua-51-in-c/
//http://csl.sublevel3.org/lua/

#include <cstdio>
#include <cassert>

extern "C"
	{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
	}

enum
	{
	OBJECT_UPDATE_NOTYET,  //not updated yet
	OBJECT_UPDATE_CURRENT, //updating now(id==local_id())
	OBJECT_UPDATE_DONE     //update has happened
	};

enum
	{
	OBJECT_CLASS_PLAYER,
	OBJECT_CLASS_GOON,
	OBJECT_CLASS_DRAGON,
	OBJECT_CLASS_BULLET,
	OBJECT_CLASS_CNT
	};

static const char * object_class_names[]=
{
"player",
"goon",
"dragon"
};

/*sum players+bullets+enemies*/
static int global_num_objects( lua_State * L )
{
assert( lua_gettop( L ) == 0 );
lua_pushinteger( L, 1 );
return 1;
}

/*game updates since start of level*/
static int global_tick_count( lua_State * L )
{
assert( lua_gettop( L ) == 0 );
lua_pushinteger( L, 2435 );
return 1;
}

/*ID of ship AI is controlling*/
static int local_id( lua_State * L )
{
assert( lua_gettop( L ) == 0 );
lua_pushinteger( L, 0 );
return 1;
}

/*bounding box projected a number of gamestates forward*/
static int object_projected_bbox( lua_State * L )
{
assert( lua_gettop( L ) == 2 );

int object_id = lua_tointeger( L, -1 );
lua_pop( L, 1 );

int delta_t = lua_tointeger( L, -1 );
lua_pop( L, 1 );

lua_pushnumber( L, 0 );
lua_pushnumber( L, 1 );
lua_pushnumber( L, 0 );
lua_pushnumber( L, 1 );
lua_pushnumber( L, 0 );
lua_pushnumber( L, 1 );

return 6;
}

static int object_bbox( lua_State * L )
{
lua_pushinteger( L, 0 );
return object_projected_bbox( L );
}

/*tells you what this is*/
static int object_class( lua_State * L )
{
assert( lua_gettop( L ) == 1 );

int object_id = lua_tointeger( L, -1 );
lua_pop( L, 1 );

lua_pushinteger( L, OBJECT_CLASS_GOON );
return 1;
}

static int object_class_name( lua_State * L )
{
assert( lua_gettop( L ) == 1 );

object_class( L );

int object_class = lua_tointeger( L, -1 );
lua_pop( L, 1 );

lua_pushstring( L, object_class_names[object_class] );
return 1;
}

/*a name, possibly unique to the specific object*/
static int object_name( lua_State * L )
{
assert( lua_gettop( L ) == 1 );

int object_id = lua_tointeger( L, -1 );
lua_pop( L, 1 );

lua_pushstring( L, "frank" );
return 1;
}

/*position of object, projected a number of game updates*/
static int object_projected_location( lua_State * L )
{
assert( lua_gettop( L ) == 2 );

int object_id = lua_tointeger( L, -1 );
lua_pop( L, 1 );

int delta_t = lua_tointeger( L, -1 );
lua_pop( L, 1 );

lua_pushnumber( L, (lua_Number)1. );
lua_pushnumber( L, (lua_Number)2. );
lua_pushnumber( L, (lua_Number)3. );
return 3;
}

static int object_location( lua_State * L )
{
assert( lua_gettop( L ) == 1 );
lua_pushinteger( L, 0 );
return object_projected_location( L );
}

static int object_velocity( lua_State * L )
{
assert( lua_gettop( L ) == 1 );

int object_id = lua_tointeger( L, -1 );
lua_pop( L, 1 );

lua_pushnumber( L, (lua_Number)1. );
lua_pushnumber( L, (lua_Number)2. );
lua_pushnumber( L, (lua_Number)3. );
return 3;
}

/*current speed of object*/
static int object_speed( lua_State * L )
{
assert( lua_gettop( L ) == 1 );

int object_id = lua_tointeger( L, -1 );
lua_pop( L, 1 );

lua_pushnumber( L, (lua_Number)1. );
return 1;
}

/*max speed of object*/
static int object_top_speed( lua_State * L )
{
assert( lua_gettop( L ) == 1 );

int object_id = lua_tointeger( L, -1 );
lua_pop( L, 1 );

lua_pushnumber(L, (lua_Number) 1. );
return 1;
}

static int object_update_state( lua_State * L )
{
int object_id = lua_tointeger( L, -1 );
lua_pop( L, 1 );

lua_pushinteger( L, OBJECT_UPDATE_CURRENT );
return 1;
}

#define STRINGIZE_2(_x) #_x
#define STRINGIZE(_x) STRINGIZE_2(_x)
#define ENTRY( _name ) { STRINGIZE( _name ), (_name) }
struct
	{
	const char * name;
	const lua_CFunction func;
	}
const lua_funcs[]=
	{
	//things affecting/accessing current object
	ENTRY( local_id ),

	//things affecting the 'world'
	ENTRY( global_num_objects ),
	ENTRY( global_tick_count ),

	//things for a particular object
	ENTRY( object_projected_bbox ),
	ENTRY( object_bbox ),
	ENTRY( object_projected_location ),
	ENTRY( object_location ),
	ENTRY( object_velocity ),
	ENTRY( object_name ),
	ENTRY( object_top_speed ),
	ENTRY( object_speed ),
	ENTRY( object_name ),
	ENTRY( object_class ),
	ENTRY( object_class_name ),
	ENTRY( object_update_state )
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

	if( luaL_dofile(L,"foo.lua") )
		{
		printf("Lua error:%s\n",lua_tostring( L, 1 ) );
		}

	lua_close(L);
	return 0;
}
