#include <sensors-c++/sensors.h>
#include <iostream>
#include <vector>
#include <boost/asio.hpp>
#include <thread>
#include <nlohmann/json.hpp>
#include <clickhouse/client.h>

using boost::asio::ip::tcp;
using json = nlohmann::json;
using namespace clickhouse;

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
    // Все датчики в системе
 public:
    LogColector() {
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
                    message.push_back(temp_message);
                }
            }
        }
        json result(message);
        return result;
    }
};

class LogWriter {
private:
    Client client;
public:
    LogWriter(const std::string& host) : client(ClientOptions().SetHost(host)) {
        client.Execute("CREATE TABLE IF NOT EXISTS default.sensors ("
            "id UInt64,"
            "name String,"
            "feature String,"
            "subfeature String,"
            "value Float64,"
            "client_ip String"
        ") ENGINE = Memory");
        // client.Execute("CREATE TABLE IF NOT EXISTS sensors (name String, feature String, subfeatures String, value Float64) ENGINE = MergeTree() ORDER BY name");
    }

    void write(const json& msg) {
        Block block;
        auto name = std::make_shared<ColumnString>();
        auto feature = std::make_shared<ColumnString>();
        auto subfeatures = std::make_shared<ColumnString>();
        auto value = std::make_shared<ColumnFloat64>();
        auto client_ip = std::make_shared<ColumnString>();

        for (size_t i = 0; i < msg.size(); i++) {
            name->Append(msg[i]["name"]);
            feature->Append(msg[i]["feature"]);
            subfeatures->Append(msg[i]["subfeature"]);
            value->Append(msg[i]["value"]);
            client_ip->Append("192.168.0.1");
        }

        block.AppendColumn("name", name);
        block.AppendColumn("feature", feature);
        block.AppendColumn("subfeature", subfeatures);
        block.AppendColumn("value", value);
        block.AppendColumn("client_ip", client_ip);

        client.Insert("sensors", block);
    }
};

int main() {
    LogColector a;
    // LogSender sender("localhost", "9090");
    // sender.write(a.get_bus().dump());
    LogWriter writer("localhost");
    writer.write(a.get_bus());
    return 0;
}