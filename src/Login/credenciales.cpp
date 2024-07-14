#include "credenciales.h"
#include <iostream>

using namespace std;

bool AutenticacionReal::autenticar(const string &correo, const string &contrasenia) const {
    auto it = usuarios.find(correo);
    if (it != usuarios.end() && it->second == contrasenia) {
        cout << "Autenticación exitosa para: " << correo << endl;
        return true;
    }
    cout << "Autenticación fallida para: " << correo << endl;
    return false;
}

void AutenticacionReal::agregarCuenta(Cuenta* cuenta) {
    usuarios[cuenta->getCorreo()] = cuenta->getContrasenia();
}

bool ProxyAutenticacion::autenticar(const string &correo, const string &contrasenia) const {
    return autenticacionReal.autenticar(correo, contrasenia);
}

void ProxyAutenticacion::agregarCuenta(Cuenta* cuenta) {
    autenticacionReal.agregarCuenta(cuenta);
}
