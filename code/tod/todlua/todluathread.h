#ifndef TOD_TODPYTHON_TODLUASCRIPTSERVER_H
#define TOD_TODPYTHON_TODLUASCRIPTSERVER_H
/**
    @ingroup TodLuaScriptServer
    @class tod::TodLuaThread
    @brief
*/

extern "C"
{
#include "lua/lua.h"
#include "lua/lauxlib.h"
#include "lua/lualib.h"
}

#include "tod/core/uri.h"
#include "tod/engine/stopwatch.h"

namespace tod
{
    class TodLuaThread
    {
    public:
        enum YieldMode
        {
            YIELDMODE_NONE,
            YIELDMODE_FRAME,
            YIELDMODE_TIME,
        };

    public:
        TodLuaThread();
        virtual~TodLuaThread();

        bool update();
        bool runFile(lua_State* s, const Uri& uri, String* result);

        void waitSecond(const Time& sec);

        void setYieldMode(YieldMode m);
        YieldMode getYieldMode() const;

    private:
        lua_State* luaStateRoot_;
        lua_State* luaState_;
        YieldMode yieldMode_;
        engine::StopWatch stopWatch_;

        union
        {
            int waitFrame_;
            float waitTime_;
        };
    };
}

#endif // TOD_CORE_SCRIPT_SCRIPTSERVER_H
