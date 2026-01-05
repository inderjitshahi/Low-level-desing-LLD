#include <bits/stdc++.h>
using namespace std;
/*
What is Abstract Factory?
Abstract Factory provides an interface to create families of related objects without specifying their concrete classes.

Think:
Not one product
But a group of compatible products

📌 Key idea:
If Factory Method creates one object, Abstract Factory creates multiple related objects together.
“Abstract Factory is a factory of factories, producing families of related objects.”
*/

//------------------------------------- Abstract products ------------------------------------//
class Button
{
public:
    virtual void render() = 0;
    virtual ~Button() {}
};

class Checkbox
{
public:
    virtual void render() = 0;
    virtual ~Checkbox() {}
};

//-------------------------------------- Concrete Products --------------------------------------//
class WindowsButton : public Button
{
public:
    void render() override
    {
        cout << "Rendering windows button\n";
    }
};

class WindowsCheckbox : public Checkbox
{
public:
    void render() override
    {
        cout << "Rendering Windows Checkbox\n";
    }
};

class MacButton : public Button
{
public:
    void render() override
    {
        cout << "Rendering Mac Button\n";
    }
};

class MacCheckbox : public Checkbox
{
public:
    void render() override
    {
        cout << "Rendering Mac Checkbox\n";
    }
};

//----------------------------------- abstract factory ----------------------------------//
class UIFactory
{
public:
    virtual Button *createButton() = 0;
    virtual Checkbox *createCheckbox() = 0;
    virtual ~UIFactory() = default;
};

//------------------------------------ Concrete factories --------------------------------//
class WindowsUIFactory : public UIFactory
{
public:
    Button *createButton() override
    {
        return new WindowsButton();
    }

    Checkbox *createCheckbox()
    {
        return new WindowsCheckbox();
    }
};

class MacUIFactory : public UIFactory
{
public:
    Button *createButton() override
    {
        return new MacButton();
    }

    Checkbox *createCheckbox() override
    {
        return new MacCheckbox();
    }
};

//---------------------------------- Client code( most imp ) -------------------------------------//
class Application
{
private:
    UIFactory *factory;
    Button *button;
    Checkbox *checkbox;

public:
    Application(UIFactory *factory) : factory(factory)
    {
        button = factory->createButton();
        checkbox = factory->createCheckbox();
    }

    void renderUi()
    {
        button->render();
        checkbox->render();
    }

    void setFactory(UIFactory *fact)
    {
        factory = fact;
        button = factory->createButton();
        checkbox = factory->createCheckbox();
    }

    ~Application()
    {
        delete factory;
        delete button;
        delete checkbox;
    }
};

int main()
{
    UIFactory *factory = new WindowsUIFactory();
    Application app(factory); // not &factory, because factory itself a pointer not object
    app.renderUi();

    // new factory
    factory = new MacUIFactory();
    app.setFactory(factory);
    app.renderUi();
    return 0;
}