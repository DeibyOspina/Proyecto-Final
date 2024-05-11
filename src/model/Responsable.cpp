#include <iostream>
using namespace std;

class Responsable
{
private:
    string nombre;

public:
    Responsable(string nombre) : nombre(nombre){};
    
    string getNombre()
    {
        return nombre;
    };
    
    void setNombre(string nombre)
    {
        this->nombre = nombre;
    };
};