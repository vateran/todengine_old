#ifndef TOD_CORE_UTILITY_CURRENTSNAPSHOT_H
#define TOD_CORE_UTILITY_CURRENTSNAPSHOT_H
/**
    @ingroup TodCoreException
    @class tod::core::CurrentSnapShot
    @brief 
*/

#include "tod/core/primitivetype.h"
#include "tod/core/string.h"

namespace tod
{
namespace core
{
    class CurrentSnapShot
    {
    public:
        CurrentSnapShot();
        CurrentSnapShot(const char_t* type, const char_t* date,
            const char_t* time, const char_t* file_name,
            const char_t* func_sig, const char_t* func_name, int line,
            const char_t* expression);

        void setSemantic(const char_t* type, const char_t* date,
            const char_t* time, const char_t* file_name,
            const char_t* func_sig, const char_t* func_name, int line,
            const char_t* expression);

    public:
        String type_;
        String date_;
        String time_;
        String fileName_;
        String functionSignature_;
        String functionName_;
        int line_;
        String expression_;
    };

#include "tod/core/currentsnapshot.inl"

}
}

#endif // TOD_CORE_UTILITY_CURRENTSNAPSHOT_H
