#include <iostream>
#include <algorithm>

#include "../utils/EstadosProyecto.cpp"
#include "../model/BD.cpp"
#include "../utils/Utils.cpp"
using namespace std;

class ProyectoController
{
private:
    BD *bd;

public:
    ProyectoController();
    bool createProyecto(string nombre, string descripcion, string propietario);
    bool editProyecto(Proyecto *proyecto, string descripcion, string propietario);
    vector<Proyecto *> *listProyectos();
    Proyecto *findProyectoByNombre(string nombre);
    vector<Proyecto *> *sortProyectosByFecha(bool asc = true);
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
    proyecto->setEstado(EstadosProyecto::NOT_STARTED);
    proyecto->setFecha(Utils::getCurrentDate());
    bd->getProyectos()->push_back(proyecto);
    return true;
}

bool ProyectoController::editProyecto(Proyecto *proyecto, string descripcion, string propietario)
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

vector<Proyecto *> *ProyectoController::listProyectos()
{
    return bd->getProyectos();
}

vector<Proyecto *> *ProyectoController::sortProyectosByFecha(bool asc)
{
    // Se crea una copia del set para no alterar el set original
    vector<Proyecto *> *proyectosTmp = bd->getProyectos();
    sort(proyectosTmp->begin(), proyectosTmp->end(), [asc](Proyecto *a, Proyecto *b) mutable
         { return asc ? a->getFecha() < b->getFecha() : a->getFecha() > b->getFecha(); });
    return proyectosTmp;
}
