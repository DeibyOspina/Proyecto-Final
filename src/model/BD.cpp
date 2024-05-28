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
    vector<Proyecto *>* proyectos;
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
    usuario = nullptr;
    proyectos = new vector<Proyecto *>();
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