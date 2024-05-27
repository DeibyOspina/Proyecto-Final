#include <iostream>
using namespace std;

class EstadosProyecto
{
public:
    static string NOT_STARTED;
    static string IN_PROCESS;
    static string FINISHED;
    static string CANCELED;

    static void showEstados();

    static string selectEstado(int index);
};

string EstadosProyecto::NOT_STARTED = "\033[31mNo iniciado \033[0m";
string EstadosProyecto::IN_PROCESS = "\033[33mEn proceso \033[0m";
string EstadosProyecto::FINISHED = "\033[32mTerminado \033[0m";
string EstadosProyecto::CANCELED = "\033[94mCancelado \033[0m";

void EstadosProyecto::showEstados()
{
    cout << "---- " << "Estados Proyecto" << " ----" << endl;
    cout << "1. " << NOT_STARTED << endl;
    cout << "2. " << IN_PROCESS << endl;
    cout << "3. " << FINISHED << endl;
    cout << "4. " << CANCELED << endl;
    cout << "--------------------------" << endl;
}

string EstadosProyecto::selectEstado(int index)
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


