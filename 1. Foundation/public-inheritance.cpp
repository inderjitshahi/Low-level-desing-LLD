#include <iostream>
#include <string>
#include <memory> // For std::unique_ptr (better resource management)

/**
 * The "Derived is a Base" principle in public inheritance means a Derived object structurally contains a complete Base object and can therefore be safely substituted (upcast) via a Base* pointer. This Base* pointer acts as a compile-time viewfinder, only allowing access to members and methods defined in the Base class, and explicitly ignoring any unique Derived members for type safety. At run-time, if the method is declared virtual in the Base, the system uses polymorphism to execute the actual Derived class's implementation, making the object behave like the Derived type despite the Base pointer's limited view.
 *
 * However, the reverse—treating a Base object as a Derived (downcast)—is unsafe and generally disallowed, as the Base object lacks the additional structure and behavior of the Derived class. Attempting such a downcast can lead to undefined behavior, crashes, or data corruption, since the Base object does not fulfill the Derived class's contract.
 *
 *
 * Inheritance: is-a relationship, tight coupling(change in parent, change in all child), low flexibility(parent can't be changed), breaks encapsulation(can inherit protected members), static binding.
 * Composition: has-a relationship, loose coupling, high flexibility(with base pointer, objects can be changed), preserves encapsulation, dynamic binding.
 */

//======================================================================
// SECTION 1: LSP VIOLATION (Your Original Code)
// The principle is that the derived object must be perfectly usable where a base object is expected
//======================================================================

class Rectangle
{
public:
    int width = 0;
    int height = 0;

public:
    Rectangle(int w, int h) : width(w), height(h) {}
    virtual void setWidth(int w) { width = w; }
    virtual void setHeight(int h) { height = h; }
    int getArea() const { return width * height; }
};

class Square : public Rectangle
{
public:
    Square(int side) : Rectangle(side, side) {}
    void setWidth(int w) override
    {
        width = w;
        height = w;
    }
    void setHeight(int h) override
    {
        width = h;
        height = h;
    }
};

void testLSP(Rectangle *rect, const std::string &type)
{
    std::cout << "\n--- Testing " << type << " (LSP Check) ---" << std::endl;
    std::cout << "Calling setWidth(10) and setHeight(5)..." << std::endl;
    rect->setWidth(10);
    rect->setHeight(5);

    int actual_area = rect->getArea();
    std::cout << "Final Dimensions: W=" << rect->width << ", H=" << rect->height << std::endl;
    std::cout << "Actual Area: " << actual_area << " (Expected: 50)" << std::endl;

    if (actual_area != 50)
    {
        std::cout << "** LSP VIOLATION: Contract broken by substitution! **" << std::endl;
    }
}

//======================================================================
// SECTION 2: DOG IS AN ANIMAL (Safe Public Inheritance)
//======================================================================

class Animal
{
public:
    virtual void speak() const { std::cout << "Animal makes a noise." << std::endl; }
    void eat() const { std::cout << "Animal is eating." << std::endl; }
};

class Dog : public Animal
{
public:
    void fetch() const { std::cout << "Dog is fetching a ball." << std::endl; }

    // Fulfills the Animal contract but specializes the behavior
    void speak() const override { std::cout << "Woof! Woof!" << std::endl; }
};

// Function designed to work with any Animal (Base Class)
void takeCareOfAnimal(Animal *a)
{
    std::cout << "\n--- Taking care of an Animal ---" << std::endl;
    a->speak();
    a->eat();

    // The Animal* pointer CANNOT see the Dog-specific 'fetch()' method:
    // a->fetch(); // ERROR: 'class Animal' has no member named 'fetch'
}

//======================================================================
// SECTION 3: BASE IS NOT A DERIVED (Illegal Downcasting)
//======================================================================

void demonstrateIllegalDowncasting()
{
    std::cout << "\n--- Downcasting (Base is NOT a Derived) ---" << std::endl;

    // 1. Create the Base Object
    // We use a smart pointer to ensure proper cleanup, but the object itself is only an Animal.
    std::unique_ptr<Animal> baseAnimal = std::make_unique<Animal>();

    std::cout << "Base object created: Animal." << std::endl;

    // 2. The Illegal/Unsafe Downcast Attempt
    // This is UNSAFE because the object only has Animal members, not Dog members.
    // The static_cast forces the compiler to trust us, leading to potential crashes
    // if we tried to access Dog-specific data.
    Dog *d = static_cast<Dog *>(baseAnimal.get());

    std::cout << "Forced static_cast to Dog* was successful (at compile time)." << std::endl;

    // We can call methods inherited from Animal, but the object remains an Animal:
    d->speak(); // Executes Animal::speak (unless Dog's vtable is somehow used incorrectly)

    // Safely attempting to cast with dynamic_cast (requires Base to be polymorphic, which it is)
    Dog *safe_d = dynamic_cast<Dog *>(baseAnimal.get());

    if (safe_d == nullptr)
    {
        std::cout << "\nSafe cast (dynamic_cast) to Dog* FAILED." << std::endl;
        std::cout << "Reason: The object's actual runtime type is Animal, not Dog." << std::endl;
        std::cout << "Conclusion: Base is NOT a Derived, casting failed safely." << std::endl;
    }
}

//======================================================================
// MAIN EXECUTION
//======================================================================

int main()
{
    // --- PART 1: LSP Violation ---
    Rectangle *rect1 = new Rectangle(1, 1);
    testLSP(rect1, "Rectangle");

    Rectangle *rect2 = new Square(1);
    testLSP(rect2, "Square (LSP Violation)");

    delete rect1;
    delete rect2;

    // --- PART 2: Safe "IS-A" Substitution ---
    // Animal* = new Dog() -> Dog is an Animal, substitution is safe.
    Animal *myDog = new Dog();
    takeCareOfAnimal(myDog); // Dog fulfills the Animal contract
    delete myDog;

    // --- PART 3: Illegal Downcasting ---
    demonstrateIllegalDowncasting();

    return 0;
}