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
    void menuAddNotaProyecto(Proyecto *proyecto);
    void menuNotas(Proyecto *proyecto);
    void showMenuTareasProyecto();
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
        cout << "4. Buscar Tareas por Proyecto" << endl;
        cout << "5. Salir" << endl;
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
            showCreateProyecto();
            break;
        case 2:
            showEditProyecto();
            break;
        case 3:
            showMenuListProyecto();
            break;
        case 4:
            showMenuTareasProyecto();
            break;
        case 5:
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

    cout << "Seleccione un proyecto: ";
    getline(cin, nombre);

    auto proyecto = proyectoController.findProyectoByNombre(nombre);
    if (proyecto == nullptr)
    {
        cout << "Proyecto no encontrado" << endl;
        return;
    }

    Utils::clearScreen();
    int opcion = 0;
    do
    {
        cout << "----- Proyecto seleccionado: " << proyecto->getNombre() << endl;
        cout << "1. Cambiar Estado Proyecto " << endl;
        cout << "2. Editar Datos Proyecto" << endl;
        cout << "3. Notas Proyecto" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        Utils::clearScreen();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

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
                getline(cin, descripcion);

                cout << "Propietario: ";
                getline(cin, propietario);

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
        case 3:
            menuNotas(proyecto);
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }

    } while (opcion != 4);
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

        cout << "Notas: " << endl;
        notasView.showNotas(proyecto->getNotas());
    }
}

void ProyectoView::showMenuListProyecto()
{
    int opcion;
    bool sorted = true;
    do
    {
        cout << "1. Mostrar proyectos" << endl;
        cout << "2. Mostrar proyectos ordenados por fecha de creacion" << endl;
        cout << "3. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        Utils::clearScreen();

        switch (opcion)
        {
        case 1:
            showProyectos(proyectoController.listProyectos());
            break;
        case 2:
            showProyectos(proyectoController.sortProyectosByFecha(sorted));
            sorted = !sorted;
            break;
        case 3:
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }

    } while (opcion != 3);
    Utils::clearScreen();
}

void ProyectoView::menuNotas(Proyecto *proyecto)
{
    int opcion;
    string reaccionSelected;
    do
    {
        cout << "1. Agregar Nota" << endl;
        cout << "2. Agregar Reaccion" << endl;
        cout << "3. Listar Notas" << endl;
        cout << "4. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        Utils::clearScreen();

        switch (opcion)
        {
        case 1:
            menuAddNotaProyecto(proyecto);
            break;
        case 2:
            notasView.showFormAddReaccion(proyecto);
            break;
        case 3:
            notasView.showNotas(proyecto->getNotas());
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }
    } while (opcion != 4);
    Utils::clearScreen();
}

void ProyectoView::menuAddNotaProyecto(Proyecto *proyecto)
{
    auto proyectoIt = proyectoController.findProyectoByNombre(nombre);
    if (proyectoIt != nullptr)
    {
        notasView.showFormNotas(proyectoIt);
    }
}

void ProyectoView::showMenuTareasProyecto()
{
    string nombreProyecto;
    cout << "Ingrese el nombre del proyecto: ";
    cin >> nombreProyecto;
    auto proyecto = proyectoController.findProyectoByNombre(nombreProyecto);
    if (proyecto != nullptr)
    {
        cout << "Tareas del proyecto: " << proyecto->getNombre() << endl;
        for (auto tarea : proyecto->getTareas())
        {
            string responsablesStr;
            set<Responsable *> *responsables = tarea->getResponsables();
            for (auto it = responsables->begin(); it != responsables->end(); it++)
            {
                responsablesStr += (*it)->getNombre() + " | ";
            }

            cout << "Nombre: " << tarea->getNombre() << endl;
            cout << "Responsables: " << responsablesStr << endl;
            cout << "Fecha limite: " << tarea->getFechaLimite() << endl;
            cout << "Estado: " << tarea->getEstado() << endl;
            cout << "Prioridad: " << tarea->getPrioridad() << endl;
            cout << "Comentario: " << tarea->getComentario() << endl;
            cout << "--------------------------------" << endl;
        }
    }
    else
    {
        cout << "Proyecto no encontrado" << endl;
    }
}
