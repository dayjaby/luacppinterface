#include "luacppinterface.h"

Lua::Lua() : 
	state(luaL_newstate(), lua_close),
	registry(LuaTable(state, LUA_REGISTRYINDEX)),
	globals(registry.Get<LuaTable>(LUA_RIDX_GLOBALS))
{
}
	
void Lua::LoadStandardLibraries()
{
	luaL_openlibs(state.get());
}

LuaTable Lua::GetRegistry()
{
	return registry;
}

LuaTable Lua::GetGlobalEnvironment()
{
	return globals;
}

LuaTable Lua::CreateTable()
{
	lua_newtable(state.get());
	LuaTable table = LuaTable(state, -1);
	lua_pop(state.get(), 1);
	return table;
}

LuaCoroutine Lua::CreateCoroutine()
{
	lua_newthread(state.get());
	LuaCoroutine thread(state, -1);
	lua_pop(state.get(), 1);
	return thread;
}

std::string Lua::RunScript(std::string script)
{
	int err = luaL_dostring(state.get(), script.c_str());
	if (err != LUA_OK)
	{
		const char* r = lua_tostring(state.get(), -1);
		return r;
	}
	return "No errors";
}

Lua::~Lua()
{
}
