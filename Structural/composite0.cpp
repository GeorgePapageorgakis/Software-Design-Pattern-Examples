/*
A partitioning design pattern that describes a group of objects that is treated
the same way as a single instance of the same type of object. The intent of a
composite is to "compose" objects into tree structures to represent part-whole
hierarchies. Implementing the composite pattern lets clients treat individual
objects and compositions uniformly.

What problems can Composite solve?

    --A part-whole hierarchy should be represented so that clients can treat part
    and whole objects uniformly.
    --A part-whole hierarchy should be represented as tree structure.
    --Avoid query the "type" of each object before attempting to process it.

What solution does the Composite describe?

    --Define a unified Component interface for both part (Leaf) objects and whole
    (Composite) objects.
    --Individual Leaf objects implement the Component interface dileaf2ly, and
    Composite objects forward requests to their child components.

*/
/*
Design for Uniformity: Child-related operations are defined in the Component
interface. This enables clients to treat Leaf and Composite objects uniformly.
No type safety because clients can perform child-related operations on Leaf objects.
*/
#include <list>
#include <iostream>
using namespace std;

//abstract class
class Component {
    public:
        virtual void operation() const = 0;
        //For Type Safety these functions should only be defined in Composite class
        //type safety because clients cannot perform child operations on Leaf objects
        virtual void add(Component* g) {}
        virtual void remove(Component* g) {}
        virtual void getChild(int) {}
        virtual ~Component() {}
};

//Leafs (leafs have no children)
class Leaf1 : public Component {
    public:
        void operation() const { cout << "Leaf1 operation()\n"; }
};
class Leaf2 : public Component {
    public:
        void operation() const { cout << "Leaf2 operation() \n"; }
};
class Leaf3 : public Component {
    public:
        void operation() const { cout << "Leaf3 operation() \n"; }
};

//Composite will contain leaf or a group of leafs
class Composite : public Component {
    public:
        void operation() const {
            // for each element in m_Leafs, call operation()
            for (list<Component*>::const_iterator it = m_Leafs.begin(); it != m_Leafs.end(); ++it) {
                (*it)->operation();
            }
        }
        void add(Component* aComponent) {
            m_Leafs.push_back(aComponent);
        }
        void remove(Component* g) {}
        void getChild(int) {}
    private:
        list<Component*> m_Leafs;
};

//client
int main()
{
    Leaf1 leaf1;
    Leaf2 leaf2;
    Leaf3 leaf3;
    //pattern in action
    leaf2.operation();
    leaf1.operation();
    leaf3.operation();
    cout << endl;

    //make a composition of leafs and simply use the same operation() function
    Composite comp;
    comp.add(&leaf1);
    comp.add(&leaf2);
    comp.add(&leaf3);
    comp.add(&leaf2);
    //pattern in action
    comp.operation();

    return 0;
}
