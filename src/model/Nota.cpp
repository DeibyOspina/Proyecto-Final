#pragma once

#include <iostream>
#include <vector>
#include "./Usuario.cpp"
#include "./Reaccion.cpp"
using namespace std;

class Usuario;

class Nota
{
private:
    
    string titulo;
    string descripcion;

    Usuario *autor;
    vector<Reaccion *> reacciones;


public:
    Nota();
    Nota(string titulo, string descripcion, Usuario *autor);

    string getTitulo() const;
    void setTitulo(string titulo);

    string getDescripcion() const;
    void setDescripcion(string descripcion);

    Usuario *getAutor() const;
    void setAutor(Usuario *autor);

    vector<Reaccion *> getReacciones() const;
    void addReaccion(Reaccion *reaccion);
    string convertReaccionesToString() const;

};
Nota::Nota() {}

Nota::Nota(string titulo, string descripcion, Usuario *autor)
{
    this->titulo = titulo;
    this->descripcion = descripcion;
    this->autor = autor;
}

string Nota::getTitulo() const
{
    return titulo;
}

void Nota::setTitulo(string titulo)
{
    this->titulo = titulo;
}

string Nota::getDescripcion() const
{
    return descripcion;
}

void Nota::setDescripcion(string descripcion)
{
    this->descripcion = descripcion;
}

Usuario *Nota::getAutor() const
{
    return autor;
}

void Nota::setAutor(Usuario *autor)
{
    this->autor = autor;
}

vector<Reaccion *> Nota::getReacciones() const
{
    return reacciones;
}

void Nota::addReaccion(Reaccion *reaccion)
{
    reacciones.push_back(reaccion);
}

string Nota::convertReaccionesToString() const
{
    string reaccionesString = "";
    for (Reaccion *reaccion : reacciones)
    {
        reaccionesString += reaccion->getNombre() + " - ";
    }
    return reaccionesString;
}