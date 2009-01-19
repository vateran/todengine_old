#ifndef TOD_TODLUA_TODLUAFUNC_H
#define TOD_TODLUA_TODLUAFUNC_H

extern "C"
{
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
}

#include "tod/core/ref.h"
#include "tod/core/node.h"

struct TodLuaObject
{
    tod::Object* object_;
};

extern int luacmd_StackDump(lua_State* s);
extern int luacmd_ResRoot(lua_State* s);
extern int luacmd_NewObj(lua_State* s);
extern int luacmd_New(lua_State* s);
extern int luacmd_Get(lua_State* s);
extern int luacmd_Delete(lua_State* s);
extern int luacmd_Ls(lua_State* s);
extern int luacmd_PushCwn(lua_State* s);
extern int luacmd_PopCwn(lua_State* s);
extern int luacmd_TodPrint(lua_State* s);
extern int luacmd_Exit(lua_State* s);
extern int luacmd_Serialize(lua_State* s);
extern int luacmd_Deserialize(lua_State* s);
extern int luacmd_GetModuleList(lua_State* s);
extern int luacmd_GetTypeList(lua_State* s);
extern int luacmd_Invoke(lua_State* s);
extern int luacmd_Del(lua_State* s);
extern int luacmd_Panic(lua_State* s);
extern int luacmd_WaitSec(lua_State* s);

#endif // TOD_TODLUA_TODLUAFUNC_H
