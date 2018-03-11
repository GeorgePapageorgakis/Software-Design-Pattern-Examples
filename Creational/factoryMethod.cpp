/**
Uses factory methods to deal with the problem of creating objects without
having to specify the exact class of the object that will be created.
This is done by creating objects by calling a factory method—either
specified in an interface and implemented by child classes, or implemented
in a base class and optionally overridden by derived classes—rather than
by calling a constructor.

https://sourcemaking.com/design_patterns/factory_method
*/

#include <iostream>
#include <string>

class Framework
{
    public:
        Framework() : color("") {}
		virtual ~Framework() { std::cout << "base destructed" << std::endl; }
        std::string color;
        /* This is the factory method. */
        static Framework* getObject(std::string color);
};

class App1 : public Framework
{
    public:
        App1() { color = "red"; }
		~App1() { std::cout << "App1 destructed" << std::endl; }
};

class App2 : public Framework
{
    public:
        App2() { color = "blue"; }
		~App2() { std::cout << "App2 destructed" << std::endl; }
};

/* Factory Method */
Framework* Framework::getObject(std::string color)
{
    if (color == "red")
        return new App1();
    else if (color == "blue")
        return new App2();
    else
        return 0;
}


int main()
{
    /* Now we decide the type of the cup at
     * runtime by the factory method argument */
    Framework* App1  = Framework::getObject("red");
    std::cout << App1->color << std::endl;

    Framework* App2 = Framework::getObject("blue");
    std::cout << App2->color << std::endl;

	delete App1;
	delete App2;
	return EXIT_SUCCESS;
}
