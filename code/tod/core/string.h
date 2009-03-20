#ifndef TOD_CORE_TYPE_STRING_H
#define TOD_CORE_TYPE_STRING_H
/**
    @ingroup TodCoreType
    @class tod::String
    @brief
*/

#include <string>
#include "iconv/iconv.h"
#include "tod/core/define.h"
#include "tod/core/primitivetype.h"

namespace tod
{
    class String
    {
    public:
        typedef std::string stdstring;

        typedef stdstring::size_type size_type;
        typedef stdstring::reference reference;
        typedef stdstring::const_reference const_reference;
        typedef stdstring::iterator iterator;
        typedef stdstring::const_iterator const_iterator;
        typedef stdstring::reverse_iterator reverse_iterator;
        typedef stdstring::const_reverse_iterator const_reverse_iterator;
        typedef stdstring::value_type value_type;
        typedef stdstring::const_pointer pointer;
        typedef stdstring::const_pointer const_pointer;
        static const size_type npos = -1;

    public:
        String() {}
        String(const std::string& s):data_(s) {}
        String(const char_t* s, ...);
        String(const widechar_t* s, ...);
        String(const String& s, size_type offset, size_type count):
            data_(s.data_, offset, count) {}

        bool empty() const;
        size_type size() const;
        size_type length() const;

        void clear()
        {
            data_.clear();
        }

        void resize(size_type size)
        {
            data_.resize(size);
        }

        void resize(size_type size, value_type c)
        {
            data_.resize(size, c);
        }

        void reserve(size_type capacity=0)
		{
            data_.reserve(capacity);
		}

        String& assign(const String& s)
		{
		    data_.assign(s.data_);
            return (*this);
		}
	    String& assign(const String& s, size_type offset, size_type count)
		{
            data_.assign(s.data_, offset, count);
            return (*this);
        }

	    String& assign(const value_type* c, size_type num)
		{
            data_.assign(c, num);
		    return (*this);
		}

	    String& assign(const value_type* c)
		{
		    data_.assign(c);
            return (*this);
		}

	    String& assign(size_type count, value_type c)
		{
            data_.assign(count, c);
		    return (*this);
		}

	    String& assign(const_pointer first, const_pointer last)
		{
            data_.assign(first, last);
		    return (*this);
		}

	    String& assign(const_iterator first, const_iterator last)
		{
            data_.assign(first, last);
            return (*this);
		}

        size_type find(const String& s, size_type offset=0) const
		{
		    return data_.find(s.data_, offset);
		}

	    size_type find(const value_type* c, size_type offset, size_type count) const
		{
            return data_.find(c, offset, count);
		}

	    size_type find(const value_type* c, size_type offset=0) const
		{
		    return data_.find(c, offset);
		}

	    size_type find(value_type c, size_type offset=0) const
		{
		    return data_.find(c, offset);
		}

	    size_type rfind(const String& s, size_type offset=npos) const
		{
		    return rfind(s.data_, offset);
		}

	    size_type rfind(const value_type* c, size_type offset, size_type count) const
		{
            return data_.rfind(c, offset, count);
		}

	    size_type rfind(const value_type* c, size_type offset=npos) const
		{
		    return data_.rfind(c, offset);
		}

	    size_type rfind(value_type c, size_type offset=npos) const
		{
		    return data_.rfind(c, offset);
		}

        String substr(size_type offset=0, size_type count=npos) const
		{
		    return String(data_, offset, count);
		}

	    int compare(const String& s) const
		{
		    return data_.compare(s.data_);
		}

	    int compare(size_type offset, size_type count, const String& s) const
		{
		    return data_.compare(offset, count, s.data_);
		}

	    int compare(size_type loffset, size_type count, const String& s, size_type roffset, size_type ncount) const
		{
            return data_.compare(loffset, count, s.data_, roffset, ncount);
		}

	    int compare(const value_type* c) const
		{
		    return data_.compare(c);
		}

	    int compare(size_type offset, size_type count, const value_type* c) const
		{
		    return data_.compare(offset, count, c);
		}

	    int compare(size_type offset, size_type count, const value_type* c, size_type ncount) const
		{
            return data_.compare(offset, count, c, ncount);
		}

        const value_type* c_str() const;
	    const value_type* data() const;

        reference at(size_type offset);
        const_reference at(size_type offset) const;

        iterator begin();
        iterator end();
        const_iterator begin() const;
        const_iterator end() const;
        reverse_iterator rbegin();
        reverse_iterator rend();
        const_reverse_iterator rbegin() const;
        const_reverse_iterator rend() const;
        
        void format(const char_t* s, ...);
        void format(const char_t* s, va_list args);

        void format(const widechar_t* s, ...);
        void format(const widechar_t* s, va_list args);

        bool operator < (const String& s) const;
        bool operator > (const String& s) const;

        friend bool operator == (const String& s1, const String& s2);
        friend bool operator != (const String& s1, const String& s2);
        friend bool operator == (const String& s1, const char_t* s2);
        friend bool operator != (const String& s1, const char_t* s2);
        friend bool operator == (const char_t* s1, const String& s2);
        friend bool operator != (const char_t* s1, const String& s2);

        friend String operator + (const String& s1, const String& s2);
        friend String operator + (const String& s1, const char_t* s2);
        friend String operator + (const char_t* s1, const String& s2);        

        const String& operator += (const String& s)
        {
            data_ += s.data_;
            return (*this);
        }
        
        operator char_t* ();
        operator const char_t* () const;
        operator widechar_t* ();
        operator const widechar_t* () const;
        
        operator int ();
        operator const int () const;
        operator unsigned int ();
        operator const unsigned int () const;
        operator int64_t ();
        operator const int64_t () const;
        operator uint64_t ();
        operator const uint64_t () const;
        operator float ();
        operator const float () const;
        operator double ();
        operator const double () const;

        /**
            Utilities
        */
        //@{
        int toInt() const;
        uint64_t toInt64() const;
        float toFloat() const;
        double toDouble() const;
        String extractPath() const;
        void replace(const String& src_str, const String& dst_str);
        //@}

    public:
        static void initializeEncoding();
        static void finalizeEncoding();
        static iconv_t encodingHandle_;
        static void encoding(
            const char* src, size_t src_len,
            char* dest, size_t dest_len);

    private:
        stdstring data_;
    };

#include "tod/core/string.inl"

}

#endif // TOD_CORE_TYPE_STRING_H
