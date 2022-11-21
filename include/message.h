#include <iostream>

// виртуальный класс сообщения
class VirtualMessage {
public:
    VirtualMessage() {}
    virtual ~VirtualMessage() {}
};

// класс сообщения
class Message : public VirtualMessage {
public:
    Message() = default;
    ~Message() override = default;
    std::string getMessage() {
        return "Message";
    }
};
