/*
Lazy initialization is the tactic of delaying the creation of an object, the
calculation of a value, or some other expensive process until the first time
it is needed. It is a kind of lazy evaluation that refers specifically to the
instantiation of objects or other resources.

This is typically accomplished by augmenting an accessor method (or property getter)
to check whether a private member, acting as a cache, has already been initialized.
If it has, it is returned straight away. If not, a new instance is created, placed
into the member variable, and returned to the caller just-in-time for its first use.
*/
#include <iostream>
#include <string>
#include <map>

using namespace std;

class Fruit {
    public:
        static Fruit* getFruit(const string& type);
        static void printCurrentTypes();
    private:
        static map<string,Fruit*> types;
        string type;
        // note: constructor private forcing one to use static getFruit()
        Fruit(const string& t) : type( t ) {cout << type << " Object created..." << endl;}
};
map<string, Fruit*> Fruit::types;

/*
 Lazy Factory method, gets the Fruit instance associated with a certain type.
 Instantiates new ones as needed.
 precondition: type. Any string that describes a fruit type, e.g. "apple"
 postcondition: The Fruit instance associated with that type.
 */
Fruit* Fruit::getFruit(const string& type) {
    //try to find an existing instance; if not found std::map will return types.end()
    map<string, Fruit*>::iterator it = types.find(type);

    Fruit *f;
    if (it == types.end()) { //if no instance of proper type was found, make one
        f = new Fruit(type); //lazy initialization part
        types[type] = f;     //adding the new Fruit to the types map for later lookup
    }
    else { //if an instance was found
        f = it->second; //The return value will be the found fruit
    }
    return f;
}

/* For example purposes to see pattern in action */
void Fruit::printCurrentTypes() {
    if (!types.empty()) {
        cout << "Total instances created : " << types.size() << endl;
        for (map<string,Fruit*>::iterator iter = types.begin(); iter != types.end(); ++iter) {
            cout << (*iter).first << endl;
        }
        cout << endl;
    }
}

int main(void) {
    Fruit::getFruit("Banana");
    Fruit::printCurrentTypes();

    Fruit::getFruit("Apple");
    Fruit::printCurrentTypes();

    //returns pre-existing instance from the firs tme Fruit "Banana" was created
    Fruit::getFruit("Banana");
    Fruit::printCurrentTypes();

    return 0;
}
