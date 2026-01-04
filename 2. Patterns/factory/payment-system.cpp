#include <bits/stdc++.h>
using namespace std;

/*
Using strategy+factory pattern
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

    return 0;
}