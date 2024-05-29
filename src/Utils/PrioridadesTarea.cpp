#include <iostream>
using namespace std;

class PrioridadesTarea
{
public:
    static string HIGH;
    static string MEDIUM;
    static string LOW;

    static void showPrioridades();
    static string selectPrioridad(int index);
    static string selectPrioridad(string prioridad);
    static string selectPrioridadRoot(string prioridad);
};

string PrioridadesTarea::HIGH = "\033[31mAlta \033[0m";
string PrioridadesTarea::MEDIUM = "\033[33mMedia \033[0m";
string PrioridadesTarea::LOW = "\033[32mBaja \033[0m";

void PrioridadesTarea::showPrioridades()
{
    cout << "---- " << "Prioridades Tarea" << " ----" << endl;
    cout << "1. " << HIGH << endl;
    cout << "2. " << MEDIUM << endl;
    cout << "3. " << LOW << endl;
    cout << "--------------------------" << endl;
}

string PrioridadesTarea::selectPrioridad(int index)
{
    switch (index)
    {
    case 1:
        return HIGH;
    case 2:
        return MEDIUM;
    case 3:
        return LOW;
    default:
        return "";
    }
}

string PrioridadesTarea::selectPrioridad(string prioridad)
{
    prioridad = Utils::toLowerCase(prioridad);
    if (prioridad == "alta")
    {
        return HIGH;
    }
    else if (prioridad == "media")
    {
        return MEDIUM;
    }
    else if (prioridad == "baja")
    {
        return LOW;
    }
    else
    {
        return LOW;
    }
}

string PrioridadesTarea::selectPrioridadRoot(string prioridad)
{
    if (prioridad == HIGH)
    {
        return "Alta";
    }
    else if (prioridad == MEDIUM)
    {
        return "Media";
    }
    else if (prioridad == LOW)
    {
        return "Baja";
    }
    else
    {
        return "Baja";
    }
}