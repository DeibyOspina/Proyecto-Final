#pragma once
#include <iostream>
#include <vector>
#include <set>
#include "./Usuario.cpp"
#include "./Proyecto.cpp"

using namespace std;

class BD
{
private:
    static BD *instance;

    vector<Usuario *> *usuarios;
    vector<Proyecto *> *proyectos;
    Usuario *usuario;

    BD();
    ~BD();

public:
    // No copiable
    BD(BD &bd) = delete;
    // No asignable
    void operator=(const BD &) = delete;
    // Obtener instancia
    static BD *getInstance();

    vector<Usuario *> *getUsuarios();

    Usuario *getUsuario();
    void setUsuario(Usuario *usuario);

    vector<Proyecto *> *getProyectos();
};

BD *BD::instance = nullptr;

BD::BD()
{

    usuarios = new vector<Usuario *>();
    usuarios->push_back(new Usuario("admin", "admin", new Responsable("Daniel")));

    proyectos = new vector<Proyecto *>();
    proyectos->push_back(new Proyecto("Proyecto 1", "Proyecto de prueba 1", "Daniel"));
    
    Tarea *tarea1 = new Tarea("Tarea 1", "2021-12-31", "Pendiente", "Alta", "Comentario 1");
    tarea1->addResponsable(usuarios->begin()[0]->getResponsable());
    usuarios->begin()[0]->getResponsable()->addTarea(tarea1);
    proyectos->begin()[0]->addTarea(tarea1);
    this->usuario = usuarios->begin()[0];
}

BD::~BD()
{
    for (auto usuario : *usuarios)
    {
        delete usuario;
    }
    delete usuarios;

    for (auto proyecto : *proyectos)
    {
        delete proyecto;
    }
    delete proyectos;
}

BD *BD::getInstance()
{
    if (instance == nullptr)
    {
        instance = new BD();
    }
    return instance;
}

vector<Usuario *> *BD::getUsuarios()
{
    return usuarios;
}

Usuario *BD::getUsuario()
{
    return usuario;
}

void BD::setUsuario(Usuario *usuario)
{
    this->usuario = usuario;
}

vector<Proyecto *> *BD::getProyectos()
{
    return proyectos;
}