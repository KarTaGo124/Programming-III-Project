#include "cuentas.h"

Memento::Memento(const string &email, const string &password) : correo(email), contrasenia(password) {}

string Memento::getCorreo() const { return correo; }

string Memento::getContrasenia() const { return contrasenia; }

Cuenta::Cuenta(const string &email, const string &password) : correo(email), contrasenia(password) {
    guardarEstado();
}

Cuenta::~Cuenta() {
    for (auto estado : estados) {
        delete estado;
    }
}

void Cuenta::setCorreo(const string &email) { correo = email; }

void Cuenta::setContrasenia(const string &password) { contrasenia = password; }

string Cuenta::getCorreo() const { return correo; }

string Cuenta::getContrasenia() const { return contrasenia; }

void Cuenta::guardarEstado() {
    estados.push_back(new Memento(correo, contrasenia));
    cout << "Estado guardado." << endl;
}

void Cuenta::restaurarEstado(int indice) {
    if (indice >= 0 && indice < estados.size()) {
        correo = estados[indice]->getCorreo();
        contrasenia = estados[indice]->getContrasenia();
        cout << "Estado restaurado." << endl;
    } else {
        cout << "Índice inválido." << endl;
    }
}

vector<Memento*> Cuenta::getEstados() const {
    return estados;
}
