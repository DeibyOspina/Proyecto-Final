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
    Reaccion(string nombre, Usuario *autor);

    string getNombre() const;
    void setNombre(string nombre);

    Usuario *getAutor() const;
    void setAutor(Usuario *autor);
};

Reaccion::Reaccion()
{
}

Reaccion::Reaccion(string nombre, Usuario *autor)
{
    this->nombre = nombre;
    this->autor = autor;
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