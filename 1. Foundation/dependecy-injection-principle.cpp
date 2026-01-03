#include <bits/stdc++.h>
using namespace std;

/*
 Dependency Inversion Principle (DIP) — quick guide:
 - High-level modules should not depend on low-level modules. Both should depend on abstractions.
 - Abstractions should not depend on details. Details should depend on abstractions.

 This example demonstrates DIP by having `Application` depend on the `Database` interface
 (an abstract class) instead of concrete database implementations (`MYSQLDatabase`, `MongoDBDatabase`).
 Concrete implementations are injected into `Application`, allowing easy swapping, testing,
 and reduced coupling. DIP lets us change implementations without modifying business logic.

 How the example satisfies "abstractions should not depend on details":
 - `Database` is a pure abstraction: it declares `connect()` and contains no DB-specific code.
 - Concrete classes (`MYSQLDatabase`, `MongoDBDatabase`) implement `Database` — they depend on the
     abstraction (they provide details), not the other way around.
 - `Application` uses only the `Database` abstraction and has no compile-time dependency on
     MySQL or MongoDB specifics, so abstraction remains independent of details.
     Rule	How we implemented

High-level should depend on abstraction	UserService → Database
Low-level should depend on abstraction	MySQLDatabase → Database
Abstraction should not depend on details	Database has zero knowledge of concrete DBs

Dependency Injection is a technique to supply dependencies from outside instead of creating them internally.

 Notes:
 - Injection is shown via constructor and raw pointers; prefer `unique_ptr`/`shared_ptr` in real code.
 - When using raw pointers, ensure the injected object's lifetime exceeds the consumer's.
*/
class Database
{
public:
    virtual void connect() = 0;
    virtual ~Database() = default;
};

class MYSQLDatabase : public Database
{
public:
    void connect() override
    {
        cout << "Connected to MySQL Database" << endl;
    }
};

class MongoDBDatabase : public Database
{
public:
    void connect() override
    {
        cout << "Connected to MongoDB Database" << endl;
    }
};

class Application
{
    // application depends on Database abstraction, not on concrete implementations, following Dependency Injection Principle
    Database *db;

public:
    Application(Database *database) : db(database) {}

    void initialize()
    {
        db->connect();
    }
};

// ------- Object Slicing Example -------
// Object slicing happens when a derived object is copied into a base-class object by value.
// The base subobject is copied but derived-specific data and behavior are lost.
// The code below demonstrates slicing and contrasts it with pointer/reference polymorphism.
class SBase
{
public:
    string tag;
    SBase(const string &t = "SBase") : tag(t) {}
    virtual void who() { cout << "SBase: " << tag << endl; }
};

class SDerived : public SBase
{
public:
    int extra;
    SDerived(const string &t = "SDerived", int e = 0) : SBase(t), extra(e) {}
    void who() override { cout << "SDerived: " << tag << ", extra=" << extra << endl; }
};

int main()
{
    Application app1(new MYSQLDatabase());
    app1.initialize();

    MongoDBDatabase mongoDB;
    Application *app2 = new Application(&mongoDB);
    app2->initialize();
    delete app2;

    // --- object slicing demo ---
    cout << "\nObject slicing demonstration:\n";
    SDerived derived("MyDerived", 99);

    // Slicing: copying derived into base object by value — derived parts lost
    SBase sliced = derived; // derived is sliced into SBase
    sliced.who();           // calls SBase::who(), derived info lost

    // Contrast: reference/pointer preserve polymorphism
    SBase &ref = derived;
    ref.who(); // calls SDerived::who()
    SBase *ptr = &derived;
    ptr->who(); // calls SDerived::who()
    return 0;
}