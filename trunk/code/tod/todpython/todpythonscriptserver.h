#ifndef TOD_TODPYTHON_TODPYTHONSCRIPTSERVER_H
#define TOD_TODPYTHON_TODPYTHONSCRIPTSERVER_H
/**
    @ingroup TodPythonScriptServer
    @class tod::core::ScriptServer
    @brief
*/

#include "tod/core/scriptserver.h"

namespace tod
{
namespace engine
{
namespace script
{
    class TodPythonScriptServer : public core::ScriptServer
    {
    public:
        TodPythonScriptServer();
        virtual~TodPythonScriptServer();
        DECLARE_CLASS(TodPythonScriptServer, core::ScriptServer);

        static void initialize();

        override bool run(
            const core::char_t* str,
            core::Parameter* parameter);
        override bool run(const core::Uri& uri);

    public:
        static bool s_standAlone_;
    };
}
}
}

#endif // TOD_CORE_SCRIPT_SCRIPTSERVER_H
