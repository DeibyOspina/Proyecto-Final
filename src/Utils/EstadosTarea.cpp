#include <iostream>
using namespace std;

class EstadosTarea
{
public:
    static string PENDIENTE;
    static string EN_PROCESO;
    static string TERMINADA;
    static string CANCELADA;
};

string EstadosTarea::PENDIENTE = "Pendiente";
string EstadosTarea::EN_PROCESO = "En proceso";
string EstadosTarea::TERMINADA = "Terminada";
string EstadosTarea::CANCELADA = "Cancelada";