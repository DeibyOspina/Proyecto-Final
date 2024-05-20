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
    set<Proyecto *>* proyectos;
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

    set<Proyecto *> *getProyectos();
};

BD *BD::instance = nullptr;

BD::BD()
{
    usuarios = new vector<Usuario *>();
    usuarios->push_back(new Usuario("admin", "admin", new Responsable("Daniel")));
    usuario = nullptr;
    proyectos = new set<Proyecto *>();
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

set<Proyecto *> *BD::getProyectos()
{
    return proyectos;
}