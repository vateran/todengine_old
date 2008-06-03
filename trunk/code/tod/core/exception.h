#ifndef TOD_CORE_UTILITY_EXCEPTION_H
#define TOD_CORE_UTILITY_EXCEPTION_H
/**
    @ingroup TodCoreException
    @class tod::Exception
    @brief 
*/

#include <list>
#include <exception>
#include "tod/core/define.h"
#include "tod/core/string.h"
#include "tod/core/singleton.h"

namespace tod
{
    class Exception : public std::exception
    {
    public:
        Exception(
            int error_code, int line, const String& file,
            const String& function, const String& description);

        void setErrorCode(int error_code);
        void setLine(int line);
        void setFile(const String& file);
        void setFunction(const String& function);
        void setDescription(const String& description);

        int getErrorCode() const;
        int getLine() const;
        const String& getFile() const;
        const String& getFunction() const;
        const String& getDescription() const;
        String getFullDescription() const;

    private:
        int errorCode_;
        int line_;
        String file_;
        String function_;
        String description_;
    };
    
    class ExceptionHandler
    {
    public:
        virtual void handle(const Exception& e)=0;
    };

    class ThrowExceptionHandler : public ExceptionHandler
    {
    public:
        override void handle(const Exception& e);
    };

    class MessageBoxExceptionHandler : public ExceptionHandler
    {
    public:
        override void handle(const Exception& e);
    };

    class ExceptionManager : public Singleton<ExceptionManager>
    {
    public:
        ExceptionManager()
        {
            add(new MessageBoxExceptionHandler);
        }
        virtual~ExceptionManager()
        {
            for (ExceptionHandlers::iterator i = handlers_.begin();
                 i != handlers_.end(); ++i)
                delete *i;
        }

        void add(ExceptionHandler* handler)
        {
            handlers_.push_back(handler);
        }
        void handle(const Exception& e)
        {
            for (ExceptionHandlers::iterator i = handlers_.begin();
                 i != handlers_.end(); ++i)
                 (*i)->handle(e);
        }

    private:
        typedef std::list<ExceptionHandler*> ExceptionHandlers;

    private:
        ExceptionHandlers handlers_;
    };

#define TOD_THROW_EXCEPTION(err_code, desc) \
    ExceptionManager::instance()->handle(tod::Exception(\
        err_code, ___LINE___, ___FILE___, ___FUNCTION___, desc));

enum TodExceptionCode
{
    TODEXCEPTIONCODE_RESOURCEOPEN,
};

}

#endif // TOD_CORE_UTILITY_EXCEPTION_H
