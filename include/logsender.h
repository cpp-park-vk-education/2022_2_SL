#include <iostream>
#include <vector>
#include "component.h"
#include "serializer.h"
#include <boost>

using boost::asio::ip::tcp::socket socket;

// класс отправителя логов
class LogCollector : public IComponent {
 public:
    LogCollector() = default;
    ~LogCollector() override = default;
    void set_serializer(Serializer serializer) {
        serializer_ = serializer;
    }
    void set_socket(socket socket) {
        socket_ = socket;
    }
private:
    Serializer serializer_;
    std::string kName;
    socket socket_;
};
