#include <iostream>
using namespace std;

class Base
{
public:
    // first base constructor is called, then derived constructor, no matter the any other rules
    // reverse order for destructor: first derived destructor is called, then base destructor
    // constructors can never be virtual, order is fixed, first base class constructor is called, then derived class constructor
    Base()
    {
        cout << "Base Constructor Called" << endl;
    }

    // without virtual keyword, call depends on pointer type, i.e compile time binding
    virtual void show()
    {
        cout << "Base Show Called" << endl;
    }

    // virtual destructor ensures derived destructor is called when deleting through base pointer, otherwise only base destructor is called, leading to resource leaks if derived allocated resources
    virtual ~Base()
    {
        cout << "Base Destructor Called" << endl;
    }
};

class Derived : public Base
{
public:
    Derived()
    {
        cout << "Derived Constructor Called" << endl;
    }

    void show() override
    {
        cout << "Derived Show Called" << endl;
    }
    ~Derived()
    {
        cout << "Derived Destructor Called" << endl;
    }
};

int main()
{
    // Base *base is compile time type
    // new Derived() is run time type
    // by default, call depends on pointer type (Base), so Base::show() is called, but with virtual keyword, call depends on run time type (Derived), so Derived::show() is called
    Base *base = new Derived();
    base->show();
    delete base;
}
