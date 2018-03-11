/*
 Adapter-Wrapper-Translator allows the interface of an existing class to be used
 as another interface. It is often used to make existing classes work with others
 without modifying their source code.

Adapter design pattern solves problems like:

   --How can a class, that does not have an interface that a client requires,
     be reused ?
   --How can classes that have incompatible interfaces work together?
   --How can an alternative interface be provided for a class?

how to solve such problems:

   --Define a separate Adapter class that converts the (incompatible) interface
    of a class (Adaptee) into another interface (Target) clients require.
   --Work through an Adapter to work with (reuse) classes that do not have the
   required interface.
*/
#include <iostream>

// Desired interface (Target)
class TargetInterface
{
  public:
    virtual void operation() = 0;
};

// Legacy component (Adaptee)
class Adaptee
{
    public:
        Adaptee(int x, int y) : m_x(x), m_y(y) {
            std::cout << "Adaptee(x, y)\n";
        }
        void specificOperation() { std::cout << "Adaptee: specificOperation().\n"; }
    private:
        int m_x, m_y;
};

// Class Adapter - wrapper (implements Target, inherits Adaptee)
class classAdapter: public TargetInterface, private Adaptee
{
    public:
        classAdapter(int x, int y) : Adaptee(x, y) {
                std::cout << "classAdapter(x, y)\n";
        }
        void operation() override {
            std::cout << "classAdapter: operation().\n";
            specificOperation();
        }
};

// Desired interface (Target)
class TargetInterfaceOA
{
  public:
    virtual void operation() = 0;
};
// Object Adapter (implements Target, associates Adaptee)
class objectAdapter: public TargetInterfaceOA
{
    public:
        objectAdapter(Adaptee& ad) : m_adaptee(ad) {
                std::cout << "objectAdapter(x, y)\n";
        }
        void operation() override {
            std::cout << "objectAdapter: operation().\n";
            m_adaptee.specificOperation();
        }
    private:
        Adaptee& m_adaptee;
};

//main serves as Client here
int main()
{
    TargetInterface *tca = new classAdapter(20, 40);
    tca->operation();

    std::cout << std::endl;

    //object ad can be elsewhere or b
    Adaptee ad(10, 30);
    TargetInterfaceOA *toa = new objectAdapter(ad);
    toa->operation();

    return EXIT_SUCCESS;
}
