#pragma once
#include <algorithm>
#include <queue>
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
    queue<Responsable *> *sortResponsables();
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

queue<Responsable *> *ResponsableController::sortResponsables()
{
    queue<Responsable *> *responsables = new queue<Responsable *>();
    auto usuarios = bd->getUsuarios();
    sort(usuarios->begin(), usuarios->end(), [](Usuario *a, Usuario *b)
         { return a->getResponsable()->getNombre() < b->getResponsable()->getNombre(); });
    for (auto usuario : *usuarios)
    {
        responsables->push(usuario->getResponsable());
    }
    return responsables;
}