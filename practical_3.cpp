#include <iostream>
#include <string>

using namespace std;

// Base Class
class Employee
{
protected:
    int empID;
    string empName;

public:
    void acceptEmployee()
    {
        cout << "Enter Employee ID: ";
        cin >> empID;

        cin.ignore();

        cout << "Enter Employee Name: ";
        getline(cin, empName);
    }
};

// Personal Record Class
class PersonalRecord : virtual public Employee
{
protected:
    string dob;
    string address;
    string contact;

public:
    void acceptPersonal()
    {
        cout << "Enter Date of Birth: ";
        getline(cin, dob);

        cout << "Enter Address: ";
        getline(cin, address);

        cout << "Enter Contact Number: ";
        getline(cin, contact);
    }

    void displayPersonal()
    {
        cout << "\n----- PERSONAL RECORD -----";
        cout << "\nEmployee ID      : " << empID;
        cout << "\nEmployee Name    : " << empName;
        cout << "\nDate of Birth    : " << dob;
        cout << "\nAddress          : " << address;
        cout << "\nContact Number   : " << contact;
    }
};

// Professional Record Class
class ProfessionalRecord : virtual public Employee
{
protected:
    string designation;
    string department;
    string organization;
    int experience;

public:
    void acceptProfessional()
    {
        cout << "Enter Designation: ";
        getline(cin, designation);

        cout << "Enter Department: ";
        getline(cin, department);

        cout << "Enter Organization: ";
        getline(cin, organization);

        cout << "Enter Years of Experience: ";
        cin >> experience;
    }

    void displayProfessional()
    {
        cout << "\n\n----- PROFESSIONAL RECORD -----";
        cout << "\nDesignation       : " << designation;
        cout << "\nDepartment        : " << department;
        cout << "\nOrganization      : " << organization;
        cout << "\nExperience        : " << experience << " years";
    }
};

// Academic Record Class
class AcademicRecord : virtual public Employee
{
protected:
    string qualification;
    string specialization;
    string university;
    int passingYear;

public:
    void acceptAcademic()
    {
        cin.ignore();

        cout << "Enter Highest Qualification: ";
        getline(cin, qualification);

        cout << "Enter Specialization: ";
        getline(cin, specialization);

        cout << "Enter University: ";
        getline(cin, university);

        cout << "Enter Passing Year: ";
        cin >> passingYear;
    }

    void displayAcademic()
    {
        cout << "\n\n----- ACADEMIC RECORD -----";
        cout << "\nHighest Qualification : " << qualification;
        cout << "\nSpecialization        : " << specialization;
        cout << "\nUniversity            : " << university;
        cout << "\nPassing Year          : " << passingYear;
    }
};

// Multiple Inheritance
class EmployeeBioData : public PersonalRecord, public ProfessionalRecord, public AcademicRecord
{
public:

    void accept()
    {
        cout << "\n===== ENTER EMPLOYEE BIO-DATA =====\n";

        acceptEmployee();
        acceptPersonal();
        acceptProfessional();
        acceptAcademic();
    }

    void display()
    {
        cout << "\n\n========== EMPLOYEE BIO-DATA ==========";

        displayPersonal();
        displayProfessional();
        displayAcademic();

        cout << "\n\n=======================================\n";
    }
};

// Main Function
int main()
{
    EmployeeBioData emp;

    emp.accept();
    emp.display();

    return 0;
}
