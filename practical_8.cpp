#include<iostream>
#include<stdlib.h>
#include<string.h>

using namespace std;

template<typename T>
void sort(T a[],int n)
{
    int pos;
    T temp;

    for(int i=0;i<n-1;i++)
    {
        pos=i;
        for(int j=i+1;j<n;j++)
        {
            if (a[j]<a[pos])
            pos=j;
        }
        if (pos!=i)
        {
            temp=a[i];
            a[i]=a[pos];
            a[pos]=temp;
        }
    }
    //display element
    cout<<"sorted elements are ";
    for(int k=0;k<n;k++)
    { 
        cout<<"\n"<<a[k];
    }
}

int main()
{
    int ch;
    int no;
    int ele;
    int fno;
    while(1)
    {
        cout<<"\nSORTING MENU \n1.integer sorting\n2.character sorting\n3.float sorting\n4.exit";
        cout<<"\nEnter choice: ";
        cin>>ch;
        switch(ch)
        {
            case 1:
                cout<<"\nInteger sorting\n";
                cout<<"\nEnter no of element to be sorted\n";
                cin>>no;
                int sor1[100];
                cout<<"\nEnter element\n";
                for(int i=0;i<no;i++)
                {
                    cin>>sor1[i];
                }
                sort<int>(sor1,no); 
                break;
            case 2:
                cout<<"\ncharacter sorting\n";
                cout<<"\nenter no of element to be sorted\n";
                cin>>ele;
                char sor2[100];
                cout<<"\nenter element\n";
                for(int i=0;i<ele;i++)
                {
                    cin>>sor2[i];
                }
                sort<char>(sor2,ele);
                break;
            case 3:
                cout<<"\nfloating type sorting\n";
                cout<<"\nenter no of element to be sorted\n";
                cin>>fno;
                float sor3[100];
                cout<<"\nenter element\n";
                for(int i=0;i<fno;i++)
                {
                    cin>>sor3[i];
                }
                sort<float>(sor3,fno);
                break;
            case 4:
                cout<<"\nEXITING";
                exit(0);
        } 
    }
    return 0;
}

















#include<iostream>
#include<stdlib.h>
using namespace std;

// Template function for input
template<typename T>
void accept(T a[], int n)
{
    cout << "\nEnter elements:\n";

    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
}

// Template function for Bubble Sort
template<typename T>
void sort(T a[], int n)
{
    T temp;

    for(int i = 0; i < n-1; i++)
    {
        for(int j = 0; j < n-i-1; j++)
        {
            if(a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }

    // Display sorted elements
    cout << "\nSorted elements are:\n";

    for(int k = 0; k < n; k++)
    {
        cout << "\n" << a[k];
    }
}

int main()
{
    int ch, n;

    while(1)
    {
        cout << "\n\nSORTING MENU";
        cout << "\n1. Integer sorting";
        cout << "\n2. Character sorting";
        cout << "\n3. Float sorting";
        cout << "\n4. Exit";

        cout << "\nEnter choice: ";
        cin >> ch;

        switch(ch)
        {
            case 1:
            {
                cout << "\nInteger sorting";
                cout << "\nEnter number of elements: ";
                cin >> n;

                int sor1[100];

                accept(sor1, n);
                sort(sor1, n);

                break;
            }

            case 2:
            {
                cout << "\nCharacter sorting";
                cout << "\nEnter number of elements: ";
                cin >> n;

                char sor2[100];

                accept(sor2, n);
                sort(sor2, n);

                break;
            }

            case 3:
            {
                cout << "\nFloat sorting";
                cout << "\nEnter number of elements: ";
                cin >> n;

                float sor3[100];

                accept(sor3, n);
                sort(sor3, n);

                break;
            }

            case 4:
                cout << "\nEXITING";
                exit(0);

            default:
                cout << "\nInvalid choice!";
        }
    }

    return 0;
}










#include<iostream>
#include<stdlib.h>
using namespace std;

template<typename T>
void sort(T a[], int n)
{
    T temp;

    // Accept elements
    cout << "\nEnter elements:\n";
    for(int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    // Bubble Sort
    for(int i = 0; i < n-1; i++)
    {
        for(int j = 0; j < n-i-1; j++)
        {
            if(a[j] > a[j+1])
            {
                temp = a[j];
                a[j] = a[j+1];
                a[j+1] = temp;
            }
        }
    }

    // Display sorted elements
    cout << "\nSorted elements are:\n";
    for(int i = 0; i < n; i++)
    {
        cout << "\n" << a[i];
    }
}

int main()
{
    int ch, n;

    while(1)
    {
        cout << "\n\nSORTING MENU";
        cout << "\n1. Integer sorting";
        cout << "\n2. Character sorting";
        cout << "\n3. Float sorting";
        cout << "\n4. Exit";

        cout << "\nEnter choice: ";
        cin >> ch;

        switch(ch)
        {
            case 1:
            {
                cout << "\nEnter number of elements: ";
                cin >> n;

                int sor1[100];
                sort(sor1, n);
                break;
            }

            case 2:
            {
                cout << "\nEnter number of elements: ";
                cin >> n;

                char sor2[100];
                sort(sor2, n);
                break;
            }

            case 3:
            {
                cout << "\nEnter number of elements: ";
                cin >> n;

                float sor3[100];
                sort(sor3, n);
                break;
            }

            case 4:
                cout << "\nEXITING";
                exit(0);

            default:
                cout << "\nInvalid choice!";
        }
    }

    return 0;
}