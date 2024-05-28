#include <iostream>
#include <iomanip>
#include <string>
#include "../utils/utils.cpp"
#include "./NotasView.cpp"
#include "../controller/ProyectoController.cpp"
using namespace std;

class ProyectoView
{
private:
    NotasView notasView;
    ProyectoController proyectoController;
    string nombre;
    string descripcion;
    string propietario;
    string estado;

public:
    ProyectoView();
    void showMenuProyecto();
    void showCreateProyecto();
    void showEditProyecto();
    void showMenuListProyecto();
    void showProyectos(vector<Proyecto *> *proyectos);
    void menuAddNotaProyecto();
};

ProyectoView::ProyectoView()
{
}

void ProyectoView::showMenuProyecto()
{
    int opcion;
    Utils::clearScreen();
    do
    {
        cout << "--------------------------" << endl;
        cout << "1. Crear Proyecto" << endl;
        cout << "2. Editar Proyecto" << endl;
        cout << "3. Listar Proyectos" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        Utils::clearScreen();

        switch (opcion)
        {
        case 1:
            showCreateProyecto();
            break;
        case 2:
            showEditProyecto();
            break;
        case 3:
            showMenuListProyecto();
            break;
        case 4:
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }
    } while (opcion != 4);
    Utils::clearScreen();
}

void ProyectoView::showCreateProyecto()
{
    do
    {
        try
        {
            cin.ignore();
            cout << "------- Crear Proyecto ---------" << endl;
            cout << "Nombre: ";
            getline(cin, nombre);

            cout << "Descripcion: ";
            getline(cin, descripcion);

            cout << "Propietario: ";
            getline(cin, propietario);

            if (proyectoController.createProyecto(nombre, descripcion, propietario))
            {
                cout << "Proyecto creado" << endl;
                break;
            }
        }
        catch (const exception &e)
        {
            cerr << e.what() << '\n';
        }
    } while (true);
    Utils::clearScreen();
}

void ProyectoView::showEditProyecto()
{
    cout << "------- Proyectos Disponibles ---------" << endl;
    showProyectos(proyectoController.listProyectos());

    cin.ignore();
    cout << "Seleccione un proyecto: ";
    getline(cin, nombre);

    auto proyecto = proyectoController.findProyectoByNombre(nombre);
    if (proyecto == nullptr)
    {
        cout << "Proyecto no encontrado" << endl;
        return;
    }

    int opcion = 0;
    do
    {
        cout << "----- Proyecto seleccionado: " << proyecto->getNombre() << endl;
        cout << "1. Cambiar Estado Proyecto " << endl;
        cout << "2. Editar Datos Proyecto" << endl;
        cout << "3. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        Utils::clearScreen();

        switch (opcion)
        {
        case 1:
            EstadosProyecto::showEstados();
            cout << "Seleccione un estado: ";
            cin >> opcion;
            estado = EstadosProyecto::selectEstado(opcion);
            if (estado.empty())
            {
                cout << "Estado no valido" << endl;
                break;
            }
            proyecto->setEstado(estado);
            cout << "Estado cambiado" << endl;
            break;
        case 2:
            try
            {
                cout << "------- Editar Datos Proyecto ---------" << endl;
                cout << "Descripcion: ";
                descripcion = Utils::getLine(descripcion);

                cout << "Propietario: ";
                propietario = Utils::getLine(propietario);

                if (proyectoController.editProyecto(proyecto, descripcion, propietario))
                {
                    cout << "Proyecto editado" << endl;
                    break;
                }
            }
            catch (const exception &e)
            {
                opcion = 2;
                cerr << e.what() << '\n';
            }
            break;

        default:
            cout << "Opcion no valida" << endl;
            break;
        }

    } while (opcion != 3);
    Utils::clearScreen();
}

void ProyectoView::showProyectos(vector<Proyecto *> *proyectos)
{
    cout << setw(15) << left << "Nombre"
         << setw(15) << left << "Propietario"
         << setw(30) << left << "Fecha Creacion"
         << setw(15) << left << "Estado"
         << setw(15) << left << "Descripcion"
         << endl;

    for (auto proyecto : *proyectos)
    {
        cout << setw(15) << left << proyecto->getNombre()
             << setw(15) << left << proyecto->getPropietario()
             << setw(30) << left << proyecto->getFecha()
             << setw(15) << left << proyecto->getEstado()
             << setw(15) << left << proyecto->getDescripcion()
             << endl;
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
}
