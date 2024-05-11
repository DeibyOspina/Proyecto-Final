#pragma once
#include <iostream>
#include <algorithm>
#include "../model/BD.cpp"

using namespace std;

class UsuarioController
{
private:
    BD *bd;

public:
    UsuarioController()
    {
        bd = BD::getInstance();
    };

    bool login(string username, string password)
    {
        Usuario *usuario = findByUsername(username);
        if (usuario == nullptr)
        {
            return false;
        }
        else if (usuario->getPassword() == password)
        {
            bd->setUsuario(usuario);
            return true;
        }
        return false;
    };

    void logout()
    {
        bd->setUsuario(nullptr);
    };

    bool isLogged()
    {
        return bd->getUsuario() != nullptr;
    };

    Usuario *save(string username, string password, string nombre)
    {
        Usuario *usuario = findByUsername(username);
        if (usuario != nullptr)
        {
            return nullptr;
        }
        else
        {
            Responsable *responsable = new Responsable(nombre);
            Usuario *usuario = new Usuario(username, password, responsable);
            bd->getUsuarios()->push_back(usuario);
            return usuario;
        }
    };

    bool update(string username, string password, string nombre)
    {
        Usuario *usuario = findByUsername(username);
        if (usuario != nullptr)
        {
            usuario->setPassword(password);
            usuario->getResponsable()->setNombre(nombre);
        }
        return usuario != nullptr;
    };

    Usuario *findByUsername(string username)
    {
        vector<Usuario *> *usuarios = bd->getUsuarios();
        auto it = find_if(usuarios->begin(), usuarios->end(), [username](Usuario *usuario)
                          { return usuario->getUsername() == username; });

        return it != usuarios->end() ? *it : nullptr;
    };

    Usuario *getLoggedUser()
    {
        return bd->getUsuario();
    };
};
