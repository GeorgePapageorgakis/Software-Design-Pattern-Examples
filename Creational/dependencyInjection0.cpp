#include <iostream>

//interface serviceA
class ServiceA
{
    public:
        virtual void executeService() = 0;
        //virtual ServiceA* interfaceInjection() = 0;
};
//interface serviceB
class ServiceB
{
    public:
        virtual void executeService() = 0;
        //virtual ServiceB* interfaceInjection() = 0;
};

//ServiceA1 realizes/implements ServiceA
class ServiceA1 : public ServiceA
{
    public:
        void executeService() override { std::cout << "serviceA1 is working\n"; }
};
//ServiceB1 realizes/implements ServiceB
class ServiceB1 : public ServiceB
{
    public:
        void executeService() override { std::cout << "serviceB1 is working\n"; }
};


class Client  {
    private:
        // Internal reference to services used by client.
        ServiceA * service1;
        ServiceB * service2;
    public:
        Client () { std::cout << "default Client created...\n";}
        //constructor injection, dependencies are provided through class constructor
        Client(ServiceA * service1, ServiceB * service2) : service1(service1), service2(service2) {
            if (service1 == nullptr) {
                std::cout << "service1 must not be null\n";
            }
            if (service2 == nullptr) {
                std::cout << "service2 must not be null\n";
            }
            std::cout << "CI Client created...\n";
        }
        //setter injection, the client exposes a setter method that the injector
        //has to be called after client obj is constructed
        void setServiceA(ServiceA* service) {
             this->service1 = service;
        }
        void setServiceB(ServiceB* service) {
             this->service2 = service;
        }
        void callServices() const{
           std::cout << "Client::services called\n";
           service1->executeService();
           service2->executeService();
       }
};

//creates and injects to Client (depends on Client and ServicesA1-B1)
class Injector {
    public:
        static Client* constructionInjectionClient(){
            ServiceA1* sa1 = new ServiceA1;
            ServiceB1* sb1 = new ServiceB1;
            std::cout << "service sa1 created...\n";
            std::cout << "service sb1 created...\n";
            return new Client(sa1, sb1);
        }
        static Client* setterInjectionClient(){
            Client* cl = new Client();
            cl->setServiceA(new ServiceA1());
            cl->setServiceB(new ServiceB1());
            std::cout << "service sa1 injected...\n";
            std::cout << "service sb1 injected...\n";
            return cl;
        }
};

int main(){
    Client* clp;

    clp = Injector::constructionInjectionClient();
    clp->callServices();
    std::cout << std::endl;
    Client* c = Injector::setterInjectionClient();
    c->callServices();

    return EXIT_SUCCESS;
}
