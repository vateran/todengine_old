#ifndef TOD_CORE_UTILITY_UPDATEPROPERTY_UPDATEPROPERTYSERVER_H
#define TOD_CORE_UTILITY_UPDATEPROPERTY_UPDATEPROPERTYSERVER_H
/**
    @ingroup TodCoreUtility
    @class tod::core::UpdatePropertyServer
    @brief 
*/

#include <list>
#include "tod/core/ref.h"
#include "tod/core/node.h"
#include "tod/core/singleton3.h"

namespace tod
{
    class UpdatePropertyBase
    {
    public:
        virtual void update(
            Object* from, Property* from_p,
            Object* to, Property* to_p)=0;
    };

    class UpdatePropertyServer :
        public Node,
        public Singleton3<UpdatePropertyServer>
    {
    public:
        UpdatePropertyServer();
        ~UpdatePropertyServer();
        DECLARE_CLASS(UpdatePropertyServer, Node);

        bool update();

        UpdatePropertyBase* find(type_id from, type_id to);

    private:
        template <typename T>
        struct UpdatePropertyEqualType : public UpdatePropertyBase
        {
            override void update(
                Object* from, Property* from_p,
                Object* to, Property* to_p);
        };
        template <typename FROM, typename TO>
        struct UpdateProperty : public UpdatePropertyBase
        {
            override void update(
                Object* from, Property* from_p,
                Object* to, Property* to_p);
        };
        class PropertyTypeId
        {
        public:
            PropertyTypeId(type_id from, type_id to);
            bool operator < (const PropertyTypeId& rhs) const;
            type_id from_;
            type_id to_;
        };

    private:
        typedef std::map
            <PropertyTypeId, UpdatePropertyBase*> UpdateProperties;
        UpdateProperties updateProperties_;
    };
}

#endif // TOD_CORE_UTILITY_UPDATEPROPERTY_UPDATEPROPERTYSERVER_H
