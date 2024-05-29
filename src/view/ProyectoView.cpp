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
        cout << "3. Salir" << endl;
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

void ProyectoView::menuAddNotaProyecto()
{
    showProyectos(proyectoController.listProyectos());
    cin.ignore();
    cout << "Seleccione un proyecto: ";
    getline(cin, nombre);

    auto proyecto = proyectoController.findProyectoByNombre(nombre);
    if (proyecto != nullptr)
    {
        notasView.showFormNotas(proyecto);
    }
}
