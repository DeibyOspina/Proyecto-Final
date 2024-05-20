#include <iostream>
#include <string>
#include <set>
#include <list>
#include <iomanip>

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
    void showFormNotas(Proyecto* proyecto);
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
         << setw(15) << left << nota->getReacciones().size()
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
    for (Nota *nota : notas)
    {
        showNota(nota);
    }
}

void NotasView::showFormNotas(Proyecto* proyecto)
{
    cout << "Titulo: ";
    getline(cin, titulo);

    cout << "Descripcion: ";
    getline(cin, descripcion);

    notasController.setProyecto(proyecto);
    notasController.addNotaProyecto(titulo, descripcion);
    notasController.setProyecto(nullptr);
}