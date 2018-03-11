/*
Inspired by https://sourcemaking.com/design_patterns/bridge
*/
#include <iostream>

// Defines the Abstract Interface
// Maintains the Implementor reference.
class ThreadScheduler
{
    public:
        virtual void operation() = 0;
};

// Implementator Interface for internal implementation that Bridge uses.
// Defines the interface for implementation classes
class ThreadScheduler_Implementor
{
    public:
        virtual void operationImp() = 0;
};

// Realization/Implementation of ThreadScheduler (UML Abstraction1)
// Associates(Aggregates?) imp.operationImp() from ThreadScheduler_Implementor
class Bridge : public ThreadScheduler
{
    protected:
        ThreadScheduler_Implementor* imp;
    public:
        Bridge(ThreadScheduler_Implementor* backend) { imp = backend; }
};

/* Different special cases of the interface. */

class PreemptiveThreadScheduler : public Bridge
{
    public:
        PreemptiveThreadScheduler(ThreadScheduler_Implementor* backend) : Bridge(backend) {}
        void operation()
        {
            std::cout << "Preemtive ThreadScheduler running on ";
            imp->operationImp();
        }
};
class TimeSlicedThreadScheduler : public Bridge
{
    public:
        TimeSlicedThreadScheduler(ThreadScheduler_Implementor* backend) : Bridge(backend) {}
        void operation()
        {
            std::cout << "Time Sliced ThreadScheduler running on ";
            imp->operationImp();
        }
};

/* Different background implementations.
Realization/Implementation of ThreadScheduler_Implementor */

class WindowsPTS : public ThreadScheduler_Implementor
{
    public:
        void operationImp() { std::cout << "WindowsPTS" << std::endl; }
};
class UnixPTS : public ThreadScheduler_Implementor
{
    public:
        void operationImp() { std::cout << "UnixPTS!" << std::endl; }
};


int main()
{
    ThreadScheduler *absIntUse = nullptr;
    ThreadScheduler_Implementor *osWindowsPTS = new WindowsPTS;
    ThreadScheduler_Implementor *osUnixPTS    = new UnixPTS;

    // First case
    absIntUse = new PreemptiveThreadScheduler(osWindowsPTS);
    absIntUse->operation();
    absIntUse = new PreemptiveThreadScheduler(osUnixPTS);
    absIntUse->operation();

    // Second case
    absIntUse = new TimeSlicedThreadScheduler(osWindowsPTS);
    absIntUse->operation();

    absIntUse = new TimeSlicedThreadScheduler(osUnixPTS);
    absIntUse->operation();

    return EXIT_SUCCESS;
}
