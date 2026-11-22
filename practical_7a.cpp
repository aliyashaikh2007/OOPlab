
#include <iostream>
#include <string>
using namespace std;

class MyException {
public:
    string msg;

    MyException(string m) {
        msg = m;
    }
};

int main() {
    int age;
    float income;
    string city, vehicle;

    try {

        cout << "Enter Age: ";
        cin >> age;

        if (age < 18 || age > 55) {
            throw MyException("Age must be between 18 and 55.");
        }
        
        cout << "Enter Monthly Income: ";
        cin >> income;

        if (income < 50000 || income > 100000) {
            throw MyException("Income must be between Rs. 50,000 and Rs. 1,00,000.");
        }
        
        cout << "Enter City: ";
        cin >> city;

        if (city != "Pune" && city != "Mumbai" &&
            city != "Bangalore" && city != "Chennai") {
            throw MyException("City must be Pune, Mumbai, Bangalore or Chennai.");
        }

        cout << "Do you have a 4-wheeler (Yes/No): ";
        cin >> vehicle;

        if (vehicle != "Yes" && vehicle != "yes") {
            throw MyException("User must have a 4-wheeler.");
        }

        cout << "\nUser meets all the criteria!";
    }

    catch (MyException e) {
        cout << "\nException: " << e.msg<<"\n";
    }

    catch (...) {
        cout << "\nUnknown Exception Occurred!";
    }

    return 0;
}
