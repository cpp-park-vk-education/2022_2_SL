#pragma once

#include <iostream>
#include <nlohmann/json.hpp>

#include "message.h"

using json = nlohmann::json;


template<class T>
class ISerializer {

    public:

    virtual T serialize(AbstractMessage &element);

    virtual void deserialize(T element, AbstractMessage &message);
};

class Serializer_json :  public ISerializer<json> {
    
    public:

    json serialize(AbstractMessage &element) override;

    void deserialize(json element, AbstractMessage &message) override;
};

class Serializer_str :  public ISerializer<std::string> {
    
    public:

    std::string serialize(AbstractMessage &element) override;

    void deserialize(std::string element, AbstractMessage &message) override;
};
