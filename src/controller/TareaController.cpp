#pragma once

#include <iostream>
#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>
#include <set>

#include "../model/BD.cpp"
#include "../model/Tarea.cpp"
#include "../utils/utils.cpp"
#include "../utils/EstadosTarea.cpp"
#include "../utils/PrioridadesTarea.cpp"
#include "./FilesController.cpp"
#include "./ResponsableController.cpp"

using namespace std;

class TareaController
{
private:
    BD *bd;
    Proyecto *proyecto;

public:
    TareaController();
    set<Tarea *> createTareaToCSV(string pathCSV);
    void exportTareasToCSV(set<Tarea *> tareas, string pathCSV);
    bool validHeader(vector<string> header);

    Tarea *findTareaByNombre(set<Tarea *> tareas, string nombre);
    Tarea *findTareaByNombre(list<Tarea *> tareas, string nombre);
    Tarea *findTareaByNombre(string nombre);

    Tarea *crearTarea(string nombre, string fechaLimite, string estado, string prioridad, string comentario);
    void editarTarea(Tarea *tarea, string nombre, string fechaLimite, string estado, string prioridad, string comentario);

    void setProyecto(Proyecto *proyecto);
    vector<Proyecto *> *getProyectos();

    set<Tarea *> sortTareasByPrioridad(set<Tarea *> tareas, bool asc);
    list<Tarea *> sortTareasByPrioridad(list<Tarea *> tareas, bool asc);

    list<Tarea *> createRecurrentTareas(Tarea *tarea, int periodicidadDias, string fechaLimite);
};

TareaController::TareaController()
{
    bd = BD::getInstance();
}

void TareaController::setProyecto(Proyecto *proyecto)
{
    this->proyecto = proyecto;
}

set<Tarea *> TareaController::createTareaToCSV(string pathCSV)
{
    FilesController fileController(pathCSV);
    ResponsableController responsableController;

    vector<vector<string>> data = fileController.readCSV('\n', ";");
    set<Tarea *> tareas;

    validHeader(data[0]);
    data.erase(data.begin());

    for (vector<string> row : data)
    {
        string nombreResponsable = row[1];
        Responsable *responsable = responsableController.findByNombre(nombreResponsable);
        if (responsable != nullptr && row.size() <= 7)
        {
            Tarea *tarea = new Tarea(row[0], row[2], responsable, row[3], row[4], row[5]);
            tareas.insert(tarea);
            responsable->addTarea(tarea);
        }
        else
        {
            throw invalid_argument("Verifique que todos los datos de la tarea sean correctos y que el responsable exista.");
        }
    }
    return tareas;
}

bool TareaController::validHeader(vector<string> header)
{
    if (Utils::toLowerCase(header[0]) != "nombre")
    {
        throw invalid_argument("El encabezado del archivo en la columna 1 debe ser 'nombre'");
    }
    if (Utils::toLowerCase(header[1]) != "responsable")
    {
        throw invalid_argument("El encabezado del archivo en la columna 2 debe ser 'responsable'");
    }
    if (Utils::toLowerCase(header[2]) != "fecha limite")
    {
        throw invalid_argument("El encabezado del archivo en la columna 3 debe ser 'fecha limite'");
    }
    if (Utils::toLowerCase(header[3]) != "estado")
    {
        throw invalid_argument("El encabezado del archivo en la columna 4 debe ser 'estado'");
    }
    if (Utils::toLowerCase(header[4]) != "prioridad")
    {
        throw invalid_argument("El encabezado del archivo en la columna 5 debe ser 'prioridad'");
    }
    if (Utils::toLowerCase(header[5]) != "comentario")
    {
        throw invalid_argument("El encabezado del archivo en la columna 6 debe ser 'comentario'");
    }
    return true;
}

void TareaController::exportTareasToCSV(set<Tarea *> tareas, string pathCSV)
{
    FilesController fileController(pathCSV + "/tareas.csv", true);
    vector<vector<string>> data;
    vector<string> header = {"Nombre", "Responsable", "Fecha Limite", "Estado", "Prioridad", "Comentario"};
    data.push_back(header);
    for_each(tareas.begin(), tareas.end(), [&data](Tarea *tarea)
             {
        auto it = *tarea->getResponsables()->begin();
        vector<string> row = {tarea->getNombre(), it->getNombre() , 
        tarea->getFechaLimite(), tarea->getEstado(), tarea->getPrioridad(), tarea->getComentario()};
        data.push_back(row); });
    fileController.writeCSV(data, '\n', ";");
}

Tarea *TareaController::findTareaByNombre(set<Tarea *> tareas, string nombre)
{
    auto it = find_if(tareas.begin(), tareas.end(), [nombre](Tarea *tarea)
                      { return tarea->getNombre() == nombre; });
    return it != tareas.end() ? *it : nullptr;
}

Tarea *TareaController::findTareaByNombre(list<Tarea *> tareas, string nombre)
{
    auto it = find_if(tareas.begin(), tareas.end(), [nombre](Tarea *tarea)
                      { return tarea->getNombre() == nombre; });
    return it != tareas.end() ? *it : nullptr;
}

Tarea *TareaController::findTareaByNombre(string nombre)
{
    set<Tarea *> tareas = bd->getUsuario()->getResponsable()->getTareas();
    return findTareaByNombre(tareas, nombre);
}

Tarea *TareaController::crearTarea(string nombre, string fechaLimite, string estado, string prioridad, string comentario)
{
    if (proyecto == nullptr)
    {
        throw invalid_argument("No ha seleccionado ningún proyecto.");
    }
    Tarea *tarea = new Tarea(nombre, fechaLimite, estado, prioridad, comentario);
    proyecto->addTarea(tarea);
    return tarea;
}

void TareaController::editarTarea(Tarea *tarea, string nombre, string fechaLimite, string estado, string prioridad, string comentario)
{
    if (tarea == nullptr)
    {
        throw invalid_argument("La tarea no existe.");
    }

    tarea->setNombre(nombre);
    tarea->setFechaLimite(fechaLimite);
    tarea->setEstado(estado);
    tarea->setPrioridad(prioridad);
    tarea->setComentario(comentario);

    cout << "La tarea ha sido editada exitosamente." << endl;
}

vector<Proyecto *> *TareaController::getProyectos()
{
    return bd->getProyectos();
}

set<Tarea *> TareaController::sortTareasByPrioridad(set<Tarea *> tareas, bool asc)
{
    sort(tareas.begin(), tareas.end(), [asc](Tarea *t1, Tarea *t2)
         { return asc ? t1->getPrioridad() < t2->getPrioridad() : t1->getPrioridad() > t2->getPrioridad(); });
    return tareas;
}

list<Tarea *> TareaController::sortTareasByPrioridad(list<Tarea *> tareas, bool asc)
{
    sort(tareas.begin(), tareas.end(), [asc](Tarea *t1, Tarea *t2)
         { return asc ? t1->getPrioridad() < t2->getPrioridad() : t1->getPrioridad() > t2->getPrioridad(); });
    return tareas;
}

list<Tarea *> TareaController::createRecurrentTareas(Tarea *tarea, int periodicidadDias, string fechaLimiteStr)
{
    list<Tarea *> tareasRecurrentes;
    int periodicidad = periodicidadDias * Utils::SEGUNDOS_POR_DIA;
    time_t fechaInicio = time(nullptr) + periodicidad;
    time_t fechaLimite = Utils::parseDate(fechaLimiteStr);

    while (fechaInicio < fechaLimite)
    {
        Tarea *tarea = new Tarea(tarea->getNombre(), Utils::parseDate(fechaInicio),
                                 EstadosTarea::NOT_STARTED, tarea->getPrioridad(),
                                 tarea->getComentario());
        tarea->setResponsables(tarea->getResponsables());
        tareasRecurrentes.push_back(tarea);
        fechaInicio += periodicidad;
    }
    return tareasRecurrentes;
}
