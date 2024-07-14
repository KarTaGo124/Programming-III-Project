#ifndef GESTOR_ARCHIVOS_H
#define GESTOR_ARCHIVOS_H

#include <vector>
#include "login/cuentas.h"

using namespace std;

class GestorArchivos {
private:
    static GestorArchivos* instancia;
    GestorArchivos() {}

public:
    static GestorArchivos* obtenerInstancia();
    static void guardarCuentas(const vector<Cuenta*>& cuentas);
    static void cargarCuentas(vector<Cuenta*>& cuentas);
};

#endif // GESTOR_ARCHIVOS_H