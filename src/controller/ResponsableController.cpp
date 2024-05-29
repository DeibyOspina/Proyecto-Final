#pragma once
#include <algorithm>
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
    vector<Responsable *> sortResponsables(bool asc = true);
};

ResponsableController::ResponsableController()
{
    bd = BD::getInstance();
}

Responsable *ResponsableController::findByNombre(string nombre)
{
    auto usuarios = bd->getUsuarios();
    auto it = find_if(usuarios->begin(), usuarios->end(), [nombre](Usuario *usuario)
                      { return usuario->getResponsable()->getNombre() == nombre; });
    return it != usuarios->end() ? (*it)->getResponsable() : nullptr;
}

vector<Responsable *> ResponsableController::sortResponsables(bool asc)
{
    vector<Responsable *> responsables;
    auto usuarios = bd->getUsuarios();
    sort(usuarios->begin(), usuarios->end(), [asc](Usuario *a, Usuario *b)
         { return asc ? a->getResponsable()->getNombre() < b->getResponsable()->getNombre()
                      : a->getResponsable()->getNombre() > b->getResponsable()->getNombre(); });
                      
    for (auto usuario : *usuarios)
    {
        responsables.push_back(usuario->getResponsable());
    }
    return responsables;
}