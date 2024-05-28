#include <iostream>
using namespace std;

class Reacciones
{
public:
    static string HAPPY_FACE;
    static string SAD_FACE;
    static string ANGRY_FACE;
    static string CRYING_FACE;

    static void showReacciones();
    static string selectReaccion(int reaccion);
};

string Reacciones::HAPPY_FACE = "😊";
string Reacciones::SAD_FACE = "😢";
string Reacciones::ANGRY_FACE = "😡";
string Reacciones::CRYING_FACE = "😭";

void Reacciones::showReacciones()
{
    cout << "---- " << "Reacciones" << " ----" << endl;
    cout << "1. " << HAPPY_FACE << endl;
    cout << "2. " << SAD_FACE << endl;
    cout << "3. " << ANGRY_FACE << endl;
    cout << "4. " << CRYING_FACE << endl;
    cout << "--------------------------" << endl;
}

string Reacciones::selectReaccion(int index)
{
    switch (index)
    {
    case 1:
        return HAPPY_FACE;
    case 2:
        return SAD_FACE;
    case 3:
        return ANGRY_FACE;
    case 4:
        return CRYING_FACE;
    default:
        return "";
    }
}