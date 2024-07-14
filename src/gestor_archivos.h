#ifndef GESTOR_ARCHIVOS_H
#define GESTOR_ARCHIVOS_H

#include "login/gestor_cuentas.h"
#include <vector>

class GestorArchivos {
private:
    static GestorArchivos *instancia;

    GestorArchivos() = default;

public:
    static GestorArchivos *obtenerInstancia();

    void guardarCuentas(const GestorCuentas &cuentas);

    void cargarCuentas(GestorCuentas &cuentas);
};

#endif // GESTOR_ARCHIVOS_H
