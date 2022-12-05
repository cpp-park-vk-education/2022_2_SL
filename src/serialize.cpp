#include "serialize.h"
   
json Serializer_json::serialize(AbstractMessage &element) {
    return element.get_body();
};

void Serializer_json::deserialize(json element, AbstractMessage &message) {
    message.set_body(element);
};
