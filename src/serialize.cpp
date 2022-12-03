#include "serialize.h"
   
json Serializer_json::serialize(LogMessage element) {
    return element.get_body();
};

AbstractMessage Serializer_json::deserialize(json element) {
    LogMessage rt;
    rt.set_body(element);
    return rt;
};