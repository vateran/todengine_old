#ifndef TOD_ENGINE_GRAPHICS_CORE_FORMAT_H
#define TOD_ENGINE_GRAPHICS_CORE_FORMAT_H
/**
    @ingroup TodEngineGraphicsCore
    @enum tod::engine::graphics::Format
    @brief 
*/

#include "tod/core/define.h"
#include "tod/core/primitivetype.h"
#include "tod/core/string.h"

namespace tod
{
namespace engine
{
namespace graphics
{
    class Format
    {
    public:
        enum Value
        {
            UNKNOWN              =  0,

            R8G8B8               = 20,
            A8R8G8B8             = 21,
            X8R8G8B8             = 22,
            R5G6B5               = 23,
            X1R5G5B5             = 24,
            A1R5G5B5             = 25,
            A4R4G4B4             = 26,
            R3G3B2               = 27,
            A8                   = 28,
            A8R3G3B2             = 29,
            X4R4G4B4             = 30,
            A2B10G10R10          = 31,
            G16R16               = 34,

            A8P8                 = 40,
            P8                   = 41,

            L8                   = 50,
            A8L8                 = 51,
            A4L4                 = 52,

            V8U8                 = 60,
            L6V5U5               = 61,
            X8L8V8U8             = 62,
            Q8W8V8U8             = 63,
            V16U16               = 64,
            W11V11U10            = 65,
            A2W10V10U10          = 67,

            UYVY                 = tod_MAKEFOURCC('U', 'Y', 'V', 'Y'),
            YUY2                 = tod_MAKEFOURCC('Y', 'U', 'Y', '2'),
            DXT1                 = tod_MAKEFOURCC('D', 'X', 'T', '1'),
            DXT2                 = tod_MAKEFOURCC('D', 'X', 'T', '2'),
            DXT3                 = tod_MAKEFOURCC('D', 'X', 'T', '3'),
            DXT4                 = tod_MAKEFOURCC('D', 'X', 'T', '4'),
            DXT5                 = tod_MAKEFOURCC('D', 'X', 'T', '5'),

            D16_LOCKABLE         = 70,
            D32                  = 71,
            D15S1                = 73,
            D24S8                = 75,
            D16                  = 80,
            D24X8                = 77,
            D24X4S4              = 79,

            VERTEXDATA           = 100,
            INDEX16              = 101,
            INDEX32              = 102,

            D32_LOCKABLE         = 84,
            S8_LOCKABLE          = 85,

            L16                  = 81,

            Q16W16V16U16         = 110,

            MULTI2_ARGB8         = tod_MAKEFOURCC('M','E','T','1'),

            // Floating point surface formats
            // s10e5 formats (16-bits per channel)
            R16F                 = 111,
            G16R16F              = 112,
            A16B16G16R16F        = 113,

            // IEEE s23e8 formats (32-bits per channel)
            R32F                 = 114,
            G32R32F              = 115,
            A32B32G32R32F        = 116,

            CxV8U8               = 117,

            // Monochrome 1 bit per pixel format
            A1                   = 118,

            INVALID              = 0xffffffff,
            FORCE_DWORD          = 0x7fffffff
        };

    public:
        class enumerator
        {
        public:
            enumerator();
            enumerator(Value value);
            Format operator * () const;            
            operator Format () const
            {
                return Format(s_values[index_]);
            }
            void operator ++ () const;
            bool operator == (const enumerator& lhs) const;
            bool operator != (const enumerator& lhs) const;

        private:
            mutable int index_;

        private:
            static Value s_values[];
            static int s_size;

        };
        typedef const enumerator const_enumerator;

    public:
        Format();
        Format(const core::char_t* str);
        Format(const core::String& str);
        Format(const Value& value);
        Format(const int& value);

        void fromString(const core::char_t* str);
        void fromString(const core::String& str);
        core::String toString() const;

        int bit() const;
        int sbufBit() const;
        int zbufBit() const;

        enumerator beginEnum();
        enumerator endEnum();
        const_enumerator beginEnum() const;
        const_enumerator endEnum() const;

        bool operator == (const Format& lhs) const;
        bool operator != (const Format& lhs) const;
        bool operator == (const Value& lhs) const;
        bool operator != (const Value& lhs) const;
        operator Value () const;

        template <typename T>
        operator T () const
        {
            return static_cast<T>(value_);
        }

    private:
        Value from_string(const core::char_t* str);

    private:
        Value value_;
    };
}
}
}

#endif // TOD_ENGINE_GRAPHICS_CORE_FORMAT_H
