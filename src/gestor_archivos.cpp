#include "gestor_archivos.h"
#include <fstream>
#include <iostream>

using namespace std;

GestorArchivos* GestorArchivos::instancia = nullptr;

GestorArchivos* GestorArchivos::obtenerInstancia() {
    if (instancia == nullptr) {
        instancia = new GestorArchivos();
    }
    return instancia;
}

void GestorArchivos::guardarCuentas(const vector<Cuenta*>& cuentas) {
    ofstream archivo("../archivos/cuentas.txt");
    for (auto cuenta : cuentas) {
        archivo << cuenta->getCorreo() << " " << cuenta->getContrasenia() << endl;
    }
    archivo.close();
}

void GestorArchivos::cargarCuentas(vector<Cuenta*>& cuentas) {
    ifstream archivo("../archivos/cuentas.txt");
    string correo, contrasenia;
    while (archivo >> correo >> contrasenia) {
        cuentas.push_back(new Cuenta(correo, contrasenia));
    }
    archivo.close();
}
