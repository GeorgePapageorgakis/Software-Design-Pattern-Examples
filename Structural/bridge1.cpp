/*
http://www.bogotobogo.com/DesignPatterns/bridge.php
*/
#include <iostream>
using namespace std;

// Implementor
class DrawingImplementor {
    public:
        virtual void drawSquare(double) = 0;    //operationImp()
        virtual ~DrawingImplementor() {}
};

// Abstraction
class Shape {
    public:
        virtual void draw() = 0;    //operation()
        virtual void resize(double pct) = 0;
        virtual ~Shape() {}
};
// Bridges the abstraction and its implementation, letting them vary independently
// Refined Abstraction1
class Square: public Shape {
    public:
        Square(double s, DrawingImplementor& Implementor) :
        	side(s), drawingImplementor(Implementor) {}
        virtual ~Square() {}

        // low-level i.e. Implementation specific
        void draw() { drawingImplementor.drawSquare(side); }
        // high-level i.e. Abstraction specific
        void resize(double pct) { side *= pct; }
    private:
        double side;
        DrawingImplementor& drawingImplementor;
};

// ConcreteImplementor A
class DrawingImplementorA: public DrawingImplementor {
    public:
        DrawingImplementorA() {}
        virtual ~DrawingImplementorA() {}

    	// operationImp() example: drawing with brush
        void drawSquare(double side) {
            cout << "\nImplementorA.square with side = "<< side << endl;
        }
};

// ConcreteImplementor B
class DrawingImplementorB: public DrawingImplementor {
    public:
        DrawingImplementorB() {}
        virtual ~DrawingImplementorB() {}

    	// operationImp() example: drawing with pencil
        void drawSquare(double side) {
            cout << "\nImplementorB.square with side = "<< side << endl;
        }
};

int main() {
    DrawingImplementorA ImplementorA;
    DrawingImplementorB ImplementorB;
    Shape* sqA = new Square(1, ImplementorA);
    Shape* sqB = new Square(2, ImplementorB);

    sqA->resize(10); sqA->draw();
    sqB->resize(10); sqB->draw();

    return 0;
}
