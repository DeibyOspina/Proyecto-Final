#pragma once

#include <iostream>
#include "./Responsable.cpp"
using namespace std;

class Responsable;

class Usuario
{
private:
    string username;
    string password;
    Responsable *responsable;

public:
    Usuario(string username, string password, Responsable *responsable);
    Usuario(string username, string password);
    string getUsername();
    void setUsername(string username);
    string getPassword();
    void setPassword(string password);
    Responsable *getResponsable();
    void setResponsable(Responsable *responsable);
};

Usuario::Usuario(string username, string password, Responsable *responsable)
{
    this->username = username;
    this->password = password;
    this->responsable = responsable;
}

Usuario::Usuario(string username, string password){
    this->username = username;
    this->password = password;
}

string Usuario::getUsername()
{
    return username;
}

void Usuario::setUsername(string username)
{
    this->username = username;
}

string Usuario::getPassword()
{
    return password;
}

void Usuario::setPassword(string password)
{
    this->password = password;
}

Responsable *Usuario::getResponsable()
{
    return responsable;
}

void Usuario::setResponsable(Responsable *responsable)
{
    this->responsable = responsable;
}