#include <bits/stdc++.h>
using namespace std;
/*
Interface Segregation Principle (ISP)

Clients should not be forced to depend on interfaces they do not use.

In simple words:
👉 Prefer many small, specific interfaces over one big “fat” interface.

When to apply ISP:
    -Different clients use different subsets of behavior
    -You see empty methods / exceptions
    -Interfaces start growing too large
    -You expect frequent changes in features
*/

class Notification
{
public:
    virtual void sendEmail() = 0;
    virtual void sendSMS() = 0;
    virtual void sendPush() = 0;
};

class EmailNotification
{
public:
    virtual void sendEmail() = 0;
};

class SMSNotification
{
public:
    virtual void sendSMS() = 0;
};

class PushNotification
{
public:
    virtual void sendPush() = 0;
};

class EmailService : public EmailNotification
{
public:
    void sendEmail() override {}
};

class SMSService : public SMSNotification
{
public:
    void sendSMS() override {}
};

// ISP works best with Dependency Inversion.
// High-level module depends on small abstractions, not on concrete implementations.
class OrderService
{
    EmailNotification *notifier;

public:
    OrderService(EmailNotification *notifier)
        : notifier(notifier) {}

    void placeOrder()
    {
        notifier->sendEmail();
    }
};

int main()
{

    return 0;
}