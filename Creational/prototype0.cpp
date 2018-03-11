/*
Prototype is used when the type of objects to create is determined by a
prototypical instance, which is cloned to produce new objects. It is used to:

    --avoid subclasses of an object creator in the client application, like the
    factory method pattern does.
    --avoid the inherent cost of creating a new object in the standard way
    (e.g., using the 'new' keyword) when it is prohibitively expensive for a
    given application.

Prototype design pattern solves problems:

    --How can objects be created so that which objects to create can be
    specified at run-time?
    --How can dynamically loaded classes be instantiated?

How to solve such problems:

    --Define a Prototype object that returns a copy of itself.
    --Create new objects by copying a Prototype object.

The client, instead of writing code that invokes the "new" operator on a
hard-coded class name, instead:
    --calls the clone() method on the prototype
    --calls a factory method with a parameter designating the particular
    concrete derived class desired
    --or invokes the clone() method through some mechanism provided by another
    design pattern.
*/
#include <iostream>
#include <string>

/* Prototype base class. */
class Prototype
{
    protected:
        std::string type;
        int value;
    public:
        virtual Prototype* clone() const = 0;
        std::string getType() const { return type; }
        int getValue() const { return value; }
};

//clonable Prototype class
class ConcreteClonable1 : public Prototype
{
    public:
        ConcreteClonable1(int number)
        {
            std::cout << "ConcreteClonable1 cnstr\n";
            type  = "Type1";
            value = number;
        }
        ConcreteClonable1 (const ConcreteClonable1& x) : Prototype(x)
        {
            std::cout << "ConcreteClonable1 copy cnstr\n";
        }
        Prototype* clone() const { return new ConcreteClonable1(*this); }
};
//clonable Prototype class
class ConcreteClonable2 : public Prototype
{
    public:
        ConcreteClonable2(int number)
        {
            std::cout << "ConcreteClonable2 cnstr\n";
            type  = "Type2";
            value = number;
        }
        ConcreteClonable2 (const ConcreteClonable2& x) : Prototype(x)
        {
            std::cout << "ConcreteClonable2 copy cnstr\n";
        }
        Prototype* clone() const { return new ConcreteClonable2(*this); }
};

/* Factory that manages prorotype instances and produces their clones. */
class ObjectFactory
{
    private:
        static Prototype* type1value1;
        static Prototype* type1value2;
        static Prototype* type2value1;
        static Prototype* type2value2;
    public:
        //cache the objects
        static void  initialize()
        {
            type1value1 = new ConcreteClonable1(1);
            type1value2 = new ConcreteClonable1(2);
            type2value1 = new ConcreteClonable2(1);
            type2value2 = new ConcreteClonable2(2);
        }

        static Prototype* getType1Value1() { return type1value1->clone(); }
        static Prototype* getType1Value2() { return type1value2->clone(); }
        static Prototype* getType2Value1() { return type2value1->clone(); }
        static Prototype* getType2Value2() { return type2value2->clone(); }
};
Prototype* ObjectFactory::type1value1 = nullptr;
Prototype* ObjectFactory::type1value2 = nullptr;
Prototype* ObjectFactory::type2value1 = nullptr;
Prototype* ObjectFactory::type2value2 = nullptr;


int main()
{
    ObjectFactory::initialize();
    Prototype* object;

    /* All the object were created by cloning the prototypes. */
    object = ObjectFactory::getType1Value1();
    std::cout << object->getType() << ": " << object->getValue() << std::endl;

    object = ObjectFactory::getType1Value2();
    std::cout << object->getType() << ": " << object->getValue() << std::endl;

    object = ObjectFactory::getType2Value1();
    std::cout << object->getType() << ": " << object->getValue() << std::endl;

    object = ObjectFactory::getType2Value2();
    std::cout << object->getType() << ": " << object->getValue() << std::endl;

    return EXIT_SUCCESS;
}
