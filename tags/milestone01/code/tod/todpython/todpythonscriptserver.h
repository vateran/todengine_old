#ifndef TOD_TODPYTHON_TODPYTHONSCRIPTSERVER_H
#define TOD_TODPYTHON_TODPYTHONSCRIPTSERVER_H
/**
    @ingroup TodPythonScriptServer
    @class tod::TodPythonScriptServer
    @brief
*/

#include "tod/core/singleton3.h"
#include "tod/core/scriptserver.h"
#include "tod/core/nodeeventsubscriber.h"

namespace tod
{
    class TodPythonScriptServer :
        public ScriptServer,
        public Singleton3<TodPythonScriptServer>
    {
    public:
        TodPythonScriptServer();
        virtual~TodPythonScriptServer();
        DECLARE_CLASS(TodPythonScriptServer, ScriptServer);

        static void initialize();

        override bool run(const String& str, String* result);
        override bool call(
            const String& str,
            Parameter* parameter);
        override bool runFile(const Uri& uri, String* result);

    private:
        class NodeEventSubscriberImpl : public NodeEventSubscriber
        {
        public:
            void onAttachTo(Node* parent, Node* child);
            void onDetachFrom(Node* parent, Node* child);
        };

    public:
        static NodeEventSubscriberImpl nodeEventSubscriber_;

    public:
        static bool s_standAlone_;
    };
}

#endif // TOD_TODPYTHON_TODPYTHONSCRIPTSERVER_H

