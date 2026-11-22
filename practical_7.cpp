
#include <iostream>
#include <string>
using namespace std;

class InvalidUser {
public:
    string message;

    InvalidUser(string msg) {
        message = msg;
    }
};

int main() {
    int age;
    float income;
    string city, vehicle;

    cout << "Enter Age: ";
    cin >> age;

    cout << "Enter Monthly Income: ";
    cin >> income;

    cout << "Enter City: ";
    cin >> city;

    cout << "Do you have a 4-wheeler (Yes/No): ";
    cin >> vehicle;

    try {
        if (age < 18 || age > 55) {
            throw InvalidUser("Age must be between 18 and 55.");
        }

        if (income < 50000 || income > 100000) {
            throw InvalidUser("Income must be between Rs. 50,000 and Rs. 1,00,000.");
        }

        if (city != "Pune" && city != "Mumbai" &&
            city != "Bangalore" && city != "Chennai") {
            throw InvalidUser("City must be Pune, Mumbai, Bangalore or Chennai.");
        }

        if (vehicle != "Yes" && vehicle != "yes" && vehicle != "YES") {
            throw InvalidUser("User must have a 4-wheeler.");
        }

        cout << "\nUser meets all the criteria!";
    }
    catch (InvalidUser e) {
        cout << "\nException: " << e.message;
    }

    return 0;
}
