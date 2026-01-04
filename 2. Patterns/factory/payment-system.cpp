#include <bits/stdc++.h>
using namespace std;

/*
Using strategy+factory pattern

std::function<ReturnType(ArgumentTypes...)> wrapper_name; storing functions instead data
unordered_map<PaymentType, function<PaymentStrategy*()>> registry;
map[TYPE] = [](){ return new CreditCard(); };  A pointer to the logic (the lambda). runs only when: registry[type]()
*/

class PaymentStrategy
{
public:
    virtual bool pay(int amount) = 0;
    virtual ~PaymentStrategy() {}
};

class UpiPayment : public PaymentStrategy
{
public:
    bool pay(int amount) override
    {
        cout << "Processing UPI payment of ₹" << amount << endl;
        return true;
    }
};

class CardPayment : public PaymentStrategy
{
public:
    bool pay(int amount) override
    {
        cout << "Processing Card payment of ₹" << amount << endl;
        return true;
    }
};

class NetBankingPayment : public PaymentStrategy
{
public:
    bool pay(int amount) override
    {
        cout << "Processing NetBanking payment of ₹" << amount << endl;
        return true;
    }
};

enum class PaymentType
{
    UPI,
    CARD,
    NETBANKING
};

class PaymentStrategyFactory
{
public:
    static PaymentStrategy *createStrategy(PaymentType type)
    {
        switch (type)
        {
        case PaymentType::UPI:
            return new UpiPayment();
        case PaymentType::CARD:
            return new CardPayment();
        case PaymentType::NETBANKING:
            return new NetBankingPayment();
        default:
            return nullptr;
        }
    }
};

class PaymentService
{
private:
    PaymentStrategy *strategy;

public:
    PaymentService(PaymentStrategy *strategy) : strategy(strategy) {}

    void processPayment(int amount)
    {
        strategy->pay(amount)
    }

    ~PaymentService()
    {
        delete strategy;
    }
};

int main()
{
    // the factory pattern, but violating the ocp principal as if else in createStrategy
    // with PaymentStrategyFactory interface and derived classes, automatically ocp compliant
    PaymentStrategy *strategy =
        PaymentStrategyFactory::createStrategy(PaymentType::UPI);

    PaymentService service(strategy); // the strategy pattern
    service.processPayment(500);

    return 0;
}
