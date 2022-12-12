#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "session.h"
#include <nlohmann/json.hpp>

using boost::asio::io_service;
using boost::asio::ip::tcp;
using boost::asio::ip::address;
using json = nlohmann::json;

class Server {
 public:
  Server(boost::asio::io_service& io_service, short port)
      : io_service_(io_service),
        acceptor_(io_service, tcp::endpoint(tcp::v4(), port)) {
    start_accept();
  }

 private:
  void start_accept() {
    Session* new_session = new Session(io_service_);
    acceptor_.async_accept(
        new_session->socket(),
        boost::bind(&Server::handle_accept, this, new_session,
                    boost::asio::placeholders::error));
  }

  void handle_accept(Session* new_session,
                     const boost::system::error_code& error) {
    if (!error) {
      new_session->start();
      start_accept();
    } else {
      delete new_session;
    }
  }

  boost::asio::io_service& io_service_;
  tcp::acceptor acceptor_;
};

int main(int argc, char* argv[]) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: server <port> " << std::endl;
      return 1;
    }

    boost::asio::io_service io_service;

    Server s(io_service, std::atoi(argv[1]));

    io_service.run();
  } catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
