#include <iostream>

/* Adaptee (source) interface */
class AdapteeInterface
{
    public:
        virtual void specificOperation() = 0;
};

class Adaptee : public AdapteeInterface
{
    public:
        void specificOperation() override { std::cout << "Adaptee specificOperation())\n"; }
};

class TargetInterface
{
    public:
        virtual void operation() = 0;
};

// Object Adapter - wrapper (implements Target, overrides Adaptee)
class Adapter : public TargetInterface
{
    public:
        void attach(AdapteeInterface* outlet) { adaptee = outlet; }
        void operation() override {
            std::cout << "Adapter operation()\n";
            adaptee->specificOperation();
        }
    private:
        AdapteeInterface* adaptee;
};

class Client
{
    public:
        void attach(TargetInterface* x)  { ti = x; }
        void useTargetInterface() {
            std::cout << "Client time!" << std::endl;
            ti->operation();
        }
    private:
        TargetInterface* ti;
};


int main()
{
    Adaptee* adaptee = new Adaptee;
    Adapter* adapter = new Adapter;
    Client* cl = new Client;

    /* attaching to adaptee */
    adapter->attach(adaptee);
    cl->attach(adapter);

    /* target interface usage from client */
    cl->useTargetInterface();

    return EXIT_SUCCESS;
}
