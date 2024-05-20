#include <iostream>
#include <algorithm>

#include "../model/BD.cpp"
using namespace std;

class ProyectoController
{
private:
    BD *bd;

public:
    ProyectoController();
    bool createProyecto(string nombre, string descripcion, string propietario);
    bool editProyecto(Proyecto* proyecto, string descripcion, string propietario);
    set<Proyecto *>* listProyectos();
    Proyecto *findProyectoByNombre(string nombre);
};

ProyectoController::ProyectoController()
{
    bd = BD::getInstance();
}

bool ProyectoController::createProyecto(string nombre, string descripcion, string propietario)
{
    if (findProyectoByNombre(nombre))
    {
        throw invalid_argument("El proyecto ya existe.");
    }
    Proyecto *proyecto = new Proyecto(nombre, descripcion, propietario);
    bd->getProyectos()->insert(proyecto);
    return true;
}

bool ProyectoController::editProyecto(Proyecto* proyecto, string descripcion, string propietario)
{
    if (proyecto != nullptr)
    {
        proyecto->setDescripcion(descripcion);
        proyecto->setPropietario(propietario);
        return true;
    }
    else
    {
        throw invalid_argument("El proyecto no existe.");
        return false;
    }
}

Proyecto *ProyectoController::findProyectoByNombre(string nombre)
{
    auto it = find_if(bd->getProyectos()->begin(), bd->getProyectos()->end(), [nombre](Proyecto *proyecto)
                      { return proyecto->getNombre() == nombre; });
    return it != bd->getProyectos()->end() ? *it : nullptr;
}

set<Proyecto *>* ProyectoController::listProyectos()
{
    return bd->getProyectos();
}
