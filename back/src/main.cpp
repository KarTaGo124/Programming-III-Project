#include "gestor_archivos.h"
#include "login/autenticacion.h"
#include "login/gestor_cuentas.h"
#include "streaming.cpp"

#include <iostream>

using namespace std;

/*bool registro(GestorCuentas &cuentas, ProxyAutenticacion &proxy,int opcion,string correo, string contrasenia) {
    Cuenta *cuenta = nullptr;
    bool autenticacionExitosa = false;

    while (!autenticacionExitosa) {
        
        switch (opcion) {
            case 1: {
                if (cuentas.obtenerCuenta(correo) == nullptr) {
                    if (cuentas.agregarCuenta(correo, contrasenia)) {
                        cuenta = cuentas.obtenerCuenta(correo);
                        proxy.agregarCuenta(cuenta);
                        GestorArchivos::obtenerInstancia()->guardarCuenta(*cuenta); // Guardar la nueva cuenta
                        return true;
                    } else {
                        return false;
                    }
                } else {
                    return false;
                }
                break;
            }
            case 2: {

                if (proxy.autenticar(correo, contrasenia)) {
                    cuenta = cuentas.obtenerCuenta(correo);
                    GestorArchivos::obtenerInstancia()->cargarCuenta(*cuenta); // Cargar datos de la cuenta
                    return true;
                } else {
                    return false;
                }
                break;
            }

        }
    }

    if (cuenta) {
        Streaming streaming;
        streaming.systemOn(cuenta);
        GestorArchivos::obtenerInstancia()->guardarCuenta(*cuenta); // Guardar la cuenta al cerrar sesión
    }
}
*/
/*int main() {
    GestorCuentas *cuentas = GestorCuentas::obtenerInstancia();
    GestorArchivos::obtenerInstancia()->cargarCuentas(*cuentas); // Cargar todas las cuentas al inicio
    ProxyAutenticacion proxy;
    const auto &todasLasCuentas = cuentas->obtenerTodasLasCuentas();
    for (const auto &pair : todasLasCuentas) {
        proxy.agregarCuenta(pair.second);
    }

    registro(*cuentas, proxy);

    return 0;
}
*/