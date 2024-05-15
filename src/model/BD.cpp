#pragma once
#include <iostream>
#include <vector>
#include "./Usuario.cpp"

using namespace std;

class BD
{
private:
    static BD *instance;
    vector<Usuario *> *usuarios;
    Usuario *usuario;

    BD();

public:
    // No copiable
    BD(BD &bd) = delete;

    // No asignable
    void operator = (const BD &) = delete;

    // Obtener instancia
    static BD *getInstance();

    vector<Usuario *> *getUsuarios();
    Usuario *getUsuario();
    void setUsuario(Usuario *usuario);
};

BD *BD::instance = nullptr;

BD::BD()
{
    usuarios = new vector<Usuario *>();
    usuarios->push_back(new Usuario("admin", "admin", new Responsable("Daniel")));
    usuario = nullptr;
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