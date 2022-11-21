#include <iostream>

// класс интерфейса компонента
class IComponent {
public:
    virtual ~IComponent() {}
    virtual void Operation() = 0;
};