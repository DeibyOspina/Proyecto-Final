#pragma once

#include <iostream>
#include <set>
#include <vector>
#include "./Responsable.cpp"
#include "./Nota.cpp" 
using namespace std;


class Responsable;

class Tarea
{
private:
    string nombre;
    string fechaLimite;
    Responsable *responsable;
    string estado;
    string prioridad;
    string comentario;
    set<Nota *> notas;

public:
    Tarea(string nombre, string fechaLimite, Responsable *responsable, string estado, string prioridad, string comentario);

    string getNombre() const;
    void setNombre(const string &nombre);

    string getFechaLimite() const;
    void setFechaLimite(const string &fechaLimite);

    Responsable *getResponsable() const;
    void setResponsable(Responsable *responsable);

    string getEstado() const;
    void setEstado(const string &Estado);

    string getPrioridad() const;
    void setPrioridad(const string &prioridad);

    string getComentario() const;
    void setComentario(const string &comentario);

    set<Nota *> getNotas() const;
    void setNotas(const set<Nota *> &notas);

    void addNota(Nota *nota);

    vector<string> toVector();
};

Tarea::Tarea(string nombre, string fechaLimite, Responsable *responsable, string estado, string prioridad, string comentario)
{
    this->nombre = nombre;
    this->fechaLimite = fechaLimite;
    this->responsable = responsable;
    this->estado = estado;
    this->prioridad = prioridad;
    this->comentario = comentario;
}

string Tarea::getNombre() const
{
    return nombre;
}

void Tarea::setNombre(const string &nombre)
{
    this->nombre = nombre;
}

string Tarea::getFechaLimite() const
{
    return fechaLimite;
}

void Tarea::setFechaLimite(const string &fechaLimite)
{
    this->fechaLimite = fechaLimite;
}

Responsable *Tarea::getResponsable() const
{
    return responsable;
}

void Tarea::setResponsable(Responsable *responsable)
{
    this->responsable = responsable;
}

string Tarea::getEstado() const
{
    return estado;
}

void Tarea::setEstado(const string &Estado)
{
    this->estado = Estado;
}

string Tarea::getPrioridad() const
{
    return prioridad;
}

void Tarea::setPrioridad(const string &prioridad)
{
    this->prioridad = prioridad;
}

string Tarea::getComentario() const
{
    return comentario;
}

void Tarea::setComentario(const string &comentario)
{
    this->comentario = comentario;
}

set<Nota *> Tarea::getNotas() const
{
    return notas;
}

void Tarea::setNotas(const set<Nota *> &notas)
{
    this->notas = notas;
}

void Tarea::addNota(Nota *nota)
{
    notas.insert(nota);
}