#pragma once

#include <iostream>
#include "./Usuario.cpp"
#include "../utils/Reacciones.cpp"
using namespace std;

class Usuario;

class Reaccion : public Reacciones
{
private:
    string nombre;
    Usuario *autor;

public:
    Reaccion();

    string getNombre() const;
    void setNombre(string nombre);

    Usuario *getAutor() const;
    void setAutor(Usuario *autor);
};

Reaccion::Reaccion()
{
}

string Reaccion::getNombre() const
{
    return nombre;
}

void Reaccion::setNombre(string nombre)
{
    this->nombre = nombre;
}

Usuario *Reaccion::getAutor() const
{
    return autor;
}

void Reaccion::setAutor(Usuario *autor)
{
    this->autor = autor;
}