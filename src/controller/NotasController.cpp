#include <iostream>

#include "../model/BD.cpp"
using namespace std;

class NotasController
{
private:
    BD *bd;
    Tarea *tarea;
    Proyecto *proyecto;

public:
    NotasController();
    void setTarea(Tarea *tarea);
    void setProyecto(Proyecto *proyecto);

    Tarea *addNotaTarea(string titulo, string descripcion);
    Proyecto *addNotaProyecto(string titulo, string descripcion);
};

NotasController::NotasController()
{
}

void NotasController::setTarea(Tarea *tarea)
{
    this->tarea = tarea;
}

void NotasController::setProyecto(Proyecto *proyecto)
{
    this->proyecto = proyecto;
}

Tarea *NotasController::addNotaTarea(string titulo, string descripcion)
{
    if (tarea == nullptr)
    {
        throw invalid_argument("No ha selecionado ninguna tarea.");
    }
    Nota *nota = new Nota(titulo, descripcion, bd->getUsuario());
    tarea->addNota(nota);
    return tarea;
}

Proyecto *NotasController::addNotaProyecto(string titulo, string descripcion)
{
    if (proyecto == nullptr)
    {
        throw invalid_argument("No ha selecionado ningun proyecto.");
    }
    Nota *nota = new Nota(titulo, descripcion, bd->getUsuario());
    proyecto->addNota(nota);
    return proyecto;
}
