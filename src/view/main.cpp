#include <iostream>
#include "UsuarioView.cpp"

using namespace std;

int main(int argc, char const *argv[])
{
    UsuarioView *usuarioView = new UsuarioView();
    usuarioView->showMenu();
    return 0;
}
