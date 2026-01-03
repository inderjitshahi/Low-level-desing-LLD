#include <iostream>
using namespace std;

/********************* 1) Diamond Problem (WITHOUT virtual) ********************/

class A {
public:
    int value;
    A() { value = 10; }
};

class B : public A { };

class C : public A { };

class D : public B, public C {
public:
    void show() {
        // cout << value;   // ❌ ERROR: ambiguous — which value? B::A or C::A?
        cout << B::value << " and " << C::value << " (Ambiguity)" << endl;
    }
};


/****************** 2) Diamond Problem SOLUTION using virtual ******************/

class A2 {
public:
    int value;
    A2() { value = 20; }
};

class B2 : virtual public A2 { };

class C2 : virtual public A2 { };

class D2 : public B2, public C2 {
public:
    void show() {
        // Now only one shared copy comes from A2 due to virtual inheritance
        cout << value << " (Resolved)" << endl;
    }
};


/******************************* MAIN FUNCTION *********************************/

int main() {
    cout << "---- Without virtual inheritance (Diamond Problem) ----" << endl;
    D obj1;
    obj1.show();   // Ambiguity (two copies of A)

    cout << "\n---- With virtual inheritance (Solved) ----" << endl;
    D2 obj2;
    obj2.show();   // Single copy of A2

    return 0;
}
