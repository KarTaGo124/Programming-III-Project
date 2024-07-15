#ifndef GESTOR_ARCHIVOS_H
#define GESTOR_ARCHIVOS_H

#include "login/gestor_cuentas.h"

class GestorArchivos {
private:
    static GestorArchivos *instancia;

    GestorArchivos() = default;

public:
    static GestorArchivos *obtenerInstancia() {
        if (instancia == nullptr) {
            instancia = new GestorArchivos();
        }
        return instancia;
    }

    void cargarCuentas(GestorCuentas &cuentas);
    void guardarCuenta(Cuenta &cuenta);
};

#endif
