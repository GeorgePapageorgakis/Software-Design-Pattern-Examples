#include <iostream>
#include <vector>

class Multiton
{
public:
	unsigned getId();
	static Multiton *getInstance();
private:
	static std::vector<Multiton *> listOfInstancePtrs;
	// Limit of Objects this class will return in cycle
	static const unsigned limit;
	// Current index of getInstance() function call
	static unsigned currentIndex;
	// ID of each object
	unsigned mId;
	Multiton();
};

std::vector<Multiton *> Multiton::listOfInstancePtrs(limit, nullptr);
const unsigned Multiton::limit = 5;
unsigned Multiton::currentIndex =  0;

Multiton::Multiton() {
	std::cout << " instance created... ";
	mId = currentIndex + 1;
}

unsigned Multiton::getId() {
	return mId;
}
//lazy initialization
Multiton* Multiton::getInstance() {
	currentIndex = currentIndex % limit;
	if(!Multiton::listOfInstancePtrs[currentIndex % limit]) {
		Multiton::listOfInstancePtrs[currentIndex % limit] = new Multiton();
	}
	return Multiton::listOfInstancePtrs[currentIndex++ % limit];
}


int main()
{
	std::cout << Multiton::getInstance()->getId() << std::endl;
	std::cout << Multiton::getInstance()->getId() << std::endl;
	std::cout << Multiton::getInstance()->getId() << std::endl;
	std::cout << Multiton::getInstance()->getId() << std::endl;
	std::cout << Multiton::getInstance()->getId() << std::endl;
	std::cout << Multiton::getInstance()->getId() << std::endl;
	std::cout << Multiton::getInstance()->getId() << std::endl;
	return 0;
}
