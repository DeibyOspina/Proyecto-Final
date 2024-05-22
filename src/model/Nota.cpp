#pragma once

#include <iostream>
#include <queue>
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
    queue<Reaccion *> reacciones;

public:
    Nota();
    Nota(string titulo, string descripcion, Usuario *autor);

    string getTitulo() const;
    void setTitulo(string titulo);

    string getDescripcion() const;
    void setDescripcion(string descripcion);

    Usuario *getAutor() const;
    void setAutor(Usuario *autor);

    queue<Reaccion *> getReacciones() const;
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

queue<Reaccion *> Nota::getReacciones() const
{
    return reacciones;
}