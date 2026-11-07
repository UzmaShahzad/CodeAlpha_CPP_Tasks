#include<iostream>
#include<string>
#include "registration.h"

int main()
{
    User user;
    int choice;

    do
    {
        cout << "\n========== LOGIN SYSTEM ==========\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";

        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            user.registration();
            break;

        case 2:
            user.login();
            break;

        case 3:
            cout << "\nThank you for using the system!\n";
            break;

        default:
            cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 3);

    return 0;
}
