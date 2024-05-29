#pragma once

#include <iostream>
#include <iomanip>

#include "../utils/utils.cpp"
#include "../model/Tarea.cpp"
#include "./UsuarioView.cpp"
#include "../controller/TareaController.cpp"

using namespace std;

class TareaView
{
private:
    TareaController tareaController;
    UsuarioController usuarioController;
    ProyectoController proyectoController;

    string nombre;
    string fechaLimite;
    string estado;
    string prioridad;
    string comentario;

public:
    TareaView();

    void menuUploadCSV();
    void showTarea(Tarea *tarea);
    void showTarea(set<Tarea *> tareas);
    void menuExportCSV();
    void menuTarea();
    void menuNotas();
    void menuListTarea();
    void showFormTarea();
    void showFormEditarTarea();
    void showFormAsignarResponsable(Tarea *tarea);
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

    string responsables = "";
    for (auto it = tarea->getResponsables()->begin(); it != tarea->getResponsables()->end(); it++)
    {
        responsables += "- " + (*it)->getNombre() + "\n ";
    }

    cout << setw(15) << left << "Nombre"
         << setw(15) << left << "Fecha Limite"
         << setw(15) << left << "Responsable"
         << setw(15) << left << "Estado"
         << setw(15) << left << "Prioridad"
         << setw(15) << left << "Comentario" << endl;

    cout << setw(15) << left << tarea->getNombre()
         << setw(15) << left << tarea->getFechaLimite()
         << setw(15) << left << responsables
         << setw(15) << left << tarea->getEstado()
         << setw(15) << left << tarea->getPrioridad()
         << setw(15) << left << tarea->getComentario() << endl;
}

void TareaView::showTarea(set<Tarea *> tareas)
{
    cout << setw(15) << left << "Nombre"
         << setw(15) << left << "Fecha Limite"
         << setw(15) << left << "Responsable"
         << setw(15) << left << "Estado"
         << setw(15) << left << "Prioridad"
         << setw(15) << left << "Comentario" << endl;

    for (auto tarea : tareas)
    {
        string responsables = "";
        for (auto it = tarea->getResponsables()->begin(); it != tarea->getResponsables()->end(); it++)
        {
            responsables += "- " + (*it)->getNombre() + "\n ";
        }
        cout << setw(15) << left << tarea->getNombre()
             << setw(15) << left << tarea->getFechaLimite()
             << setw(15) << left << responsables
             << setw(15) << left << tarea->getEstado()
             << setw(15) << left << tarea->getPrioridad()
             << setw(15) << left << tarea->getComentario() << endl;
    }
}

void TareaView::menuTarea()
{
    Utils::clearScreen();
    int opcion = 6;
    do
    {
        try
        {
            cout << "-------------------------------------------------" << endl;
            cout << "1. Mostrar tareas. " << endl;
            cout << "2. Crear Tarea. " << endl;
            cout << "3. Editar Tareas. " << endl;
            cout << "4. Crear Tareas Con CSV. " << endl;
            cout << "5. Exportar mis Tareas a CSV. " << endl;
            cout << "6. Salir. " << endl;
            cout << "Ingrese una opción: ";
            cin >> opcion;

            cin.ignore();
            Utils::clearScreen();
            switch (opcion)
            {
            case 1:
                menuListTarea();
                break;
            case 2:
                showFormTarea();
                break;
            case 3:
                showFormEditarTarea();
                break;
            case 4:
                menuUploadCSV();
                break;
            case 5:
                menuExportCSV();
                break;
            case 6:
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
    Utils::clearScreen();
};

void TareaView::menuListTarea()
{
    int opcion = 3;
    do
    {
        cout << "-------------------------------------------------" << endl;
        cout << "1. Mostrar Todas las tareas. " << endl;
        cout << "2. Mostrar Tareas Por Responsable. " << endl;
        cout << "3. Salir. " << endl;
        do
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
            }
            cout << "Ingrese una opción: ";
            cin >> opcion;
        } while (cin.fail());
        Utils::clearScreen();

        cin.ignore();
        switch (opcion)
        {
        case 1:
        {
            auto usuarios = usuarioController.getUsuarios();
            for (auto it = usuarios->begin(); it != usuarios->end(); it++)
            {
                Usuario *usuario = *it;
                if (!usuario->getResponsable()->getTareas().empty())
                {
                    showTarea(usuario->getResponsable()->getTareas());
                }
            }
        }
        break;
        case 2:
        {
            string nombreResponsable;
            cout << "Ingrese el nombre del responsable: ";
            getline(cin, nombreResponsable);
            Responsable *responsable = usuarioController.findResponsableByNombre(nombreResponsable);
            if (responsable)
            {
                showTarea(responsable->getTareas());
            }
            else
            {
                cout << "Responsable no encontrado" << endl;
            }
        }
        break;
        case 3:
            break;
        default:
            cout << "Opción inválida" << endl;
            break;
        }

    } while (opcion != 3);
    Utils::clearScreen();
}

void TareaView::showFormTarea()
{
    string nombreProyecto;
    cout << "Ingrese el nombre del proyecto al cual desea agregar la tarea: ";
    getline(cin, nombreProyecto);
    auto proyecto = proyectoController.findProyectoByNombre(nombreProyecto);

    if (proyecto == nullptr)
    {
        cout << "Proyecto no encontrado" << endl;
        return;
    }

    tareaController.setProyecto(proyecto);
    cout << "Ingrese el nombre de la tarea: ";
    getline(cin, nombre);

    while (!Utils::isDate(fechaLimite))
    {
        cout << "Ingrese la fecha límite de la tarea: ";
        getline(cin, fechaLimite);
    }

    int index = 0;
    EstadosTarea::showEstados();
    while (estado.empty())
    {
        cout << "Seleccione el estado de la tarea: ";
        cin >> index;
        estado = EstadosTarea::selectEstado(index);
    }

    index = 0;
    PrioridadesTarea::showPrioridades();
    while (prioridad.empty())
    {
        cout << "Seleccione la prioridad de la tarea: ";
        cin >> index;
        prioridad = PrioridadesTarea::selectPrioridad(index);
    }

    cin.ignore();
    cout << "Ingrese algún comentario para la tarea: ";
    getline(cin, comentario);

    auto tarea = tareaController.crearTarea(nombre, fechaLimite, estado, prioridad, comentario);
    showFormAsignarResponsable(tarea);

    cout << "Tarea creada exitosamente" << endl;
    showTarea(tarea);

    tareaController.setProyecto(nullptr);
}

void TareaView::showFormEditarTarea()
{
    string nuevoNombre, nombreResponsable;
    cout << "Ingrese el nombre del responsable de la tarea a editar: ";
    getline(cin, nombreResponsable);

    Responsable *responsable = usuarioController.findResponsableByNombre(nombreResponsable);
    if (responsable == nullptr)
    {
        cout << "Responsable no encontrado" << endl;
        return;
    }

    cout << "Ingrese el nombre de la tarea a editar: ";
    getline(cin, nombre);

    Tarea *tarea = tareaController.findTareaByNombre(responsable->getTareas(), nombre);
    if (tarea == nullptr)
    {
        cout << "Tarea no encontrada" << endl;
        return;
    }

    cout << "Ingrese el nuevo nombre de la tarea: ";
    getline(cin, nuevoNombre);

    cout << "Ingrese la nueva fecha límite de la tarea: ";

    while (!Utils::isDate(fechaLimite))
    {
        cout << "Ingrese la fecha límite de la tarea: ";
        getline(cin, fechaLimite);
    }

    int index = 0;
    cout << "Seleccione el estado de la tarea: ";
    EstadosTarea::showEstados();
    while (estado.empty())
    {
        cin >> index;
        estado = EstadosTarea::selectEstado(index);
    }

    index = 0;
    cout << "Seleccione la prioridad de la tarea: ";
    PrioridadesTarea::showPrioridades();
    while (prioridad.empty())
    {
        cin >> index;
        prioridad = PrioridadesTarea::selectPrioridad(index);
    }

    cout << "Ingrese un nuevo comentario para la tarea: ";
    getline(cin, comentario);

    tareaController.editarTarea(tarea, nuevoNombre, fechaLimite, estado, prioridad, comentario);
}

void TareaView::showFormAsignarResponsable(Tarea *tarea)
{
    cout << "------------- Asigne responsables a la tarea --------------" << endl;
    auto usuarios = usuarioController.getUsuarios();
    for (auto it = usuarios->begin(); it != usuarios->end(); it++)
    {
        cout << "--------- " << (*it)->getResponsable()->getNombre() << endl;
    }

    int opcion = 0;
    do
    {
        cout << "1. Agregar responsable a la tarea " << endl;
        cout << "2. Salir " << endl;
        do
        {
            if (cin.fail())
            {
                cin.clear();
                cin.ignore();
            }
            cout << "Ingrese una opción: ";
            cin >> opcion;
        } while (cin.fail());

        if (opcion == 1)
        {
            cin.ignore();
            string nombreResponsable;
            cout << "Ingrese el nombre del responsable: ";
            getline(cin, nombreResponsable);

            Responsable *responsable = usuarioController.findResponsableByNombre(nombreResponsable);
            if (responsable)
            {
                tarea->addResponsable(responsable);
            }
            else
            {
                cout << "Responsable no encontrado" << endl;
            }
        }
        else if (opcion != 2)
        {
            cout << "Opción inválida" << endl;
        }
    } while (opcion != 2 || tarea->getResponsables()->empty());
}
