/**
Abstract Factory design pattern solves problems:

    --How can an application be independent of how its objects are created?
    --How can a class be independent of how the objects it requires are created?
    --How can families of related or dependent objects be created?

How Abstract Factory design pattern solves such problems:

    --Encapsulate object creation in a separate (factory) object. That is,
    define an interface (AbstractFactory) for creating objects, and implement
    the interface.
    --A class delegates object creation to a factory object instead of creating
    objects directly.
*/
#include <iostream>
using namespace std;

class Shape {
    public:
        Shape() { id_ = total_++; }
        virtual void draw() = 0;
  protected:
        unsigned int id_;
        static unsigned int total_;
};

unsigned int Shape::total_ = 0;

class Circle : public Shape {
    public:
        void draw() { cout << "circle " << id_ << ": draw" << endl; }
};
class Square : public Shape {
    public:
        void draw() { cout << "square " << id_ << ": draw" << endl; }
};
class Ellipse : public Shape {
    public:
        void draw() { cout << "ellipse " << id_ << ": draw" << endl; }
};
class Rectangle : public Shape {
    public:
        void draw() { cout << "rectangle " << id_ << ": draw" << endl; }
};

//Abstract Factory
class Factory {
    public:
        virtual Shape* createCurvedInstance() = 0;
        virtual Shape* createStraightInstance() = 0;
};

class SimpleShapeFactory : public Factory {
    public:
        Shape* createCurvedInstance() { return new Circle; }
        Shape* createStraightInstance() { return new Square; }
};
class RobustShapeFactory : public Factory {
    public:
        Shape* createCurvedInstance() { return new Ellipse; }
        Shape* createStraightInstance() { return new Rectangle; }
};

int main() {
    Factory* Sfactory = new SimpleShapeFactory;
    Factory* Rfactory = new RobustShapeFactory;
    Shape* shapes[6];

    shapes[0] = Sfactory->createCurvedInstance();   //new Circle;
    shapes[1] = Sfactory->createStraightInstance(); //new Square;
    shapes[2] = Sfactory->createCurvedInstance();   //new Circle;

    shapes[3] = Rfactory->createCurvedInstance();   //new Ellipse;
    shapes[4] = Rfactory->createStraightInstance(); //new Rectangle;
    shapes[5] = Rfactory->createCurvedInstance();   //new Ellipse;

    for (int i=0; i < (sizeof(shapes)/sizeof(*shapes)); i++) {
        shapes[i]->draw();
    }
    return EXIT_SUCCESS;
}
