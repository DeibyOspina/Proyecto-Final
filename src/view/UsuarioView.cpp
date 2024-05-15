#pragma once

#include <iostream>
#include "../controller/UsuarioController.cpp"
#include "../model/Usuario.cpp"
#include "../Utils/Utils.cpp"
#include "./TareaView.cpp"
#include "./ProyectoView.cpp"

using namespace std;

class UsuarioView
{
private:
    UsuarioController usuarioController;
    TareaView tareaView;
    ProyectoView proyectoView;
    string username;
    string password;
    string nombre;

public:
    UsuarioView();
    void clear();
    void showLogin();
    void showRegister();
    void showMenu();
    void showMenuDashBoard();
};

UsuarioView::UsuarioView() {}

void UsuarioView::clear()
{
    username = "";
    password = "";
    nombre = "";
}

void UsuarioView::showLogin()
{
    cout << "inicio de sesión" << endl;
    cout << "Usuario: ";
    cin >> username;
    cout << "Contraseña: ";
    cin >> password;
}

void UsuarioView::showRegister()
{
    cout << "Registro:" << endl;
    do
    {
        cout << "Ingrese el nombre de usuario: ";
        cin >> username;
    } while (username.empty());
    username = Utils::toLowerCase(username);

    do
    {
        cout << "Ingrese la contraseña: ";
        cin >> password;
    } while (password.empty());

    do
    {
        cout << "Ingrese su nombre: ";
        nombre = Utils::getLine(nombre);
    } while (nombre.empty());
}

void UsuarioView::showMenu()
{
    int option = 0;

    do
    {
        clear();
        cout << "1. Iniciar sesión" << endl;
        cout << "2. Registrarse" << endl;
        cout << "3. Salir" << endl;
        cout << "Ingrese una opción: ";
        cin >> option;
        Utils::clearScreen();

        switch (option)
        {
        case 1:
            showLogin();
            if (usuarioController.login(username, password))
            {
                showMenuDashBoard();
            }
            else
            {
                cout << "Usuario o contraseña incorrectos" << endl;
            }
            break;

        case 2:
            showRegister();
            if (usuarioController.save(username, password, nombre) != nullptr)
            {
                cout << "Usuario registrado correctamente" << endl;
            }
            else
            {
                cout << "El usuario ya existe" << endl;
            }
            break;
        default:
            cout << "Opción inválida" << endl;
            break;
        }
    } while (option != 3);
}

void UsuarioView::showMenuDashBoard()
{
    int opcion = 0;
    Utils::clearScreen();
    do
    {
        cout << "-------------------------------------------------" << endl;
        cout << "Bienvenido " << usuarioController.getLoggedUser()->getResponsable()->getNombre() << endl;
        cout << "1. Tareas" << endl;
        cout << "2. Proyectos" << endl;
        cout << "3. Salir" << endl;
        cout << "-------------------------------------------------" << endl;

        cout << "Ingrese una opción: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            tareaView.menuTarea();
            break;
        case 2:
            proyectoView.showMenuProyecto();
            break;
        case 3:
            cout << "Saliendo.." << endl;
            usuarioController.logout();
            break;
        default:
            cout << "Opción inválida" << endl;
            break;
        }

    } while (opcion != 3);
}
