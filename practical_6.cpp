#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    string name;
    int age, rollno;

    // Create and open file in write mode
    ofstream fout("student.txt");

    cout << "Enter Student Name: ";
    cin >> name;

    cout << "Enter Age: ";
    cin >> age;

    cout << "Enter Roll Number: ";
    cin >> rollno;

    // Write student details into file
    fout << "Student Details" << endl;
    fout << "Name: " << name << endl;
    fout << "Age: " << age << endl;
    fout << "Roll Number: " << rollno << endl;

    // Close the file
    fout.close();

    cout << "\nData written successfully!\n";

    // Reopen file in read mode
    ifstream fin("student.txt");

    cout << "\nReading Student Details:\n";
    cout << "------------------------\n";

    string line;

    // Read and display file contents
    while (getline(fin, line))
    {
        cout << line << endl;
    }

    // Close the file
    fin.close();

    return 0;
}
