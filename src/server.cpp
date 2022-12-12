#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

using boost::asio::io_service;
using boost::asio::ip::tcp;
using boost::asio::ip::address;
using json = nlohmann::json;

class Session {
 public:
  Session(io_service& io_service) : socket_(io_service) {
    std::cout << "Session created" << std::endl;
  }

  tcp::socket& socket() { return socket_; }

  void start() {
    socket_.async_read_some(
        boost::asio::buffer(data_, max_length),
        boost::bind(&Session::handle_read, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));
  }

  void reverse(std::string& msg) { std::reverse(msg.begin(), msg.end()); }

  void handle_read(const boost::system::error_code& error,
                   size_t bytes_transferred) {
    if (!error) {
      std::cout << "Received: " << data_ << std::endl;
      std::string msg(data_, bytes_transferred);
      try {
        json j = json::parse(msg);
        std::cout << "Received json: " << j << std::endl;
        // write to file
        std::ofstream o("output.json");
        o << j << std::endl;
        o.close();
        msg = "Received json!";
      } catch (json::parse_error& e) {
        msg =  "Ты мне пишешь: " + msg + "\n Понимаешь, что это не json?";
      }
      boost::asio::async_write(
          socket_, boost::asio::buffer(msg.c_str(), msg.length()),
          boost::bind(&Session::handle_write, this,
                      boost::asio::placeholders::error));
    } else {
      delete this;
    }
  }

  void handle_write(const boost::system::error_code& error) {
    if (!error) {
      socket_.async_read_some(
          boost::asio::buffer(data_, max_length),
          boost::bind(&Session::handle_read, this,
                      boost::asio::placeholders::error,
                      boost::asio::placeholders::bytes_transferred));
    } else {
      delete this;
    }
  }

 private:
  tcp::socket socket_;
  enum { max_length = 4096 };
  char data_[max_length];
};

class Server {
 public:
  Server(boost::asio::io_service& io_service, short port)
      : io_service_(io_service),
        acceptor_(io_service, tcp::endpoint(tcp::v4(), port)) {
          // acceptor_(io_service, tcp::endpoint(address::from_string("192.168.0.10"), port)) {
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
