/*
 * C++ Singleton
 * Limitation: Single Threaded Design
 * See: http://www.aristeia.com/Papers/DDJ_Jul_Aug_2004_revised.pdf
 *      For problems associated with locking in multi threaded applications
 *
 * Limitation:
 * If you use this Singleton (A) within a destructor of another Singleton (B)
 * This Singleton (A) must be fully constructed before the constructor of (B)
 * is called.
 */
#include <iostream>

class Singleton final //optional prevent inheritance, c++11
{
    private:
        /* Here will be the instance stored. */
        static Singleton* instance;
        /* Private constructor to prevent instantiating. */
        Singleton();
        //~Singleton();
        // Singleton(Singleton const&);      // Don't Implement
        // void operator=(Singleton const&); // Don't implement
        // move constructor
        // Singleton (Singleton&& x) {}
        // move assignment
        // Singleton& operator= (Singleton&& x) {}
    public:
        /* Static access method. */
        static Singleton* getInstance();
        void method();
        // move constructor
        Singleton (Singleton&& x)           = delete;
        // move assignment
        Singleton& operator= (Singleton&& x)= delete;
        Singleton(Singleton const&)         = delete;
        void operator=(Singleton const&)    = delete;
        /*Note: Scott Meyers mentions in his Effective Modern C++ book,
             that deleted functions should generally be public as it
             results in better error messages due to the compilers
             behavior to check accessibility before deleted status
        */
};

Singleton::Singleton() { std::cout << "Singleton instance Created..." << std::endl; }
//Singleton::~Singleton() { delete instance; std::cout << "Singleton destroyed." << std::endl; }

/* Null, because instance will be initialized on demand. */
Singleton* Singleton::instance = nullptr;

//Lazy initialization
//for non-Lazy version, instantiate @ constructor and only return instance here
Singleton* Singleton::getInstance()
{
    if (instance == nullptr) {
        instance = new Singleton();
    }
    return instance;
}

void Singleton::method()
{
    std::cout << "Method of the singleton class" << std::endl;
}

int main()
{
    {
        //new Singleton(); // Won't work
        Singleton* s = Singleton::getInstance(); // Ok
        Singleton* r = Singleton::getInstance();
        /* The addresses will be the same. */
        std::cout << s << std::endl;
        std::cout << r << std::endl;
    }

    Singleton* a = Singleton::getInstance();
    Singleton* b = Singleton::getInstance();
    Singleton* c = a;
    Singleton* d(a);
    a = b;
    /* The addresses will be the same. */
    a->method();
    std::cout << b << std::endl;
    std::cout << c << std::endl;
    std::cout << d << std::endl;
    d->method();

    return EXIT_SUCCESS;
}
