#include <iostream>
#include "message.h"

// интерфейс сериализатора
class ISerializer {
public:
    virtual ~ISerializer() = default;
    virtual std::string serialize() = 0;
};

// класс сериализатора
class Serializer : public ISerializer {
public:
    Serializer() = default;
    ~Serializer() override = default;
    std::string serialize(Message message) {
        return "Serializer";
    }
    Message deserialize(std::string message) {
        return Message();
    }
};