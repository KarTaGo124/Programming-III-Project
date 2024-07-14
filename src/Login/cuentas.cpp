#include "cuentas.h"

Cuenta::Cuenta(const string &email, const string &password)
        : correo(email), contrasenia(password) {}

void Cuenta::setCorreo(const string &email) {
    correo = email;
}

void Cuenta::setContrasenia(const string &password) {
    contrasenia = password;
}

string Cuenta::getCorreo() const {
    return correo;
}

string Cuenta::getContrasenia() const {
    return contrasenia;
}
