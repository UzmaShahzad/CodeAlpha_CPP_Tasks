#include<iostream>
#include "registration.h"
#include<string>

bool User::checkUsername(string name)
{
    ifstream file("users.txt");

    string savedUsername, savedPassword;

    while (file >> savedUsername >> savedPassword)
    {
        if (savedUsername == name)
        {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

void User::registration()
{
    cout << "\nEnter Username: ";
    cin >> username;

    if (checkUsername(username))
    {
        cout << "\nUsername already exists!\n";
        return;
    }

    cout << "Enter Password: ";
    cin >> password;

    if (password.length() < 6)
    {
        cout << "\nPassword must be at least 6 characters!\n";
        return;
    }

    ofstream file("users.txt", ios::app);

    file << username << " " << password << endl;

    file.close();

    cout << "\nRegistration Successful!\n";
}

void User::login()
{
    string enteredUsername, enteredPassword;
    string savedUsername, savedPassword;

    cout << "\nEnter Username: ";
    cin >> enteredUsername;

    cout << "Enter Password: ";
    cin >> enteredPassword;

    ifstream file("users.txt");

    bool found = false;

    while (file >> savedUsername >> savedPassword)
    {
        if (savedUsername == enteredUsername &&
            savedPassword == enteredPassword)
        {
            found = true;
            break;
        }
    }

    file.close();

    if (found)
    {
        cout << "\nLogin Successful! Welcome "
            << enteredUsername << "!\n";
    }
    else
    {
        cout << "\nInvalid Username or Password!\n";
    }
}