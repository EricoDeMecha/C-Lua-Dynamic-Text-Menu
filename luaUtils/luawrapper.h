//
// Created by koech on 6/30/2023.
//

#ifndef MPROJECT_LUAUTILS_H
#define MPROJECT_LUAUTILS_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdbool.h>

#define push_value(state, value) \
    _Generic(value, \
    int: pushInteger, \
    double: pushDouble, \
    char* : pushString, \
    bool: pushBoolean)


typedef struct LuaWrapper LuaWrapper;

typedef enum {
    LUA_WRAPPER_OK,
    LUA_WRAPPER_INIT_FAILED,
    LUA_WRAPPER_LOAD_FAILED
}Lua_Wrapper_Status;

// wrapper utils
LuaWrapper* wrapperInit();
void wrapperCleanUp(LuaWrapper* luaWrapper);
bool loadLuaFile(LuaWrapper* luaWrapper, const char *filename);
void doLuaFile(LuaWrapper* luaWrapper, const char* filename);
void doLuaString(LuaWrapper* luaWrapper, const char* luaString);

// pushing values to the stack
void pushInteger(lua_State *L, int value);
void pushDouble(lua_State *L, double value);
void pushString(lua_State *L, const char *value);
void pushBoolean(lua_State *L, bool value);

// calling c functions
void call_va(const char *func, const char *sig, ...);

#endif //MPROJECT_LUAUTILS_H
