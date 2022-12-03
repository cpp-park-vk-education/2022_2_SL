#pragma once

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


template<class T>
class ISerializer {

    public:

    ISerializer() = default;

    virtual ~ISerializer() = default;

    virtual T serialize(AbstractMessage element) = 0;

    virtual AbstractMessage deserialize(T element) = 0;
};

class Serializer_json :  public ISerializer<json> {
    
    public:

    json serialize(AbstractMessage element) override;

    AbstractMessage deserialize(json element) override;
};

class Serializer_str :  public ISerializer<std::string> {
    
    public:

    std::string serialize(AbstractMessage element) override;

    AbstractMessage deserialize(std::string element) override;
};
