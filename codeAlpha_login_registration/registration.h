#ifndef USER_H
#define USER_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class User
{
private:
    string username;
    string password;

public:
    bool checkUsername(string name);
    void registration();
    void login();
};

#endif
