#ifndef TOD_CORE_OBJECT_VARIABLES_H
#define TOD_CORE_OBJECT_VARIABLES_H
/**
    @ingroup TodCoreObject
    @class tod::Variable
    @brief
*/

#include <vector>
#include "tod/core/primitivetype.h"
#include "tod/core/simplevariable.h"

namespace tod
{
    class Variables
    {
    public:
        Variables();
        ~Variables();

        void clear();
        bool empty() const;
        size_t size() const;
        
        template <typename T>
        void add(const T& v);
        template <typename T>
        SimpleVariable<T>& get(index_t index);
        Variable* get(index_t index);

        void setForceList(bool enable);
        bool isForceList() const;

    private:
        typedef std::vector<Variable*> Array;

    private:
        Array array_;
        bool forceList_;
    };

#include "tod/core/variables.inl"

}

#endif // TOD_CORE_OBJECT_VARIABLES_H
