#include <iostream>

using json = nlohmann::json;

class AbstractMessage {
    
    protected:

    std::string receiver;
    std::string format;

    public:

    virtual std::string get_format();

    virtual std::string get_receiver();

};

class LogMessage : public AbstractMessage {
    
    private:

    json body;

    public:

    bool set_body(json element);
    json get_body();
};

template<class T>
class ISerializer {

    public:

    T serialize(AbstractMessage element);

    AbstractMessage deserialize(T element);
};

template<class T>
class Serializer : public ISerializer {

    public:

    T serialize(AbstractMessage element);

    AbstractMessage deserialize(T element);
};

class Serializer_json :  public Serializer {
    
    public:

    json serialize(AbstractMessage element);

    AbstractMessage deserialize(json element);
};
