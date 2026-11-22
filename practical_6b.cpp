
#include <iostream>
#include <fstream>
using namespace std;

class Student
{
    char name[30];
    int age, rollno;

public:
    void accept()
    {
        cout << "Enter Student Name: ";
        cin >> name;

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Roll Number: ";
        cin >> rollno;
    }

    void display()
    {
        cout << "\nStudent Details";
        cout << "\nName: " << name;
        cout << "\nAge: " << age;
        cout << "\nRoll Number: " << rollno;
    }
};

int main()
{
    Student s;

    // Open file in write mode
    ofstream fout;
    fout.open("student.dat", ios::out | ios::binary);

    s.accept();
    // Write student object into file
    fout.write((char*)&s, sizeof(s));

    // Close file
    fout.close();

    cout << "\n\nData written successfully!";

    // Open file in read mode
    ifstream fin;
    fin.open("student.dat", ios::in | ios::binary);

    // Read student object from file
    fin.read((char*)&s, sizeof(s));

    // Display student details
    s.display();

    // Close file
    fin.close();

    return 0;
}
