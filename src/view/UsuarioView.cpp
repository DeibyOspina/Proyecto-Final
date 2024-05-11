#pragma once

#include <iostream>
#include "../controller/UsuarioController.cpp"
#include "../utils/Utils.cpp"
using namespace std;

class UsuarioView
{
private:
    UsuarioController usuarioController;
    string username;
    string password;
    string nombre;

public:
    UsuarioView(){};

    void clear()
    {
        username = "";
        password = "";
        nombre = "";
    }

    void showLogin()
    {
        cout << "inicio de sesión" << endl;
        cout << "Usuario: ";
        cin >> username;
        cout << "Contraseña: ";
        cin >> password;
    };

    void showRegister()
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
    };

    void showMenu()
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

            case 3:
                cout << "Saliendo..." << endl;
                usuarioController.logout();
                break;
            default:
                cout << "Opción inválida" << endl;
                break;
            }
        } while (option != 3);
    };

    void showMenuDashBoard()
    {
        cout << "-------------------------------------------------" << endl;
        cout << "Bienvenido " << usuarioController.getLoggedUser()->getResponsable()->getNombre() << endl;
        cout << "1. Ver mis datos" << endl;
        cout << "2. Actualizar mis datos" << endl;
        cout << "3. Salir" << endl;
        cout << "-------------------------------------------------" << endl;
    }
};
