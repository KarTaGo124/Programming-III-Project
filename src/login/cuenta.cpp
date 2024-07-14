#include "cuenta.h"
#include <iostream>

using namespace std;

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

unordered_set<int> &Cuenta::getVerMasTarde() {
    return verMasTarde;
}

unordered_map<string, int> &Cuenta::getLikes() {
    return likes;
}

void Cuenta::agregarVerMasTarde(int idPelicula) {
    verMasTarde.insert(idPelicula);
}

void Cuenta::agregarLike(const string &tag) {
    likes[tag]++;
}

void Cuenta::agregarVerAhora(string titulo) {
    cout << "Disfrutando la película: " << titulo << endl;
}
