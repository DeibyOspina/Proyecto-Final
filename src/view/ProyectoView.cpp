#include <iostream>
#include <iomanip>
#include <string>
#include "../Utils/Utils.cpp"
#include "../controller/ProyectoController.cpp"
using namespace std;

class ProyectoView
{
private:
    ProyectoController proyectoController;
    string nombre;
    string descripcion;
    string propietario;

public:
    ProyectoView();
    void showMenuProyecto();
    void showCreateProyecto();
    void showEditProyecto();
    void showProyectos();
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
            showProyectos();
            break;
        default:
            cout << "Opcion no valida" << endl;
            break;
        }
    } while (opcion != 4);
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
}

void ProyectoView::showEditProyecto()
{
    showProyectos();
    cin.ignore();
    cout << "Seleccione un proyecto: ";
    getline(cin, nombre);

    auto proyecto = proyectoController.findProyectoByNombre(nombre);
    if (proyecto != nullptr)
    {
        do
        {
            try
            {
                cout << "------- Editar Proyecto ---------" << endl;
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
                cerr << e.what() << '\n';
            }
        } while (true);
    }
}

void ProyectoView::showProyectos()
{
    set<Proyecto *> *proyectos = proyectoController.listProyectos();
    cout << setw(15) << left << "Nombre"
         << setw(15) << left << "Propietario"
         << setw(15) << left << "Descripcion"
         << endl;

    for (auto proyecto : *proyectos)
    {
        cout << setw(15) << left << proyecto->getNombre()
             << setw(15) << left << proyecto->getPropietario()
             << setw(15) << left << proyecto->getDescripcion()
             << endl;
    }
}