//
// Created by koech on 6/30/2023.
//

#include <malloc.h>
#include "luawrapper.h"


struct LuaWrapper{
    lua_State *L;
    int offset;
    Lua_Wrapper_Status  status;
};

LuaWrapper* wrapperInit(){
    LuaWrapper *luaWrapper = malloc(sizeof(LuaWrapper));
    luaWrapper->L = luaL_newstate();
    if(luaWrapper->L == NULL){
        luaWrapper->status = LUA_WRAPPER_INIT_FAILED;
        wrapperCleanUp(luaWrapper);
        return NULL;
    }
    luaL_openlibs(luaWrapper->L);
    luaWrapper->offset = lua_gettop(luaWrapper->L);
    luaWrapper->status = LUA_WRAPPER_OK;
    return luaWrapper;
}

void wrapperCleanUp(LuaWrapper* luaWrapper){
    if(luaWrapper != NULL){
        lua_close(luaWrapper->L);
        free(luaWrapper);
    }
}

bool loadLuaFile(LuaWrapper* luaWrapper, const char *filename){
    int result = luaL_loadfile(luaWrapper->L, filename);
    if(result != LUA_OK){
        luaWrapper->status = LUA_WRAPPER_LOAD_FAILED;
        lua_close(luaWrapper->L);
        return false;
    }else{
        // execute the loaded chunk
        result = lua_pcall(luaWrapper->L, 0, 0, 0);
        if(result != 0) {
            const char *error = lua_tostring(luaWrapper->L, -1);
            printf("Error: %s\n", error);
            lua_close(luaWrapper->L);
            return false;
        }
        luaWrapper->offset = lua_gettop(luaWrapper->L);
        luaWrapper->status = LUA_WRAPPER_OK;
        return true;
    }
}

void doLuaFile(LuaWrapper* luaWrapper, const char* filename){
    int result = luaL_dofile(luaWrapper->L, filename);
    if(result  != LUA_OK){
        printf("Error: %s\n", lua_tostring(luaWrapper->L, -1));
    }
    lua_settop(luaWrapper->L, 0);// clear the stack;
    luaWrapper->offset = lua_gettop(luaWrapper->L);
}

void doLuaString(LuaWrapper* luaWrapper, const char* luaString){
    int result = luaL_dostring(luaWrapper->L, luaString);
    if(result != LUA_OK){
        printf("Error: %s\n", lua_tostring(luaWrapper->L, -1));
    }
    lua_settop(luaWrapper->L, 0);// clear the stack;
    luaWrapper->offset = lua_gettop(luaWrapper->L);
}

void pushInteger(lua_State *L, int value) {
    lua_pushinteger(L, value);
}

void pushDouble(lua_State *L, double value) {
    lua_pushnumber(L, value);
}

void pushString(lua_State *L, const char *value) {
    lua_pushstring(L, value);
}

void pushBoolean(lua_State *L, bool value) {
    lua_pushboolean(L, value);
}


void call_va(const char *func, const char *sig, ...) {
    va_list vl;
    int narg, nres;  /* number of arguments and results */

    // Check if the function exists in the global environment
    lua_getglobal(L, func);
    if (!lua_isfunction(L, -1)) {
        lua_pop(L, 1); // Remove the non-function value from the stack
        error(L, "function `%s' not found", func);
    }

    va_start(vl, sig);

    // Check available stack space
    int nstack = lua_gettop(L);
    int needed = 0;
    const char *s = sig;
    while (*s) {
        switch (*s++) {
            case 'd':  /* double argument */
            case 'i':  /* int argument */
                needed++;
                break;
            case 's':  /* string argument */
                needed += sizeof(char*);
                break;
            case '>':
                goto endwhile;
            default:
                error(L, "invalid option (%c)", *(s - 1));
        }
    }
    endwhile:

    if (nstack + needed > LUA_MINSTACK) {
        error(L, "stack overflow");
    }

    /* push arguments */
    narg = 0;
    s = sig;
    while (*s) {  /* push arguments */
        switch (*s++) {
            case 'd':  /* double argument */
                lua_pushnumber(L, va_arg(vl, double));
                break;
            case 'i':  /* int argument */
                lua_pushnumber(L, va_arg(vl, int));
                break;
            case 's':  /* string argument */
                lua_pushstring(L, va_arg(vl, char *));
                break;
            case '>':
                goto endargs;
            default:
                error(L, "invalid option (%c)", *(s - 1));
        }
        narg++;
    }
    endargs:

    /* do the call */
    nres = strlen(sig);  /* number of expected results */
    if (lua_pcall(L, narg, nres, 0) != 0)  /* do the call */
        error(L, "error running function `%s': %s", func, lua_tostring(L, -1));

    /* retrieve results */
    nres = -nres;  /* stack index of first result */
    s = sig;
    while (*s) {  /* get results */
        switch (*s++) {
            case 'd':  /* double result */
                if (!lua_isnumber(L, nres))
                    error(L, "wrong result type");
                *va_arg(vl, double *) = lua_tonumber(L, nres);
                break;
            case 'i':  /* int result */
                if (!lua_isnumber(L, nres))
                    error(L, "wrong result type");
                *va_arg(vl, int *) = (int)lua_tonumber(L, nres);
                break;
            case 's':  /* string result */
                if (!lua_isstring(L, nres))
                    error(L, "wrong result type");
                *va_arg(vl, const char **) = lua_tostring(L, nres);
                break;

            default:
                error(L, "invalid option (%c)", *(sig - 1));
        }
        nres++;
    }
    va_end(vl);
}

