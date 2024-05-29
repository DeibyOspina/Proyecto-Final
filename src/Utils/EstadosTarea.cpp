#include <iostream>
using namespace std;

class EstadosTarea
{
public:
    static string NOT_STARTED;
    static string IN_PROCESS;
    static string FINISHED;
    static string CANCELED;

    static void showEstados();
    static string selectEstado(int index);
    static string selectEstado(string estado);
    static string selectEstadoRoot(string estado);
};

string EstadosTarea::NOT_STARTED = "\033[31mNo iniciada \033[0m";
string EstadosTarea::IN_PROCESS = "\033[33mEn proceso \033[0m";
string EstadosTarea::FINISHED = "\033[32mTerminada \033[0m";
string EstadosTarea::CANCELED = "\033[94mCancelada \033[0m";

void EstadosTarea::showEstados()
{
    cout << "---- " << "Estados Tarea" << " ----" << endl;
    cout << "1. " << NOT_STARTED << endl;
    cout << "2. " << IN_PROCESS << endl;
    cout << "3. " << FINISHED << endl;
    cout << "4. " << CANCELED << endl;
    cout << "--------------------------" << endl;
}

string EstadosTarea::selectEstado(int index)
{
    switch (index)
    {
    case 1:
        return NOT_STARTED;
    case 2:
        return IN_PROCESS;
    case 3:
        return FINISHED;
    case 4:
        return CANCELED;
    default:
        return "";
    }
}

string EstadosTarea::selectEstado(string estado)
{
    estado = Utils::toLowerCase(estado);
    if (estado == "no iniciada")
    {
        return NOT_STARTED;
    }
    else if (estado == "en proceso")
    {
        return IN_PROCESS;
    }
    else if (estado == "terminada")
    {
        return FINISHED;
    }
    else if (estado == "cancelada")
    {
        return CANCELED;
    }
    else
    {
        return NOT_STARTED;
    }
}

string EstadosTarea::selectEstadoRoot(string estado)
{
    if (estado == NOT_STARTED)
    {
        return "No iniciada";
    }
    else if (estado == IN_PROCESS)
    {
        return "En proceso";
    }
    else if (estado == FINISHED)
    {
        return "Terminada";
    }
    else if (estado == CANCELED)
    {
        return "Cancelada";
    }
    else
    {
        return "No iniciada";
    }
}