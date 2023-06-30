//
// Created by koech on 6/30/2023.
//

#ifndef MPROJECT_LUAUTILS_H
#define MPROJECT_LUAUTILS_H

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include <stdbool.h>

#define push_value(state, value) _Generic(value, int: push_integer, double: push_double, char* : push_string, bool: push_boolean, void : push_cfunc)


lua_State *get_lua_instance();

int load_lua_file(lua_State *L, const char *filename);

void push_integer(lua_State *L, int value);

void push_double(lua_State *L, double value);

void push_string(lua_State *L, const char *value);

void push_boolean(lua_State *L, bool value);

void push_cfunc(lua_State *L, lua_CFunction value)

#endif //MPROJECT_LUAUTILS_H
