#include <iostream>
#include <vector>
#include "component.h"
#include "serializer.h"
#include "sensor.h"
// #include <libsensors/sensor.h>

// класс собирателя логов
class LogCollector : public IComponent {
 public:
    LogCollector() = default;
    ~LogCollector() override = default;
    void set_serializer(Serializer serializer) {
        serializer_ = serializer;
    }
    void set_sensors(vector<Sensor> Sensors) {
        sensors_ = sensors;
    }
private:
    Serializer serializer_;
    std::string kName;
    vector<Sensor> sensors;
};
