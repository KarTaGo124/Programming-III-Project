#ifndef GESTOR_CUENTAS_H
#define GESTOR_CUENTAS_H

#include "cuenta.h"
#include <unordered_map>

using namespace std;

class GestorCuentas {
private:
    static GestorCuentas *instancia;
    unordered_map<string, Cuenta *> cuentas;

    GestorCuentas() = default;

public:
    static GestorCuentas *obtenerInstancia();

    bool agregarCuenta(const string &correo, const string &contrasenia);

    bool correoExistente(const string &correo) const;

    Cuenta *obtenerCuenta(const string &correo);

    const unordered_map<string, Cuenta *> &obtenerTodasLasCuentas() const;

    ~GestorCuentas();
};

#endif // GESTOR_CUENTAS_H