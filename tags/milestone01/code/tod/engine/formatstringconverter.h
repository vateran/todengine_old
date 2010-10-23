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
    class FormatStringConverter : public StringConverter
    {
    public:
        override type_id getTypeId();
        override const char_t* getTypeKeyword() const;
        override const String& toString(
            Object* object, Property* property);
        override void fromString(
            Object* object, Property* property,
            const String& value);

    private:
        String str_;
    };
}
}

#endif // TOD_ENGINE_MAIN_FORMATSTRINGCONVERTER_H
