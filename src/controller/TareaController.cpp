#pragma once

#include <iostream>
#include <set>
#include "../model/BD.cpp"
#include "../model/Tarea.cpp"
#include "../Utils/Utils.cpp"
#include "./FilesController.cpp"
#include "./ResponsableController.cpp"

using namespace std;

class TareaController
{
private:
    BD *bd;

public:
    TareaController();
    set<Tarea *> createTareaToCSV(string pathCSV);
    bool validHeader(vector<string> header);
    void exportTareasToCSV(set<Tarea *> tareas, string pathCSV);
};
TareaController::TareaController()
{
    bd = BD::getInstance();
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
        vector<string> row = {tarea->getNombre(), tarea->getResponsable()->getNombre(), tarea->getFechaLimite(), tarea->getEstado(), tarea->getPrioridad(), tarea->getComentario()};
        data.push_back(row); });
    fileController.writeCSV(data, '\n', ";");
}