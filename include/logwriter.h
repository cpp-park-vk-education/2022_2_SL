#include <iostream>
#include "component.h"
#include "serializer.h"
#include <clickhouse/client.h>

using clickhouse::client client;

class LogWriter : public IComponent {
    public:
        LogWriter() = default;
        ~LogWriter() override = default;
        void set_serializer(Serializer serializer) {
            serializer_ = serializer;
        }
    private:
        Serializer serializer_;
        std::string kName;
        client db;
};