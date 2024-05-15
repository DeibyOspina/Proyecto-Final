#include <iostream>
using namespace std;

class EstadosProyecto
{
public:
    static string PROCESO;
    static string TERMINADO;
    static string CANCELADO;
};

string EstadosProyecto::PROCESO = "En proceso";
string EstadosProyecto::TERMINADO = "Terminado";
string EstadosProyecto::CANCELADO = "Cancelado";