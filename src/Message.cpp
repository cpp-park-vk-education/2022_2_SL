#include <iostream>
#include <nlohmann/json.hpp>

#include "Message.hpp"


    bool LogMessage::set_body(json element) {
        if (element) {
            return true;
        } else {
            return false;
        }
    }

    json LogMessage::get_body()  {
        return 2;
    }

    json Serializer_json::serialize(LogMessage element) {
        return element.get_body();
    };

    AbstractMessage Serializer_json::deserialize(json element) {
        LogMessage rt;
        rt.set_body(element);
        return rt;
    };