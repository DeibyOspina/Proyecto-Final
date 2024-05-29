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
    ResponsableController responsableController;
    NotasView notasView;

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
    void showTarea(list<Tarea *> tareas);
    void menuExportCSV();
    void menuTarea();
    void menuNotas();
    void menuListTarea();
    void showFormTarea();
    void showFormEditarTarea();
    void showMenuEditarTarea();
    void showFormAsignarResponsable(Tarea *tarea);
    void showFormFindTarea();
    void showFormFindTareaResponsable();
    void menuAddNotaTarea(Tarea *tarea);
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

void TareaView::showTarea(list<Tarea *> tareas)
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
            cout << "6. Buscar tarea por nombre " << endl;
            cout << "7. Buscar tarea por responsable" << endl;
            cout << "8. Ver Responsables Ordenados por nombre" << endl;
            cout << "9. Salir. " << endl;
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
                showFormFindTarea();
                break;
            case 7:
                showFormFindTareaResponsable();
                break;
            case 8:
            {
                auto responsables = responsableController.sortResponsables();
                cout << "Responsables: " << endl;
                for (auto responsable : responsables)
                {
                    cout << " " << responsable->getNombre() << endl;
                }
            }
            break;
            case 9:
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
    } while (opcion != 9);
    Utils::clearScreen();
};

void TareaView::menuListTarea()
{
    int opcion = 3;
    bool sort = false;
    do
    {
        cout << "-------------------------------------------------" << endl;
        cout << "1. Mostrar Todas las tareas. " << endl;
        cout << "2. Mostrar tareas ordenadas por prioridad. " << endl;
        cout << "3. Mostrar Tareas Por Responsable. " << endl;
        cout << "4. Salir. " << endl;
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
            for (auto it = tareaController.getProyectos()->begin(); it != tareaController.getProyectos()->end(); it++)
            {
                cout << "Tareas del proyecto: " << (*it)->getNombre() << endl;
                showTarea((*it)->getTareas());
                cout << "-----------------------------------" << endl;
            }
        }
        break;
        case 2:
        {
            for (auto it = tareaController.getProyectos()->begin(); it != tareaController.getProyectos()->end(); it++)
            {
                cout << "Tareas del proyecto  : " << (*it)->getNombre() << " ordenadas de forma " << (sort ? "Ascendente" : "Descendente") << endl;
                showTarea(tareaController.sortTareasByPrioridad((*it)->getTareas(), sort));
                cout << "-----------------------------------" << endl;
            }
        }

        case 3:
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
        case 4:
            break;
        default:
            cout << "Opción inválida" << endl;
            break;
        }

    } while (opcion != 4);
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

void TareaView::menuNotas()
{
    int opcion;
    string nombreProyecto;
    cout << "Ingrese el nombre del proyecto al cual desea buscar la tarea: ";
    getline(cin, nombreProyecto);
    auto proyecto = proyectoController.findProyectoByNombre(nombreProyecto);

    cout << "Ingrese el nombre de la tarea:";
    getline(cin, nombre);
    auto tarea = tareaController.findTareaByNombre(proyecto->getTareas(), nombre);
    if (tarea == nullptr)
    {
        cout << "Tarea no encontrada" << endl;
        return;
    }

    do
    {
        cout << "1. Agregar Nota" << endl;
        cout << "2. Agregar Reaccion" << endl;
        cout << "3. Listar Notas" << endl;
        cout << "4. Salir" << endl;
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
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        Utils::clearScreen();

        switch (opcion)
        {
        case 1:
            menuAddNotaTarea(tarea);
            break;
        case 2:
            notasView.showFormAddReaccion(tarea);
            break;
        case 3:
            notasView.showNotas(tarea->getNotas());
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }
    } while (opcion != 4);
    Utils::clearScreen();
}

void TareaView::showMenuEditarTarea()
{
    int opcion = 3;
    do
    {
        cout << "-------------------------------------------------" << endl;
        cout << "1. Editar Datos . " << endl;
        cout << "2. Notas Tarea " << endl;
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
            showFormEditarTarea();
            break;

        default:
            break;
        }

    } while (opcion != 3);
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
    cout << "Seleccione el nuevo estado de la tarea: ";
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

void TareaView::showFormFindTarea()
{
    string nombreProyecto;
    cout << "Ingrese el nombre del proyecto del cual desea agregar la tarea: ";
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

    auto tarea = tareaController.findTareaByNombre(proyecto->getTareas(), nombre);
    if (tarea == nullptr)
    {
        cout << "Tarea no encontrada" << endl;
        return;
    }
    showTarea(tarea);
    tareaController.setProyecto(nullptr);
}

void TareaView::showFormFindTareaResponsable()
{
    string nombreResponsable;
    cout << "Ingrese el nombre del responsable: ";
    getline(cin, nombreResponsable);

    Responsable *responsable = usuarioController.findResponsableByNombre(nombreResponsable);
    if (responsable == nullptr)
    {
        cout << "Responsable no encontrado" << endl;
        return;
    }

    auto tarea = tareaController.findTareaByNombre(responsable->getTareas(), nombre);
    if (tarea == nullptr)
    {
        cout << "Tarea no encontrada" << endl;
        return;
    }
    showTarea(tarea);
}
