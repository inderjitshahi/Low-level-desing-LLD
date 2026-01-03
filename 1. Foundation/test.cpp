#include <bits/stdc++.h> // Include all standard libraries (not recommended for production code)
using namespace std;     // Using namespace std (generally avoided in larger projects to prevent name conflicts)

/**
 * @class Car
 * @brief A simple class representing a car with basic attributes and functionality
 *
 * This class demonstrates basic C++ class concepts including:
 * - Member variables
 * - Member functions
 * - Constructor initialization using initializer list
 */
class Car
{
public:
    // Public member variables (in practice, these should typically be private with getter/setter methods)
    string brand; // The manufacturer of the car
    string name;  // The model name of the car
    int year;     // The manufacturing year of the car

    /**
     * @brief Method to simulate driving the car
     * Outputs the car's details in a formatted string
     */
    void drive()
    {
        cout << "Driving a " << brand << " " << name << " from " << year << endl;
    }
    /**
     * @brief Constructor for Car class using initializer list
     * @param b The brand of the car
     * @param n The name/model of the car
     * @param y The manufacturing year
     *
     * Uses initializer list syntax (: brand(b), ...) which is more efficient
     * than assigning values in the constructor body
     */
    Car(const string &b, const string &n, const int &y) : brand(b), name(n), year(y) {}
};

int main()
{
    // Important note about constructors:
    // If you define ANY constructor for your class (even just one parameterized constructor),
    // the compiler will NOT automatically generate a default constructor (a zero-parameter constructor) for you.

    /* Commented out example of aggregate initialization (would only work if no constructor was defined):
     * Car car = {"Toyota", "Corolla", 2020};
     */

    // Example of proper object initialization using parameterized constructor
    Car car = Car("Toyota", "Corolla", 2020); // Copy elision optimization applies here
    // copy elision: compiler optimization that eliminates unnecessary copying of objects, especially for temporary objects by constructing them directly in the memory location where they are needed. it not apply when using new keyword. only applies for stack allocation.
    /* Examples of heap allocation (commented out to prevent memory leaks):
     * Car *car2 = new Car("Honda", "Civic", 2021);
     * car2->drive();
     * delete car2;  // Would be necessary to prevent memory leaks
     */

    // Call the drive method on our stack-allocated car object
    car.drive();

    return 0; // Program completed successfully
}
