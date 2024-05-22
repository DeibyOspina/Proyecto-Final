#pragma once
#include <list>
#include <iostream>
#include "./Tarea.cpp"
using namespace std;

class Tarea;

class Proyecto
{
private:
    
    string nombre;
    string descripcion;
    string propietario;
    string estado;

    list<Tarea *> *tareas;
    list<Nota *> notas;

public:
    Proyecto(string nombre, string propietario, string descripcion, string estado);
    Proyecto(string nombre, string descripcion, string propietario);

    string getNombre() const;
    void setNombre(string nombre);

    string getPropietario() const;
    void setPropietario(string propietario);

    string getEstado() const;
    void setEstado(string estado);

    string getDescripcion() const;
    void setDescripcion(string descripcion);

    list<Nota *> getNotas() const;
    void addNota(Nota *nota);
};

Proyecto::Proyecto(string nombre, string descripcion, string propietario, string estado)
{
    this->nombre = nombre;
    this->propietario = propietario;
    this->descripcion = descripcion;
    this->estado = estado;
}

Proyecto::Proyecto(string nombre, string descripcion, string propietario)
{
    this->nombre = nombre;
    this->descripcion = descripcion;
    this->propietario = propietario;
}

string Proyecto::getNombre() const
{
    return nombre;
}

void Proyecto::setNombre(string nombre)
{
    this->nombre = nombre;
}

string Proyecto::getPropietario() const
{
    return propietario;
}

void Proyecto::setPropietario(string propietario)
{
    this->propietario = propietario;
}

string Proyecto::getEstado() const
{
    return estado;
}

void Proyecto::setEstado(string estado)
{
    this->estado = estado;
}

string Proyecto::getDescripcion() const
{
    return descripcion;
}

void Proyecto::setDescripcion(string descripcion)
{
    this->descripcion = descripcion;
}

void Proyecto::addNota(Nota *nota)
{
    notas.push_back(nota);
}

list<Nota *> Proyecto::getNotas() const
{
    return notas;
}