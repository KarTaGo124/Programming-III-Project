#include "credenciales.h"

// Implementación de Memento
Memento::Memento(const string &email, const string &password) : correo(email), contrasenia(password) {}

string Memento::getCorreo() const {
    return correo;
}

string Memento::getContrasenia() const {
    return contrasenia;
}

// Implementación de Cuenta
Cuenta::Cuenta(const string &email, const string &password) : correo(email), contrasenia(password) {}

void Cuenta::guardarCuenta() {
    estados.emplace_back(correo, contrasenia);
    cout << "Cuenta Guardada" << endl;
}

string Cuenta::getCorreo() const {
    return correo;
}

string Cuenta::getContrasenia() const {
    return contrasenia;
}

// Implementación de AutenticacionReal
AutenticacionReal::AutenticacionReal() {
    usuarios["usuario1@example.com"] = "password1";
}

bool AutenticacionReal::autenticar(const string &correo, const string &contrasenia) const {
    auto it = usuarios.find(correo);
    if (it != usuarios.end() && it->second == contrasenia) {
        cout << "Autenticacion exitosa para: " << correo << endl;
        return true;
    }
    cout << "Autenticacion fallida para: " << correo << endl;
    return false;
}

void AutenticacionReal::agregarCuenta(const string &correo, const string &contrasenia) {
    usuarios[correo] = contrasenia;
}

// Implementación de ProxyAutenticacion
bool ProxyAutenticacion::autenticar(const string &correo, const string &contrasenia) const {
    return autenticacionReal.autenticar(correo, contrasenia);
}

void ProxyAutenticacion::agregarCuenta(const string &correo, const string &contrasenia) {
    autenticacionReal.agregarCuenta(correo, contrasenia);
}



