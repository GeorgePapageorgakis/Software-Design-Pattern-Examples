/*
When dealing with Tree-structured data, programmers often have to discriminate
between a leaf-node and a branch. This makes code more complex, and therefore,
more error prone. The solution is an interface that allows treating complex and
primitive objects uniformly.

Composite should be used when clients ignore the difference between compositions
of objects and individual objects.
*/
#include <iostream>
#include <vector>
using namespace std;

// Interface (lowest common denominator)
class Component
{
    public:
        virtual void traverse() = 0;
};

//Scalar class, "is a" relationship - composition
class Leaf: public Component
{
    public:
        Leaf(int val) { m_value = val; }
        void traverse() { cout << m_value << "-" << &m_value << ' '; }
    private:
        int m_value;
};

//Vector class, "is a" relationship - composition
class Composite: public Component
{
    public:
        //"container" class coupled to the interface
        void add(Component *ele) { m_children.push_back(ele); }
        void traverse()
        {
            for (int i = 0; i < m_children.size(); ++i)
                //polymorphism to delegate to children
                m_children[i]->traverse();
        }
    private:
        vector<Component*> m_children; //container
};

int main()
{
    Composite containers[4];

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 3; j++)
            containers[i].add(new Leaf(i * 3+j));

    //share the rest of the leafs in containers[0]
    for (int i = 1; i < 4; i++)
        containers[0].add(&(containers[i]));

    for (int i = 0; i < 4; i++)
    {
        containers[i].traverse();
        cout << endl;
    }

    return EXIT_SUCCESS;
}
