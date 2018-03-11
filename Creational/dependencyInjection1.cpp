/*
Technique whereby one object supplies the dependencies of another object
and decouple objects to the extent that no client code has to be changed.
A dependency is an object that can be used (a service). An injection is the
passing of a dependency to a dependent object (a client) that would use it,
rather than allowing a client to build or find the object-service.

Dependency Injection solves problems like:

    --How can an application be independent of how its objects are created?
    --How can a class be independent of how the objects it requires are created?
    --How can the way objects are created be specified in separate configuration
    files?
    --How can an application support different configurations?

how to solve such problems:

    --Define a separate (injector) object that creates and injects the objects
    that a class requires.
    --A class accepts the objects it requires from an injector object instead
    of creating the objects directly.
*/
#include <iostream>
#include <string>
using namespace std;

class Shape
{
    public:
        virtual void draw() = 0;
};

class Circle : public Shape
{
    public:
        void draw() { cout << "circle\n"; }
};

class Triangle : public Shape
{
    public:
        void draw() { cout << "triangle\n"; }
};

/* 1. This class does not have hard-coded shapessuch as Triangle and Circle
   2. So, it's decoupled and has no dependency
   3. The specific information is injected by other class
   4. This code can be remained untouched when we switch the shape to draw
*/
class Drawing
{
    public:
        void drawShape(Shape *pShape) { pShape->draw(); }
    private:
        Shape *pShape;
};

/* 1. This class pulled the hard-coded shape info out of the Drawing class
   2. This class is an interface that can be modified depending on what to draw
   3. This class does Dependency Injection
*/
class IDrawing
{
public:
  IDrawing() { d = new Drawing; }
  void draw(string s)
  {
    if(s == "triangle")
        d->drawShape(new Triangle);
    else if( s == "circle")
        d->drawShape(new Circle);
    else
        cout << "Need shape\n";
  }
private:
  Drawing *d;
};

int main(){
    Drawing dd;
    //in order to avoid dd.draw("circle")
    dd.drawShape(new Triangle());

    //with DI
    IDrawing drawObj;
    drawObj.draw("circle");
    drawObj.draw("triangle");
    drawObj.draw("");

    return EXIT_SUCCESS;
}
