#pragma once

#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class AbstractMessage {
    
    protected:

    std::string receiver;
    std::string format;

    public:
    AbstractMessage() = 0;
    virtual ~AbstractMessage() = 0;
    virtual std::string get_format() = 0;
    virtual std::string get_receiver() = 0;
    virtual bool set_body(json element) = 0;
    virtual json get_body() = 0;

};

class LogMessage : public AbstractMessage {
    
    private:

    json body;

    public:
    LogMessage() = 0;
    ~LogMessage() = 0;
    bool set_body(json element) override;
    json get_body() override;
};

