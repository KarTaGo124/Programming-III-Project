#include "gestor_cuentas.h"

GestorCuentas *GestorCuentas::instancia = nullptr;

GestorCuentas *GestorCuentas::obtenerInstancia() {
    if (instancia == nullptr) {
        instancia = new GestorCuentas();
    }
    return instancia;
}

bool GestorCuentas::agregarCuenta(const string &correo, const string &contrasenia) {
    if (correoExistente(correo)) {
        return false;
    }
    cuentas[correo] = new Cuenta(correo, contrasenia);
    return true;
}

bool GestorCuentas::correoExistente(const string &correo) const {
    return cuentas.find(correo) != cuentas.end();
}

Cuenta *GestorCuentas::obtenerCuenta(const string &correo) {
    if (correoExistente(correo)) {
        return cuentas[correo];
    }
    return nullptr;
}

const unordered_map<string, Cuenta *> &GestorCuentas::obtenerTodasLasCuentas() const {
    return cuentas;
}

GestorCuentas::~GestorCuentas() {
    for (auto &pair: cuentas) {
        delete pair.second;
    }
}
