/**
intention of builder pattern is to find a solution to the telescoping constructor
anti-pattern that occurs when the increase of object constructor parameter
combination leads to an exponential list of constructors. Instead of using
numerous constructors, the builder pattern uses another object, a builder,
that receives each initialization parameter step by step and then returns
the resulting constructed object at once.
It can be used for objects that contain flat data (HTML, SQL…), data that
can't be easily edited step by step and hence must be edited at once.

Builder design pattern solves problems like:

   --How can a class (the same construction process) create different
   representations of a complex object?
   --How can a class that includes creating a complex object be simplified?

How to solve such problems:

    --Encapsulate creating and assembling the parts of a complex object in
    a separate Builder object.
    --A class delegates object creation to a Builder object instead of
    creating the objects directly.
*/
#include <iostream>

////// Product declarations and inline impl. (Product.h) //////
class Product{
	public:
		// use this class to construct Product
		class Builder;
        // Product specific functionality
		void print();
		void doSomething();
		void doSomethingElse();
	private:
		// ariables in need of initialization to make valid object
		const int i;
		const float f;
		const char c;

		//Simple constructor - rest is handled by Builder
		Product(const int i, const float f, const char c) : i(i), f(f), c(c) {}
};

class Product::Builder{
	private:
		// variables needed for construction of object of Product class
		int i;
		float f;
		char c;
	public:
		// default values for variables
		static const constexpr int    defaultI = 1;
		static const constexpr float  defaultF = 3.1415f;
		static const constexpr char   defaultC = 'a';

		// create Builder with default values assigned
		// (in C++11 they can be simply assigned above on declaration instead)
		Builder() : i( defaultI ), f( defaultF ), c( defaultC ){ }

		// sets custom values for Product creation
		// returns Builder for shorthand inline usage (same way as cout <<)
		Builder& setI( const int i )  { this->i = i; return *this; }
		Builder& setF( const float f ){ this->f = f; return *this; }
		Builder& setC( const char c ) { this->c = c; return *this; }

		// prepare specific frequently desired Product
		// returns Builder for shorthand inline usage (same way as cout <<)
		Builder& setProductP(){
			this->i = 1;
			this->f = -1.0f/10.0f;
			this->c = '@';
			return *this;
		}
		// produce desired Product
		Product build(){
			//optionaly check var consistency and if Product
			//is buildable from given information
			return Product( this->i, this->f, this->c );
		}
};

///// Product implementation (possibly Product.cpp) /////
void Product::print(){
	using namespace std;

	cout << "Product internals dump:" << endl;
	cout << "i: " << this->i << endl;
	cout << "f: " << this->f << endl;
	cout << "c: " << this->c << endl;
}
void Product::doSomething() {}
void Product::doSomethingElse() {}


//////////////////// Usage of Builder (replaces Director from diagram)
int main(){
	// simple usage
	Product p1 = Product::Builder().setI(100).setF(100.5f).setC('x').build();
	p1.print(); // test p1

	// advanced usage
	Product::Builder b;
	b.setProductP();
	Product p2 = b.build(); // get Product P object
	b.setC('!'); // customize Product P
	Product p3 = b.build();
	p2.print(); // test p2
	p3.print(); // test p3
}
