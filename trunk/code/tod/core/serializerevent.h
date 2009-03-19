#ifndef TOD_CORE_SERIALIZER_SERIALIZEREVENT_H
#define TOD_CORE_SERIALIZER_SERIALIZEREVENT_H
/**
    @ingroup TodCoreSerializer
    @class tod::SerializerEvent
    @brief
*/

namespace tod
{
	class SerializerEvent
    {
    public:
		virtual void beginSerialize() {}
		virtual void endSerialize() {}

		virtual void beginDeserialize() {}
		virtual void endDeserialize() {}
    };
}

#endif // TOD_CORE_SERIALIZER_SERIALIZEREVENT_H
