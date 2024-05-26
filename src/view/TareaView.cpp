#pragma once

#include <iostream>
#include <iomanip>

#include "../utils/utils.cpp"
#include "../model/Tarea.cpp"
#include "../controller/TareaController.cpp"
#include "../controller/UsuarioController.cpp"
using namespace std;

class TareaView
{
private:
    TareaController tareaController;
    UsuarioController usuarioController;

public:
    TareaView();

    void menuUploadCSV();
    void showTarea(Tarea *tarea);
    void showTarea(set<Tarea *> tareas);
    void menuExportCSV();
    void menuTarea();
    void menuNotas();
};
TareaView::TareaView() {}

void TareaView::menuUploadCSV()
{
    do
    {
        string path;
        cout << "Ingrese la ruta del archivo CSV: ";
        cin >> path;
        Utils::clearScreen();
        cout << "Cargando tareas.." << endl;
        try
        {
            auto tareas = tareaController.createTareaToCSV(path);
            cout << "Tareas cargadas exitosamente" << endl;
            showTarea(tareas);
            break;
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    } while (true);
}

void TareaView::menuExportCSV()
{
    do
    {
        string path;
        cout << "Ingrese la ruta en la cual desea guardar el archivo: ";
        cin >> path;
        Utils::clearScreen();
        cout << "Exportando tareas.." << endl;
        try
        {
            tareaController.exportTareasToCSV(usuarioController.getLoggedUser()->getResponsable()->getTareas(), path);
            cout << "Tareas exportadas exitosamente" << endl;
            break;
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    } while (true);
}

void TareaView::showTarea(Tarea *tarea)
{
    cout << setw(15) << left << "Nombre"
         << setw(15) << left << "Fecha Limite"
         //<< setw(15) << left << "Responsable"
         << setw(15) << left << "Estado"
         << setw(15) << left << "Prioridad"
         << setw(15) << left << "Comentario" << endl;

    cout << setw(15) << left << tarea->getNombre()
         << setw(15) << left << tarea->getFechaLimite()
         //<< setw(15) << left << tarea->getResponsable
         << setw(15) << left << tarea->getEstado()
         << setw(15) << left << tarea->getPrioridad()
         << setw(15) << left << tarea->getComentario() << endl;
}

void TareaView::showTarea(set<Tarea *> tareas)
{
    cout << setw(15) << left << "Nombre"
         << setw(15) << left << "Fecha Limite"
         //<< setw(15) << left << "Responsable"
         << setw(15) << left << "Estado"
         << setw(15) << left << "Prioridad"
         << setw(15) << left << "Comentario" << endl;

    for (auto tarea : tareas)
    {
        cout << setw(15) << left << tarea->getNombre()
             << setw(15) << left << tarea->getFechaLimite()
             //<< setw(15) << left << tarea->getResponsable()->getNombre()
             << setw(15) << left << tarea->getEstado()
             << setw(15) << left << tarea->getPrioridad()
             << setw(15) << left << tarea->getComentario() << endl;
    }
}



void TareaView::menuTarea()
{
    int opcion = 0;
    do
    {
        try
        {

            cout << "-------------------------------------------------" << endl;
            cout << "1. Crear Tareas Con CSV" << endl;
            cout << "2. Exportar mis Tareas a CSV" << endl;
            cout << "3. Salir" << endl;
            cout << "-------------------------------------------------" << endl;

            cout << "Ingrese una opción: ";
            cin >> opcion;

            Utils::clearScreen();

            switch (opcion)
            {
            case 1:
                menuUploadCSV();
                break;
            case 2:
                menuExportCSV();
                break;
            case 3:
                cout << "Saliendo.." << endl;
                break;
            default:
                cout << "Opción inválida" << endl;
                break;
            }
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    } while (opcion != 3);
};