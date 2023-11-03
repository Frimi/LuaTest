

#ifndef LUAINTERFACE_H_
#define LUAINTERFACE_H_

#include "lua.h"

//
#define LUA_INTERFACE_LIBS {"uc", luaopen_uc}


LUAMOD_API int (luaopen_uc) (lua_State *L);


#define lua_writestring(s,l)   			printf("%.*s", l, (uint8_t*)s);
#define lua_writestringWithoutsize(s)   printf("%s", (uint8_t*)s);
#define lua_writeline()        			printf("\n");
#define lua_writestringerror(s,l)   	printf("%.*s", (int)l, (uint8_t*)s);

#endif /* LUAINTERFACE_H_ */
