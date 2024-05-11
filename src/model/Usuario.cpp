#pragma once

#include <iostream>
#include "./Responsable.cpp"
using namespace std;

class Usuario
{
private:
    string username;
    string password;
    Responsable *responsable;

public:
    Usuario(string username, string password, Responsable *responsable) : username(username), password(password), responsable(responsable){};
    Usuario(string username, string password) : username(username), password(password){};
    string getUsername()
    {
        return username;
    };

    void setUsername(string username)
    {
        this->username = username;
    };

    string getPassword()
    {
        return password;
    };

    void setPassword(string password)
    {
        this->password = password;
    };

    Responsable *getResponsable()
    {
        return responsable;
    };

    void setResponsable(Responsable *responsable)
    {
        this->responsable = responsable;
    };
};