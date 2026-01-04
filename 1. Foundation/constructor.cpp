#include <bits/stdc++.h>
using namespace std;
/*
Encapsulation is the act of bundling (data + methods in a class) and hiding (using private, protected access specifiers). It's the mechanism.

Abstraction is the result or the concept. It's the simplified view you get by focusing only on what's important and ignoring the hidden details.
*/

class MyClass
{

public:
    // Public member variable storing the name of the object
    // In real-world applications, this would typically be private with getter/setter methods
    string name;

    // Default Constructor
    MyClass(const string &n = "Default") : name(n)
    {
        cout << "Constructor called for: " << name << endl;
    }

    // Copy Constructor
    MyClass(const MyClass &other) : name(other.name + "_copy")
    {
        cout << "Copy Constructor called for: " << name << " from " << other.name << endl;
    }

    // Move Constructor (C++ 11+) - for completeness, though not strictly about copy
    // Improves performance by avoiding deep copies for temporary objects.
    MyClass(MyClass &&other) noexcept : name(other.name + "_moved")
    {
        cout << "Move Constructor called for: " << name << " from " << other.name << endl;
        other.name = "MOVED_FROM_" + other.name; // Indicate moved-from state
    }

    // Destructor
    // No parameters, No return type, Cannot be overloaded
    // a C++ class can only have one destructor.
    // If your class uses dynamic memory allocation, you MUST free memory inside destructor.
    ~MyClass()
    {
        cout << "Destructor called for: " << name << endl;
    }

    // Display method to print the object's name
    // The const keyword ensures this method doesn't modify the object's state
    void display() const
    {
        cout << "MyClass object name: " << name << endl;
    }

private:
    // Friend function to overload the << operator for easy printing of MyClass objects
    // this is always a pinter to current object, not the object itself, so always this->, never this.
    // This allows us to use cout << myClassObject directly
    // friend have no effect of access specifiers, friend simply implies that this function can access private and protected members of MyClass
    // ostream is the standard output stream class in C++, while cout is an instance of ostream used for console output.
    // returning ostream& allows chaining of output operations (e.g., cout << obj1 << obj2;)
    friend ostream &operator<<(ostream &o, const MyClass &obj)
    {
        // since friend function is not a member function, it does not have access to 'this' pointer
        // o << "printing ostream overload " << this.name << "\n";
        o << "printing ostream overload " << obj.name << "\n";
        return o;
    }
};

// --- Scenarios where Copy Constructor is Called ---

// 1. Pass by Value: Object passed as function argument
void func_passByValue(MyClass obj)
{
    cout << "  Inside func_passByValue, received: ";
    obj.display();
    // When obj goes out of scope, its destructor is called
} // Destructor for 'obj' (the copy) is called here

// 2. Return by Value: Returning object from a function
MyClass func_returnByValue(const string &name_prefix)
{
    MyClass temp_obj("Temp_" + name_prefix); // Constructor
    cout << "  Inside func_returnByValue, returning: ";
    temp_obj.display();
    return temp_obj; // Copy Constructor (or Move/Elision) can happen here
}

class MyClass2
{
private:
    int *data;
    int size;

public:
    // 1. Constructor
    MyClass2(int s) : size(s)
    {
        data = new int[size];
    }

    // 2. Destructor (Crucial for Rule of Three)
    ~MyClass2()
    {
        delete[] data;
    }

    // --- YOUR REQUESTED IMPLEMENTATIONS ---

    // 3. Copy Constructor
    // Purpose: Create a NEW object as a copy of an existing one.
    MyClass2(const MyClass2 &other)
    {
        size = other.size;
        // Deep Copy: Allocate new memory and copy values
        data = new int[size];
        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }
    }

    // 4. Copy Assignment Operator
    // Purpose: Replace the data of an ALREADY EXISTING object with another's.
    MyClass2 &operator=(const MyClass2 &other)
    {
        // Self-assignment check: what if someone does 'a = a;'?
        if (this == &other)
        {
            return *this;
        }

        // Clean up current existing resource
        delete[] data;

        // Re-allocate and copy (Deep Copy)
        size = other.size;
        data = new int[size];
        for (int i = 0; i < size; i++)
        {
            data[i] = other.data[i];
        }

        // Return a reference to allow 'a = b = c;'
        return *this;
    }
};

int main()
{
    cout << "--- Main Start ---" << endl;

    // MyClass car1 =MyClass(); // will iterprete Car() as a function
    // Object Initialization (Copy-Initialization)
    cout << "\n--- Scenario: Object Initialization (Copy-Initialization) ---" << endl;
    MyClass original("Original"); // Constructor
    cout << original;
    MyClass copy_init_obj = original;    // Copy Constructor called (copying 'original')
    MyClass moveObject = move(original); // move constructor is called
    copy_init_obj.display();
    original.display();

    cout << "\n--- Scenario: Object Initialization (Direct-Initialization) ---" << endl;
    // Direct initialization usually does NOT call copy constructor if a matching constructor exists
    MyClass direct_init_obj("DirectInit"); // Constructor called directly

    // Test specific form where C++17 guarantees copy elision for temporaries
    cout << "\n--- Scenario: Object Initialization (Temp Object Copy-Init) ---" << endl;
    MyClass temp_copy_init_obj = MyClass("Temporary"); // Constructor called. Copy/Move elided (C++17 guaranteed)
    temp_copy_init_obj.display();

    cout << "\n--- Scenario: Pass by Value ---" << endl;
    MyClass sender("Sender"); // Constructor
    func_passByValue(sender); // Copy Constructor called (to create 'obj' inside the function)
    sender.display();         // Original 'sender' is unchanged

    cout << "\n--- Scenario: Return by Value ---" << endl;
    MyClass returned_obj = func_returnByValue("FromFunc"); // Constructor for temp_obj. Then potentially Copy/Move for returned_obj.
                                                           // Usually elided in modern C++ (NRVO).
    returned_obj.display();

    cout << "\n--- Scenario: Adding to vector by value ---" << endl;
    // vector stores copies of objects, demonstrating how containers use copy constructors
    vector<MyClass> myVector;
    MyClass element_to_add("VectorElement"); // Constructor
    myVector.push_back(element_to_add);      // Copy Constructor called (to copy 'element_to_add' into vector)
    element_to_add.display();                // Original element_to_add is unchanged

    cout << "\n--- Main End ---" << endl;

    return 0;
} // Destructors for all stack-allocated objects (original, copy_init_obj, sender, returned_obj, elements in myVector) called here