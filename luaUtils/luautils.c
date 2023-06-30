//
// Created by koech on 6/30/2023.
//

#include "luautils.h"

lua_State *get_lua_instance() {
    static lua_State *L = NULL;
    if (L == NULL) {
        L = luaL_newstate();
        luaL_openlibs(L);
    }
    return L;
}

int load_lua_file(lua_State *L, const char *filename) {
    int result = luaL_loadfile(L, filename);
    if (result == LUA_OK) {
        result = lua_pcall(L, 0, LUA_MULTRET, 0);
    }
    return result;
}

void push_integer(lua_State *L, int value) {
    lua_pushinteger(L, value);
}

void push_double(lua_State *L, double value) {
    lua_pushnumber(L, value);
}

void push_string(lua_State *L, const char *value) {
    lua_pushstring(L, value);
}

void push_boolean(lua_State *L, bool value) {
    lua_pushboolean(L, value);
}

void push_cfunc(lua_State *L, lua_CFunction value) {
    lua_pushcfunction(L, value);
}
