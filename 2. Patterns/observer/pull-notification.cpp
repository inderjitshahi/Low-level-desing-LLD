#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;


// 1. Forward declaration
class ISubject;

// 2. The Abstract Observer
class IObserver
{
public:
    virtual ~IObserver() = default;
    // The "Pull" happens because we pass the Subject pointer here
    virtual void update(ISubject *subject) = 0;
};

// 3. The Base Subject
class ISubject
{
protected:
    std::vector<IObserver *> observers;

public:
    virtual ~ISubject() = default;

    void attach(IObserver *obs) { observers.push_back(obs); }

    void detach(IObserver *obs)
    {
        observers.erase(std::remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void notify()
    {
        for (IObserver *obs : observers)
        {
            obs->update(this); // Pass 'this' so observer can pull data
        }
    }
};

// 4. Concrete Subject (The Stock)
class StockMarket : public ISubject
{
    float price;
    string symbol;

public:
    StockMarket(std::string s, float p) : symbol(s), price(p) {}

    void setPrice(float newPrice)
    {
        price = newPrice;
        notify(); // Something changed!
    }

    // Getters for the "Pull"
    float getPrice() const { return price; }
    string getSymbol() const { return symbol; }
};

// 5. Concrete Observer (The Display)
class TradingApp : public IObserver
{
    std::string name;

public:
    TradingApp(std::string n) : name(n) {}

    void update(ISubject *subject) override
    {
        // We cast to the concrete type to "Pull" specific data
        StockMarket *stock = static_cast<StockMarket *>(subject);  //as getPrice is only defined in StockMarket not in ISubject

        std::cout << "[" << name << "] Alert: " << stock->getSymbol()
                  << " is now $" << stock->getPrice() << std::endl;

        //Multiple Subjects, needed if else with dynamic cast, that's why pull model is complex than push model 
        // if (auto *stock = dynamic_cast<StockMarket *>(subject))
        // {
        //     std::cout << "Stock Update: " << stock->getSymbol() << " is $" << stock->getPrice() << "\n";
        // }
        // else if (auto *weather = dynamic_cast<WeatherStation *>(subject))
        // {
        //     std::cout << "Weather Update: " << weather->getTemp() << " degrees.\n";
    }
};


int main()
{
    StockMarket nvida("NVDA", 120.0f);

    TradingApp phoneApp("iPhone");
    TradingApp tabletApp("iPad");

    nvida.attach(&phoneApp);
    nvida.attach(&tabletApp);

    std::cout << "--- Market Update ---" << std::endl;
    nvida.setPrice(125.5f);

    return 0;
}