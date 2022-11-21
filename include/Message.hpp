#pragma once

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class AbstractMessage {
    
    protected:

    std::string receiver;
    std::string format;

    public:
    AbstractMessage() = default;
    ~AbstractMessage() = default;
    virtual std::string get_format();
    virtual std::string get_receiver();
    virtual bool set_body(json element);
    virtual json get_body();

};

class LogMessage : public AbstractMessage {
    
    private:

    json body;

    public:
    LogMessage() = default;
    ~LogMessage() = default;
    bool set_body(json element) override;
    json get_body() override;
};

template<class T>
class ISerializer {

    public:

    virtual T serialize(LogMessage element);

    virtual AbstractMessage deserialize(T element);
};

class Serializer_json :  public ISerializer<json> {
    
    public:

    json serialize(LogMessage element) override;

    AbstractMessage deserialize(json element) override;
};
