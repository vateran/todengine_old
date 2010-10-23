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
#include "tod/core/parameter.h"
#include "tod/core/stopwatch.h"

namespace tod
{
    class TodLuaThread
    {
    public:
        enum ReturnCode
        {
            RETURNCODE_OK,
            RETURNCODE_YIELD,
            RETURNCODE_ERROR,
        };
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
        ReturnCode call(lua_State* s, const String& str, Parameter* param);
        ReturnCode runFile(lua_State* s, const Uri& uri, String* result);

        void waitSecond(const Time& sec);
        void waitFrame(int frame);

        void setYieldMode(YieldMode m);
        YieldMode getYieldMode() const;

    private:
        int key_;
        lua_State* luaStateRoot_;
        lua_State* luaState_;
        YieldMode yieldMode_;
        StopWatch stopWatch_;

        union
        {
            int waitFrame_;
            float waitTime_;
        };

    public:
        static int s_curFrame_;
    };
}

#endif // TOD_CORE_SCRIPT_SCRIPTSERVER_H
