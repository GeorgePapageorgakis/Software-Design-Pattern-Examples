/*
Uses a set of initialized objects kept ready to use a "pool" rather than
allocating and destroying them on demand. A client of the pool will request an
object from the pool and perform operations on the returned object. When the
client has finished, it returns the object to the pool rather than destroying it.

Object pools employ one of three strategies to handle a request when there are
no spare objects in the pool.

    --Fail to provide an object (and return an error to the client).
    --Allocate a new object, thus increasing the size of the pool. Pools that do
    this usually allow you to set the high water mark (the maximum number of
    objects ever used).
    --In a multithreaded environment, a pool may block the client until another
    thread returns an object to the pool.

*/
#include <iostream>
#include <list>
#include <typeinfo>
class Resource
{
    int value;

    public:
        Resource() : value(0) {}
        void reset() { value = 0; }
        int getValue() { return value; }
        void setValue(int number) { value = number; }
};

/* Note, that this class is a singleton. */
class ObjectPool
{
    private:
        std::list<Resource*> resources;
        static ObjectPool* instance;

        ObjectPool() {}
    public:
        /**
         * Static method for accessing class instance. Part of Singleton pattern.
         * @return ObjectPool instance.
         */
        static ObjectPool* getInstance()
        {
            if (instance == 0) { instance = new ObjectPool; }
            return instance;
        }
        /**
         * Returns instance of Resource. New resource will be created if all
         * the resources were used at the time of the request.
         * @return Resource instance.
         */
        Resource* getResource()
        {
            if (resources.empty())
            {
                std::cout << "Creating new." << std::endl;
                return new Resource;
            }
            else
            {
                std::cout << "Reusing existing." << std::endl;
                Resource* resource = resources.front();
                resources.pop_front();
                return resource;
            }
        }
        /**
        * Return resource back to the pool.
        * The resource must be initialized back to the default settings before
        * someone else attempts to use it.
        * @param object Resource instance.
        * @return void
        */
        void returnResource(Resource* object)
        {
            object->reset();
            resources.push_back(object);
        }
};

ObjectPool* ObjectPool::instance = 0;


int main()
{
    ObjectPool* pool = ObjectPool::getInstance();
    Resource* one;
    Resource* two;

    /* Resources will be created. */
    one = pool->getResource();
    one->setValue(10);
    std::cout << "one = " << one->getValue() << " [" << one << "]" << std::endl;

    two = pool->getResource();
    two->setValue(20);
    std::cout << "two = " << two->getValue() << " [" << two << "]" << std::endl;

    std::cout << "type is: " << typeid(*two).name() << std::endl;
    std::cout << "type is: " << typeid(*pool).name() << std::endl;
    pool->returnResource(one);
    pool->returnResource(two);

    /* Resources will be reused.
     * Notice that the value of both resources were reset back to zero.
     */
    one = pool->getResource();
    std::cout << "one = " << one->getValue() << " [" << one << "]" << std::endl;

    two = pool->getResource();
    std::cout << "two = " << two->getValue() << " [" << two << "]" << std::endl;

    return 0;
}
