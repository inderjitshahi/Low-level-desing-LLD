#include <bits/stdc++.h>
using namespace std;

/*
Encapsulate a request as an object, thereby letting you parameterize clients with different requests, queue or log requests, and support undo operations.

Command Pattern decouples:
    Invoker (who triggers) and,
    Receiver (who does the work)
    via commands

    | Role                    | Responsibility                                 |
| ----------------------- | ---------------------------------------------- |
| **Command (interface)** | Declares `execute()` (and optionally `undo()`) |
| **ConcreteCommand**     | Binds a receiver and implements `execute()`    |
| **Receiver**            | Does the actual work                           |
| **Invoker**             | Triggers the command                           |
| **Client**              | Creates and wires everything                   |
*/

class Command
{
public:
    virtual ~Command() {};
    virtual void execute() = 0;
};

// Receiver(Business logic)
class Light
{
public:
    void turnOn()
    {
        cout << "Light is ON\n";
    }
    void turnOff()
    {
        cout << "Light is OFF\n";
    }
};

// concrete commands
class LightOnCommand : public Command
{
private:
    Light *light;

public:
    LightOnCommand(Light *l) : light(l) {}
    void execute() override
    {
        light->turnOn();
    }
};

class LightOffCommand : public Command
{
private:
    Light *light;

public:
    LightOffCommand(Light *l) : light(l) {}

    void execute() override
    {
        light->turnOff();
    }
};

// Invoker
class RemoteControl
{
private:
    Command *command;

public:
    void setCommand(Command *cmd)
    {
        command = cmd;
    }

    void pressButton()
    {
        if (command)
            command->execute();
    }
};

int main()
{
    //   Client
    //   |
    //   v
    // Invoker (Remote)
    //   |
    //   v
    // Command (execute / undo)
    //   |
    //   v
    // Receiver (Light)

    Light livingRoomLight;
    LightOnCommand lightOn(&livingRoomLight);
    LightOffCommand lightOff(&livingRoomLight);

    RemoteControl remote;
    remote.setCommand(&lightOn);
    remote.pressButton();

    remote.setCommand(&lightOff);
    remote.pressButton();
    return 0;
}