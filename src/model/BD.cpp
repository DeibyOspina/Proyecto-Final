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

    proyectos = new vector<Proyecto *>();
    proyectos->push_back(new Proyecto("Proyecto 1", "Proyecto de prueba 1", "Daniel"));

    usuarios = new vector<Usuario *>();
    usuarios->push_back(new Usuario("admin", "admin", new Responsable("Daniel")));
    usuarios->push_back(new Usuario("user1", "password1", new Responsable("User 1")));
    usuarios->push_back(new Usuario("user2", "password2", new Responsable("User 2")));
    usuarios->push_back(new Usuario("user3", "password3", new Responsable("User 3")));
    usuarios->push_back(new Usuario("user4", "password4", new Responsable("User 4")));
    usuarios->push_back(new Usuario("user5", "password5", new Responsable("User 5")));

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