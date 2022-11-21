#include <string>

class Sensor {
public:
    Sensor() = default;
    ~Sensor() = default;
    std::string value() {
        return "Sensor";
    }
};