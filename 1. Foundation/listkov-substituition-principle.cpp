#include <bits/stdc++.h>
using namespace std;

/*
Objects of a derived class must be usable wherever objects of the base class are expected, without breaking correctness.
Liskov Substitution Principle (LSP)
In simple words:
👉 Subtypes must be substitutable for their base types.
When to apply LSP:
    -You have a class hierarchy with inheritance
    -You want to ensure derived classes behave correctly when used as base class objects

| Principle | Focus                               |
| --------- | ----------------------------------- |
| LSP   | Correct inheritance behavior            |
| ISP   | Small, role-specific interfaces         |
| DIP   | Depend on abstractions, not details     |
*/

class Rectangle
{
public:
    virtual void setWidth(int w) { width = w; }
    virtual void setHeight(int h) { height = h; }

    int getArea() const
    {
        return width * height;
    }

protected:
    int width;
    int height;
};

class Square : public Rectangle
{
public:
    void setWidth(int w) override
    {
        width = height = w;
    }

    void setHeight(int h) override
    {
        width = height = h;
    }
};

void process(Rectangle &r)
{
    r.setWidth(5);
    r.setHeight(10);
    // Expect area = 50
    std::cout << r.getArea() << std::endl;
}

int main()
{

    Rectangle r;
    Square s;

    process(r); // prints 50
    process(s); // prints 100 ❌
    // Subtypes must not strengthen preconditions or weaken postconditions
    // square and rectangle should inherit from a common more generic Shape base class instead
    // If client code needs if (derivedType) → LSP is broken
    return 0;
}