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
            cout << "1. Mostrar tareas. " << endl;
            cout << "2. Crear Tarea. " << endl;
            cout << "3. Crear Tareas Con CSV. " << endl;
            cout << "4. Editar Tareas. " << endl;
            cout << "5. Exportar mis Tareas a CSV. " << endl;
            cout << "6. Salir. " << endl;
             cout << "Ingrese una opción: ";
            cout << "-------------------------------------------------" << endl;
            cin >> opcion;
            cin.ignore(); 

            Utils::clearScreen();

            switch (opcion)
            {
            case 1:
            {
                int option;
                cout << "-------------------------------------------------" << endl;
                cout << "1. Mostrar Todas las tareas. " << endl;
                cout << "2. Mostrar Tareas Por Responsable. " << endl;
                cout << "3. Salir. " << endl;
                cout << "Ingrese una opción: " << endl;
                cout << "--------------------------------------------------" << endl;
                cin >> option;
                cin.ignore();
                if (option == 1)
                {
                    set<Tarea *> tareas = usuarioController.getLoggedUser()->getResponsable()->getTareas();
                    showTarea(tareas);
                }
                else if (option == 2)
                {
                    string nombreResponsable;
                    cout << "Ingrese el nombre del responsable: ";
                    getline(cin, nombreResponsable);
                    Responsable *responsable = usuarioController.getResponsable(nombreResponsable);
                    if (responsable)
                    {
                        showTarea(responsable->getTareas());
                    }
                    else
                    {
                        cout << "Responsable no encontrado" << endl;
                    }
                }
                else if (option == 3)
                {
                    cout << "Saliendo..." << endl;
                }
                else
                {
                    cout << "Opción inválida" << endl;
                }
                break;
            }
            case 2:
            {
                string nombre, fechaLimite, estado, prioridad, comentario;
                cout << "--------------------------------------------------" << endl;
                cout << "Ingrese el nombre de la tarea: ";
                cout << "--------------------------------------------------" << endl;
                getline(cin, nombre);

                cout << "Ingrese la fecha límite de la tarea: ";
                getline(cin, fechaLimite);

                cout << "Ingrese el estado de la tarea: ";
                getline(cin, estado);

                cout << "Ingrese la prioridad de la tarea: ";
                getline(cin, prioridad);

                cout << "Ingrese algún comentario para la tarea: ";
                getline(cin, comentario);

                tareaController.crearTarea(nombre, fechaLimite, estado, prioridad, comentario);
                break;
            }
            case 3:
                menuUploadCSV();
                break;
            case 4:
            {
                string nombre, nuevoNombre, fechaLimite, estado, prioridad, comentario;
                cout << "--------------------------------------------------" << endl;
                cout << "Ingrese el nombre de la tarea a editar: ";
                cout << "--------------------------------------------------" << endl;
                getline(cin, nombre);

                Tarea *tarea = tareaController.findTareaByNombre(nombre);
                if (tarea == nullptr)
                {
                    cout << "Tarea no encontrada" << endl;
                    break;
                }

                cout << "Ingrese el nuevo nombre de la tarea: ";
                getline(cin, nuevoNombre);

                cout << "Ingrese la nueva fecha límite de la tarea: ";
                getline(cin, fechaLimite);

                cout << "Ingrese el nuevo estado de la tarea: ";
                getline(cin, estado);

                cout << "Ingrese la nueva prioridad de la tarea: ";
                getline(cin, prioridad);

                cout << "Ingrese un nuevo comentario para la tarea: ";
                getline(cin, comentario);

                tareaController.editarTarea(tarea, nuevoNombre, fechaLimite, estado, prioridad, comentario);
                break;
            }
            case 5:
                menuExportCSV();
                break;
            case 6:
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
    } while (opcion != 6);
};
