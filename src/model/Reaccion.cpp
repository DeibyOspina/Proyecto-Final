#pragma once

#include <iostream>
#include "./Usuario.cpp"
#include "../Utils/Reacciones.cpp"
using namespace std;

class Usuario;

class Reaccion : public Reacciones
{
private:
    string nombre;
    Usuario *autor;

public:
    Reaccion();
};

Reaccion::Reaccion()
{
}