#pragma once
#include <iostream>
#include <vector>
#include "./Usuario.cpp"

using namespace std;

class BD
{
private:
    static BD *instance;
    BD(){};

    vector<Usuario *> *usuarios = new vector<Usuario *>();
    Usuario *usuario;

public:
    // No copiable
    BD(BD &bd) = delete;

    // No asignable
    void operator=(const BD &) = delete;

    // Obtener instancia
    static BD *getInstance()
    {
        if (instance == nullptr)
        {
            instance = new BD();
        }
        return instance;
    };

    vector<Usuario *>* getUsuarios()
    {
        return this->usuarios;
    };

    Usuario *getUsuario()
    {
        return this->usuario;
    };

    void setUsuario(Usuario *usuario)
    {
        this->usuario = usuario;
    };
};

BD *BD::instance = nullptr;