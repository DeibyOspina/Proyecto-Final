#pragma once

#include <iostream>
#include <algorithm>
#include "../model/Usuario.cpp"
#include "../model/BD.cpp"

using namespace std;

class UsuarioController
{
private:
    BD *bd;

public:
    UsuarioController();
    bool login(string username, string password);
    void logout();
    bool isLogged();
    Usuario *save(string username, string password, string nombre);
    bool update(string username, string password, string nombre);
    Usuario *findByUsername(string username);
    Usuario *getLoggedUser();
};

UsuarioController::UsuarioController()
{
    bd = BD::getInstance();
}

bool UsuarioController::login(string username, string password)
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
}

void UsuarioController::logout()
{
    bd->setUsuario(nullptr);
}

bool UsuarioController::isLogged()
{
    return bd->getUsuario() != nullptr;
}

Usuario *UsuarioController::save(string username, string password, string nombre)
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
}

bool UsuarioController::update(string username, string password, string nombre)
{
    Usuario *usuario = findByUsername(username);
    if (usuario != nullptr)
    {
        usuario->setPassword(password);
        usuario->getResponsable()->setNombre(nombre);
    }
    return usuario != nullptr;
}

Usuario *UsuarioController::findByUsername(string username)
{
    vector<Usuario *> *usuarios = bd->getUsuarios();
    auto it = find_if(usuarios->begin(), usuarios->end(), [username](Usuario *usuario)
                      { return usuario->getUsername() == username; });

    return it != usuarios->end() ? *it : nullptr;
}

Usuario *UsuarioController::getLoggedUser()
{
    return bd->getUsuario();
}
