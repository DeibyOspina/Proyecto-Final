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
    vector<Tarea*> tareas;

public:
    Responsable(string nombre);
    
    vector<Tarea*> getTareas();
    void setTareas(vector<Tarea*> tareas);
    void addTarea(Tarea* tarea);

    void setNombre(string nombre);
    string getNombre();
};



Responsable::Responsable(string nombre) : nombre(nombre) {}

void Responsable::setNombre(string nombre)
{
    this->nombre = nombre;
}

vector<Tarea*> Responsable::getTareas()
{
    return this->tareas;
}

void Responsable::setTareas(vector<Tarea*> tareas)
{
    this->tareas = tareas;
}

void Responsable::addTarea(Tarea* tarea)
{
    tareas.push_back(tarea);
}

string Responsable::getNombre()
{
    return nombre;
}
