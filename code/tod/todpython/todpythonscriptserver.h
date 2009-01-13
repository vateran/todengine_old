#ifndef TOD_TODPYTHON_TODPYTHONSCRIPTSERVER_H
#define TOD_TODPYTHON_TODPYTHONSCRIPTSERVER_H
/**
    @ingroup TodPythonScriptServer
    @class tod::ScriptServer
    @brief
*/

#include "tod/core/scriptserver.h"

namespace tod
{
    class TodPythonScriptServer : public ScriptServer
    {
    public:
        TodPythonScriptServer();
        virtual~TodPythonScriptServer();
        DECLARE_CLASS(TodPythonScriptServer, ScriptServer);

        static void initialize();

        override bool run(const String& str);
        override bool call(
            const String& str,
            Parameter* parameter);
        override bool runFile(const Uri& uri);

    public:
        static bool s_standAlone_;
    };
}

#endif // TOD_CORE_SCRIPT_SCRIPTSERVER_H
