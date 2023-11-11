
#include "luaInterface.h"

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

//#include "FreeRTOS.h"
//#include "semphr.h"
bool panic_state = false;
//This function is called by Lua cannot handle an occured error.
void luaAbort(void)
{
  lua_writestringerror("luaAbort", sizeof("luaAbort"));
  while(1){}
}

int get_tick(lua_State *L)
{
  uint32_t tick = HAL_GetTick();
  // Empurra o resultado (valor do tick) para a pilha Lua
  lua_pushinteger(L, tick);

  printf("TICK:%lu \n", tick);

  // Indica que uma variável (1 valor) está sendo retornada para Lua
  return 1;
}

int button_status(lua_State *L)
{
  // Empurra o resultado para a pilha Lua
  lua_pushboolean(L, button_state());

  // Indica que uma variável (1 valor) está sendo retornada para Lua
  return 1;
}

int panic_status(lua_State *L)
{
  // Empurra o resultado para a pilha Lua
  lua_pushboolean(L, panic_state);

  // Indica que uma variável (1 valor) está sendo retornada para Lua
  return 1;
}

int func1(lua_State *L)
{
  size_t size;
  const char *message = luaL_checklstring(L, 1, &size);

  const char* msg = "C func1:";
  lua_writestring(msg, strlen(msg));
  lua_writestring(message, size);
  lua_writeline();

  //Cleanup the stack.
  int n = lua_gettop(L);
  lua_pop(L, n);


  //Create the result.
  lua_pushinteger(L, 1);
  lua_pushinteger(L, 2);

  return 2;//2 results
}

int func2(lua_State *L)
{
  luaL_checktype(L, 1, LUA_TTABLE);

  lua_settop(L, 1);


  const char* msg = "C func2:";
  lua_writestring(msg, strlen(msg));


  lua_gettable(L, 1);

  //Add dummy value for the last lua_pop.
  lua_pushnil(L);

  while(lua_next(L, -2))
  {
    lua_Integer b = (int)lua_tonumber(L, -1);
    char value = 48 + b;
    lua_writestring(" ", 1);
    lua_writestring(&value, 1);
    lua_pop(L, 1);
  }

  lua_writeline();

  //Cleanup the stack.
  int n = lua_gettop(L);
  lua_pop(L, n);


  //Create the result.
  lua_newtable(L);
  lua_pushinteger(L, 5);
  lua_rawseti(L, -2, 0);
  lua_pushinteger(L, 9);
  lua_rawseti(L, -2, 1);

  return 1;
}

int counter(lua_State *L)
{
  static uint32_t counter = 0;

  counter++;
  lua_pushinteger(L, counter);
  return 1;
}

int scriptSemaphore(lua_State *L)
{
  return 0;
}

int taskDelay(lua_State *L)
{
  int delay = (int)lua_tonumber(L, -1);
  HAL_Delay(delay);
  return 0;
}

static const luaL_Reg uC_funcs[] = {
  {"func1", func1},
  {"func2", func2},
  {"counter", counter},
  {"scriptSemaphore", scriptSemaphore},
  {"taskDelay", taskDelay},
  {"get_tick", get_tick},
  {"button_status", button_status},
  {"panic_status", panic_status},
  {NULL, NULL}
};


LUAMOD_API int luaopen_uc (lua_State *L) {
  luaL_newlib(L, uC_funcs);
  return 1;
}
