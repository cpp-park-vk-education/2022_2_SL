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
    virtual ~AbstractMessage() = default;
    std::string get_format();
    std::string get_receiver();
    virtual bool set_body(json element) = 0;
    virtual json get_body() = 0;

};

class LogMessage : public AbstractMessage {
    
    private:

    json body;

    public:

    LogMessage() = default;
    ~LogMessage() override = default;

    bool set_body(json element) override;
    json get_body() override;
};

