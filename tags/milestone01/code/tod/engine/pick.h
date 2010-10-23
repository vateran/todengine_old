#ifndef TOD_ENGINE_GRAPHICS_CORE_PICK_H
#define TOD_ENGINE_GRAPHICS_CORE_PICK_H
/**
    @ingroup TodEngineGraphicsCore
    @class tod::engine::Pick
    @brief 
*/

#include <list>
#include "tod/core/node.h"
#include "tod/core/primitivetype.h"
#include "tod/core/vector3.h"

namespace tod
{
namespace engine
{
    class Pick
    {
    public:
        class Record
        {
        public:
        };
        class Result
        {
        public:
            Record* get(uint32_t index);

            void clear();
            void sort();

        private:
            typedef std::list<Record> Records;

        private:
            Records records_;
        };
    public:
        bool pickObjects(
            Node* root,
            const Vector3& origin,
            const Vector3& dir);

        const Result& getResult() const;

    private:
        Result result_;
    };
}
}

#endif // TOD_ENGINE_GRAPHICS_CORE_PICK_H
