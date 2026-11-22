
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    string name;
    int age, rollno;

    // Open file in write mode
    ofstream fout;
    fout.open("student.txt", ios::out);

    cout << "Enter Student Name: ";
    cin >> name;

    cout << "Enter Age: ";
    cin >> age;

    cout << "Enter Roll Number: ";
    cin >> rollno;

    // Write student details
    fout << "Student Details" << endl;
    fout << "Name: " << name << endl;
    fout << "Age: " << age << endl;
    fout << "Roll Number: " << rollno << endl;

    // Close write mode
    fout.close();

    cout << "\nData written successfully!\n";

    // Open file in read mode
    ifstream fin;
    fin.open("student.txt", ios::in);

    cout << "\nReading Student Details:\n";
    cout << "------------------------\n";

    string line;

    while (getline(fin, line))
    {
        cout << line << endl;
    }

    // Close read mode
    fin.close();

    return 0;
}
