#include <iostream>
#include <string>
#include <set>
#include <list>
#include <iomanip>
#include <algorithm>

#include "../controller/NotasController.cpp"
using namespace std;

class NotasView
{
private:
    NotasController notasController;

    void showHeader();
    string titulo;
    string descripcion;

public:
    NotasView();
    void showNota(Nota *nota);
    void showNotas(set<Nota *> notas);
    void showNotas(list<Nota *> notas);
    void showFormNotas(Proyecto *proyecto);
    void showFormNotas(Tarea *tarea);
    void showFormAddReaccion(Proyecto *proyecto);
    void showFormAddReaccion(Tarea* tarea);
};

NotasView::NotasView()
{
}

void NotasView::showHeader()
{
    cout << setw(15) << left << "Titulo"
         << setw(15) << left << "Autor"
         << setw(30) << left << "Descripcion"
         << setw(15) << left << "Reacciones"
         << endl;
}

void NotasView::showNota(Nota *nota)
{
    cout << setw(15) << left << nota->getTitulo()
         << setw(15) << left << nota->getAutor()->getResponsable()->getNombre()
         << setw(30) << left << nota->getDescripcion()
         << setw(15) << left << nota->convertReaccionesToString()
         << endl;
}

void NotasView::showNotas(set<Nota *> notas)
{
    for (Nota *nota : notas)
    {
        showNota(nota);
    }
}

void NotasView::showNotas(list<Nota *> notas)
{
    showHeader();
    for (Nota *nota : notas)
    {
        showNota(nota);
    }
}

void NotasView::showFormNotas(Tarea *Tarea)
{
    cout << "Titulo: ";
    getline(cin, titulo);

    cout << "Descripcion: ";
    getline(cin, descripcion);

    notasController.setTarea(Tarea);
    notasController.addNotaTarea(titulo, descripcion);
    notasController.setTarea(nullptr);
}


void NotasView::showFormNotas(Proyecto *proyecto)
{
    cout << "Titulo: ";
    getline(cin, titulo);

    cout << "Descripcion: ";
    getline(cin, descripcion);

    notasController.setProyecto(proyecto);
    notasController.addNotaProyecto(titulo, descripcion);
    notasController.setProyecto(nullptr);
}

void NotasView::showFormAddReaccion(Proyecto *proyecto)
{
    notasController.setProyecto(proyecto);
    string nombreNota;
    cout << "Ingrese el nombre de la nota: ";
    getline(cin, nombreNota);

    Nota *nota = notasController.findNotaProyectoByNombre(nombreNota);
    if (nota == nullptr)
    {
        cout << "Nota no encontrada" << endl;
        return;
    }

    int index = 0;
    string nombreReaccion;
    Reacciones::showReacciones();

    while (nombreReaccion.empty())
    {
        cout << "Seleccione una reaccion: ";
        cin >> index;
        nombreReaccion = Reacciones::selectReaccion(index);
        if (nombreReaccion.empty())
        {
            cout << "Reaccion no valida" << endl;
        }
    }

    nota->addReaccion(new Reaccion(nombreReaccion, BD::getInstance()->getUsuario()));
    cout << "Reaccion agregada" << endl;
}


void NotasView::showFormAddReaccion(Tarea *tarea)
{
    notasController.setTarea(tarea);
    string nombreNota;
    cout << "Ingrese el nombre de la nota: ";
    getline(cin, nombreNota);

    Nota *nota = notasController.findNotaTareaByNombre(nombreNota);
    if (nota == nullptr)
    {
        cout << "Nota no encontrada" << endl;
        return;
    }

    int index = 0;
    string nombreReaccion;
    Reacciones::showReacciones();

    while (nombreReaccion.empty())
    {
        cout << "Seleccione una reaccion: ";
        cin >> index;
        nombreReaccion = Reacciones::selectReaccion(index);
        if (nombreReaccion.empty())
        {
            cout << "Reaccion no valida" << endl;
        }
    }
    nota->addReaccion(new Reaccion(nombreReaccion, BD::getInstance()->getUsuario()));
    cout << "Reaccion agregada" << endl;
}