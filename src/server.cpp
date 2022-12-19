#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>
#include <clickhouse/client.h>

using boost::asio::io_service;
using boost::asio::ip::tcp;
using boost::asio::ip::address;
using json = nlohmann::json;
using namespace clickhouse;

class LogWriter {
private:
    Client client;
public:
    LogWriter(const std::string& host) : client(ClientOptions().SetHost(host)) {
        // добавление таблицы в clickhouse
        client.Execute("CREATE TABLE IF NOT EXISTS default.sensors ("
            "id UInt64,"
            "name String,"
            "feature String,"
            "subfeature String,"
            "value Float64,"
            "time UInt64,"
            "count UInt64,"
            "client_ip String"
        ") ENGINE = Memory");
        std::cout << "Table created" << std::endl;
    }

    // запись в clickhouse
    void write(const json& msg, std::string sender_ip) {
        Block block;
        auto name = std::make_shared<ColumnString>();
        auto feature = std::make_shared<ColumnString>();
        auto subfeatures = std::make_shared<ColumnString>();
        auto value = std::make_shared<ColumnFloat64>();
        auto time = std::make_shared<ColumnUInt64>();
        auto count = std::make_shared<ColumnUInt64>();
        auto client_ip = std::make_shared<ColumnString>();
        std::cout << msg << std::endl;

        for (size_t i = 0; i < msg.size(); i++) {
            name->Append(msg[i]["name"]);
            feature->Append(msg[i]["feature"]);
            subfeatures->Append(msg[i]["subfeature"]);
            value->Append(msg[i]["value"]);
            time->Append(msg[i]["time"]);
            count->Append(msg[i]["count"]);
            client_ip->Append(sender_ip);
        }

        block.AppendColumn("name", name);
        block.AppendColumn("feature", feature);
        block.AppendColumn("subfeature", subfeatures);
        block.AppendColumn("value", value);
        block.AppendColumn("time", time);
        block.AppendColumn("count", count);
        block.AppendColumn("client_ip", client_ip);

        client.Insert("sensors", block);
    }
};

class Session {
public:
    Session(io_service& io_service) : socket_(io_service) {
        std::cout << "Session created" << std::endl;
    }

    tcp::socket& socket() { return socket_; }

    void start() {
        // считываем данные из сокета
        socket_.async_read_some(
            boost::asio::buffer(data_, max_length),
            boost::bind(&Session::handle_read, this,
                        boost::asio::placeholders::error,
                        boost::asio::placeholders::bytes_transferred));
    }

    // реверс строки
    void reverse(std::string& msg) { std::reverse(msg.begin(), msg.end()); }

    // обработка данных
    void handle_read(const boost::system::error_code& error,
                    size_t bytes_transferred) {
        if (!error) {
        std::cout << "Received: " << data_ << std::endl;
        std::string msg(data_, bytes_transferred);
        try {
            json j = json::parse(msg);
            std::cout << "Received json: " << j << std::endl;

            // get sender ip
            std::string sender_ip = socket_.remote_endpoint().address().to_string();

            // write to clickhouse
            writer.write(j, sender_ip);

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

    // отправка данных
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
    LogWriter writer = LogWriter("localhost");
};

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
    // g++ -o server server.cpp -lclickhouse-cpp-lib
    // ./server 9090

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
