#pragma once
#include <algorithm>
#include <vector>
#include <iostream>

#include "../model/Usuario.cpp"
#include "../model/BD.cpp"
using namespace std;

class ResponsableController
{
private:
    BD *bd;

public:
    ResponsableController();
    Responsable *findByNombre(string nombre);
};

ResponsableController::ResponsableController()
{
    bd = BD::getInstance();
}

Responsable *ResponsableController::findByNombre(string nombre)
{
    vector<Usuario *> *usuarios = bd->getUsuarios();
    auto it = find_if(usuarios->begin(), usuarios->end(), [nombre](Usuario *usuario)
                      { return usuario->getResponsable()->getNombre() == nombre; });
    return it != usuarios->end() ? (*it)->getResponsable() : nullptr;
}