#include <bits/stdc++.h>
using namespace std;

class PricingStrategy
{
public:
    virtual double calculateFare(double distance, double minTime) = 0;
    ~PricingStrategy() = default;
};

class NormalPricing : public PricingStrategy
{
public:
    double calculateFare(double distance, double minTime) override
    {
        return (distance * 10 + minTime * 2);
    }
};

class SurgePricing : public PricingStrategy
{
    double surgeMultiplier;

public:
    SurgePricing(double multiplier) : surgeMultiplier(multiplier) {}

    double calculateFare(double distance, double minTime) override
    {
        double baseFare = (distance * 10 + minTime * 2);
        return surgeMultiplier * baseFare;
    }
};

class NightPricing : public PricingStrategy
{
public:
    double calculateFare(double distance, double minTime) override
    {
        double baseFare = distance * 10 + minTime * 2;
        return baseFare + 50;
    }
};

class RidePricingContext
{
    unique_ptr<PricingStrategy> pricingStrategy;

public:
    RidePricingContext(PricingStrategy *strategy) : pricingStrategy(strategy) {}

    void setStrategy(PricingStrategy *strategy)
    {
        pricingStrategy.reset(strategy);
    }
    double calculatePrice(double distance, double minTime)
    {
        return pricingStrategy->calculateFare(distance, minTime);
    }
};

int main()
{   
    // ocp, srp, dip covered
    // strategies
    PricingStrategy *normal = new NormalPricing();
    PricingStrategy *night = new NightPricing();
    PricingStrategy *surge = new SurgePricing(1.6);

    RidePricingContext context(normal);
    cout << "Normal Fare: " << context.calculatePrice(10, 15) << "\n";

    context.setStrategy(night);
    cout << "Night Fare: " << context.calculatePrice(10, 15) << "\n";

    context.setStrategy(surge);
    cout << "Surge Fare: " << context.calculatePrice(10, 15) << "\n";

    // free up the heap memory to avoid leakage
    delete normal;
    delete night;
    delete surge;

    return 0;
}