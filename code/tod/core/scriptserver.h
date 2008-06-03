#ifndef TOD_CORE_SCRIPT_SCRIPTSERVER_H
#define TOD_CORE_SCRIPT_SCRIPTSERVER_H
/**
    @ingroup TodCoreScriptServer
    @class tod::ScriptServer
    @brief
*/

#include "tod/core/node.h"
#include "tod/core/primitivetype.h"
#include "tod/core/uri.h"

namespace tod
{
    class Argument;
    class ReturnValue;
    class Object;
    class ScriptServer : public Node
    {
    public:
        DECLARE_CLASS(ScriptServer, Node);

        virtual bool run(
            const char_t* str,
            Parameter* parameter);
        virtual bool run(const Uri& uri);
    };
}

#endif // TOD_CORE_SCRIPT_SCRIPTSERVER_H
