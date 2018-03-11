/*
Prototype is used when creation of object is costly or complex. For example,
an object is to be created after a costly database operation, so we can cache
the object and return its clone on the next request. Once we get the cloned objects
we can modify it as we want.

Each derived class implements clone() method by returning an instance of itself.
A Factory class has been introduced that maintains a suite of "Person" objects
and knows how to delegate to the correct prototype.
*/
#include <iostream>
#include <vector>

using namespace std;

class Person {
    public:
       virtual Person* clone() = 0;
       virtual void slap_stick() = 0;
};

//Factory to manage prototypes
class Factory {
    public:
        static Person* make_Person( int choice );
    private:
        static Person* s_prototypes[4];
};

class Larry : public Person {
    public:
        Person*   clone() { return new Larry(); }
        void slap_stick() { cout << "Larry: pokes eyes\n"; }
};
class Moe : public Person {
    public:
        Person*   clone() { return new Moe(); }
        void slap_stick() { cout << "Moe: slap head\n"; }
};
class Curly : public Person {
    public:
        Person*   clone() { return new Curly(); }
        void slap_stick() { cout << "Curly: suffer abuse\n"; }
};

Person* Factory::s_prototypes[] = {
    nullptr, new Larry(), new Moe(), new Curly()
};
Person* Factory::make_Person( int choice ) {
    return s_prototypes[choice]->clone();
}

int main() {
    vector<Person*> roles;
    int choice;

    while (true) {
        cout << "Larry(1) Moe(2) Curly(3) Go(0): ";
        cin >> choice;
        if (choice > 0 && choice < 4)
            roles.push_back(Factory::make_Person( choice ));
        else
            break;
   }

   for (int i=0; i < roles.size(); ++i)
      roles[i]->slap_stick();
   for (int i=0; i < roles.size(); ++i)
      delete roles[i];
}
