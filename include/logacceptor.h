#include <iostream>
#include <vector>
#include "component.h"
#include "serializer.h"
#include "socket.h"
// #include <boost>

// using boost::asio::ip::tcp::socket socket;


class LogAcceptor : public IComponent {
 public:
    LogAcceptor() = default;
    ~LogAcceptor() override = default;
    void set_serializer(Serializer serializer) {
        serializer_ = serializer;
    }
    void set_socket(Socket socket) {
        socket_ = socket;
    }
 private:
    Serializer serializer_;
    std::string kName;
    Socket socket_;
};
