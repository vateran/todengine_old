#ifndef TOD_ENGINE_MAIN_FORMATSTRINGCONVERTER_H
#define TOD_ENGINE_MAIN_FORMATSTRINGCONVERTER_H
/**
    @ingroup TodEngineGraphicsScene
    @class tod::engine::FormatStringConverter
    @brief 
*/

#include "tod/core/stringconverter.h"

namespace tod
{
namespace engine
{
    class FormatStringConverter : public core::StringConverter
    {
    public:
        override core::type_id getTypeId();
        override const core::char_t* getTypeKeyword() const;
        override const core::String& toString(
            core::Object* object, core::Property* property);
        override void fromString(
            core::Object* object, core::Property* property,
            const core::char_t* value);

    private:
        core::String str_;
    };
}
}

#endif // TOD_ENGINE_MAIN_FORMATSTRINGCONVERTER_H
