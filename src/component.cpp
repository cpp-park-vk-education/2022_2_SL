#include <sensors-c++/sensors.h>
#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include <thread>
#include <nlohmann/json.hpp>

using boost::asio::ip::tcp;
using json = nlohmann::json;

class LogSender {
private:
    boost::asio::io_service io_service;
    tcp::socket socket;
    tcp::resolver resolver;
    tcp::resolver::query query;
    tcp::resolver::iterator endpoint_iterator;
    boost::system::error_code error;
public:
    LogSender(const std::string& host, const std::string& port) : socket(io_service), resolver(io_service), query(host, port) {
        endpoint_iterator = resolver.resolve(query);
        error = boost::asio::error::host_not_found;
        while (error && endpoint_iterator != tcp::resolver::iterator()) {
            socket.close();
            socket.connect(*endpoint_iterator++, error);
        }
        if (error)
            throw boost::system::system_error(error);
    }

    void write(const std::string& msg) {
        boost::asio::write(socket, boost::asio::buffer(msg));
    }

    std::string read() {
        boost::asio::streambuf buf;
        boost::asio::read_until(socket, buf, "");

        std::istream is(&buf);
        std::string msg;
        while (is) {
            std::string line;
            std::getline(is, line);
            msg += line;
        }
        return msg;
    }

    // async write
    void write_async(const std::string& msg) {
        socket.async_write_some(boost::asio::buffer(msg), [](const boost::system::error_code& error, std::size_t bytes_transferred) {
            if (error) {
                std::cout << "Error: " << error.message() << std::endl;
            }
        });
    }
};



class LogColector {
 private:
    std::vector<sensors::chip_name> bus;
    uint64_t counter;
 public:
    LogColector() : counter(0) {
        bus = sensors::get_detected_chips();
    }

    ~LogColector() {};

    void print_bus() {
        std::vector<sensors::feature> temp;
        std::vector<sensors::subfeature> temp_sub;
        for (size_t i = 0; i < bus.size(); i++) {
            std::cout<<"name: "<<bus[i].name()<<std::endl;
            temp = bus[i].features();
            for (size_t j = 0; j < temp.size(); j++) {
                std::cout<<"feature: "<<temp[j].number()<<" "<<temp[j].name()<<std::endl;
                temp_sub = temp[j].subfeatures();
                for (size_t k = 0; k < temp_sub.size(); k++) {
                     std::cout<<"subfeatures: "<<temp_sub[k].name()<<" | "<<temp_sub[k].read() <<  " - " <<std::endl;
                }
            }
        }
    }

    json get_bus() {
        std::vector<json> message;
        std::vector<sensors::feature> temp;
        std::vector<sensors::subfeature> temp_sub;
        for (size_t i = 0; i < bus.size(); i++) {
            temp = bus[i].features();
            for (size_t j = 0; j < temp.size(); j++) {
                temp_sub = temp[j].subfeatures();
                for (size_t k = 0; k < temp_sub.size(); k++) {
                    nlohmann::json temp_message;
                    temp_message["name"] = bus[i].name();
                    temp_message["feature"] = temp[j].name();
                    temp_message["subfeature"] = temp_sub[k].name();
                    temp_message["value"] = temp_sub[k].read();
                    temp_message["time"] = std::chrono::system_clock::now().time_since_epoch().count();
                    temp_message["count"] = counter;
                    message.push_back(temp_message);
                }
            }
        }
        counter++;
        json result(message);
        return result;
    }
};


int main(int argc, char* argv[]) {
    // g++ -o client component.cpp -lsensors-c++
    // ./client localhost 9090

    LogColector a;

    if (argc != 3) {
        std::cerr << "Usage: client <host> <port>" << std::endl;
        return 1;
    }

    LogSender sender(argv[1], argv[2]);

    while (true) {
        sender.write_async(a.get_bus().dump());
        std::cout << "data send" << std::endl; 
        std::this_thread::sleep_for(std::chrono::seconds(10));
    }

    return 0;
}
