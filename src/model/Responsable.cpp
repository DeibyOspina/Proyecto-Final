#pragma once

#include <iostream>
#include <set>
#include "./Tarea.cpp"
using namespace std;

class Tarea;

class Responsable
{
private:
    string nombre;
    set<Tarea*> tareas;

public:
    Responsable(string nombre);
    
    set<Tarea*> getTareas();
    void setTareas(set<Tarea*> tareas);
    void addTarea(Tarea* tarea);

    void setNombre(string nombre);
    string getNombre();
};



Responsable::Responsable(string nombre) : nombre(nombre) {}

void Responsable::setNombre(string nombre)
{
    this->nombre = nombre;
}

set<Tarea*> Responsable::getTareas()
{
    return this->tareas;
}

void Responsable::setTareas(set<Tarea*> tareas)
{
    this->tareas = tareas;
}

void Responsable::addTarea(Tarea* tarea)
{
    tareas.insert(tarea);
}

string Responsable::getNombre()
{
    return nombre;
}
