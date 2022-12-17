#include "message.h"

bool LogMessage::set_body(json element) {
    if (element) {
        return true;
    } else {
        return false;
    }
}

json LogMessage::get_body()  {
    json example;
    return example;
}

