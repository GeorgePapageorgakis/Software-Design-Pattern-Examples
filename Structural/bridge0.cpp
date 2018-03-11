/*
Decouple an abstraction from its implementation so that the two can vary
independently. The bridge uses encapsulation, aggregation, and can use inheritance
to separate responsibilities into different classes.
The bridge pattern can also be thought of as two layers of abstraction.
Progressively add functionality while seperating out major differences using
abstract classes.

What problems can the Bridge design pattern solve?

    --An abstraction and its implementation should be defined and extended
    independently from each other.
    --A compile-time binding between an abstraction and its implementation should
    be avoided so that an implementation can be selected at run-time.

What solution does the Bridge design pattern describe?

    --Separate an abstraction (Abstraction) from its implementation (Implementor)
    by putting them in separate class hierarchies.
    --Publish interface in an inheritance hierarchy, and bury implementation in
    its own inheritance hierarchy.
    --Implement the Abstraction in terms of (by delegating to) an Implementor object.

When to use Bridge pattern?

    --When we want to be able to change both abstract classes and concrete classes
    independently
    --When we want the first abstract class to define rules and then the concrete
     class adds additional rules
    --When abstract class (abstract Remote) has a reference to the device(abstract
    TV) and it defines abstract methods that will be defined in the concrete class
    (remote controller).

This enables to configure an Abstraction with an Implementor object at run-time.
*/
#include <iostream>

// Defines the abstract interface
// Maintains the Implementor reference.
class AbstractionInterface
{
    public:
        virtual void operation() = 0;
};

// Interface for internal implementation that Bridge uses.
// Defines the interface for implementation classes
class ImplementatorInterface
{
    public:
        virtual void operationImp() = 0;
};

// Realization/Implementation of AbstractionInterface (UML Abstraction1)
// Associates(Aggregates?) imp.operationImp() from ImplementatorInterface
class Bridge : public AbstractionInterface
{
    protected:
        ImplementatorInterface* implementation;
    public:
        Bridge(ImplementatorInterface* backend) { implementation = backend; }
};

/* Different special cases of the interface. */
// e.g. Abstraction1
class concreteProduct1 : public Bridge
{
    public:
        concreteProduct1(ImplementatorInterface* backend) : Bridge(backend) {}
        void operation()
        {
            std::cout << "Product 1 running on "; //for example Skype
            implementation->operationImp();
        }
};
// e.g. Abstraction2
class concreteProduct2 : public Bridge
{
    public:
        concreteProduct2(ImplementatorInterface* backend) : Bridge(backend) {}
        void operation()
        {
            std::cout << "Product 2 running on "; //for example Firefox
            implementation->operationImp();
        }
};

/* Different background implementations.
Realization/Implementation of ImplementatorInterface */

class Windows : public ImplementatorInterface
{
    public:
        void operationImp() { std::cout << "Windows" << std::endl; }
};
class Linux : public ImplementatorInterface
{
    public:
        void operationImp() { std::cout << "Linux!" << std::endl; }
};


int main()
{
    AbstractionInterface    *absIntUse  = nullptr;
    ImplementatorInterface  *osWindows  = new Windows;
    ImplementatorInterface  *osLinux    = new Linux;

    // First case
    absIntUse = new concreteProduct1(osWindows);
    absIntUse->operation();
    absIntUse = new concreteProduct1(osLinux);
    absIntUse->operation();

    // Second case
    absIntUse = new concreteProduct2(osWindows);
    absIntUse->operation();

    absIntUse = new concreteProduct2(osLinux);
    absIntUse->operation();

    return EXIT_SUCCESS;
}
