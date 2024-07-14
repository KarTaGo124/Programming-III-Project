#ifndef GESTOR_ARCHIVOS_H
#define GESTOR_ARCHIVOS_H

#include <vector>
#include "Login/cuentas.h"

class GestorArchivos {
private:
    static GestorArchivos* instancia;
    GestorArchivos() {}

public:
    static GestorArchivos* obtenerInstancia();
    void guardarCuentas(const vector<Cuenta*>& cuentas);
    void cargarCuentas(vector<Cuenta*>& cuentas);
};

#endif // GESTOR_ARCHIVOS_H
