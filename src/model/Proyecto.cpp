#pragma once

#include <iostream>
using namespace std;

class Proyecto
{
private:
    string nombre;
    string descripcion;
    string propietario;
    string estado;

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
};

Proyecto::Proyecto(string nombre, string descripcion, string propietario, string estado)
{
    this->nombre = nombre;
    this->propietario = propietario;
    this->estado = estado;
    this->descripcion = descripcion;
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
