#include <iostream>

#include "Message.cpp"

using json = nlohmann::json;

class AbstractMessage {
    
    protected:

    std::string receiver;
    std::string format;

    public:

    virtual std::string get_format() {
        return 1;
    }

    virtual std::string get_receiver(){
        return 2;
    }

}

class LogMessage : public AbstractMessage {
    
    private:

    json body;

    public:

    bool set_body(json element) {
        if (element) {
            return true;
        } else {
            return false;
        }
    }
    json get_body() {
        return 2;
    }
}

template<class T>
class ISerializer {

    public:

    T serialize(AbstractMessage element) {
    };

    AbstractMessage deserialize(T element) {
    };
};

template<class T>
class Serializer : public ISerializer {

    public:

    T serialize(AbstractMessage element) {
    };

    AbstractMessage deserialize(T element) {
    };
};

class Serializer_json :  public Serializer {
    
    public:

    json serialize(AbstractMessage element) {
        json element_1;
        if (element.set_body(element_1)) {
            return "Success";
        }
        return "Unsuccess";
    };

    AbstractMessage deserialize(json element) {
        AbstractMessage rt;
        rt.get_body(element);
        return rt;
    };
}
