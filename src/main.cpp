#include "gestor_archivos.h"
#include "login/autenticacion.h"
#include "login/gestor_cuentas.h"
#include "streaming.cpp"

#include <iostream>

using namespace std;

void menu(GestorCuentas &cuentas, ProxyAutenticacion &proxy) {
    Cuenta *cuenta = nullptr;
    bool autenticacionExitosa = false;

    while (!autenticacionExitosa) {
        cout << "1. Registrarse\n";
        cout << "2. Iniciar sesión\n";
        cout << "3. Salir\n";
        cout << "Elija una opción: ";

        int opcion;
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                string correo, contrasenia;
                cout << "Ingrese el correo: ";
                cin >> correo;
                cout << "Ingrese la contraseña: ";
                cin >> contrasenia;

                if (cuentas.agregarCuenta(correo, contrasenia)) {
                    cuenta = cuentas.obtenerCuenta(correo);
                    proxy.agregarCuenta(cuenta);
                    GestorArchivos::obtenerInstancia()->guardarCuentas(cuentas);
                } else {
                    cout << "Error: El correo ya está registrado.\n";
                }
                break;
            }
            case 2: {
                string correo, contrasenia;
                cout << "Ingrese el correo: ";
                cin >> correo;
                cout << "Ingrese la contraseña: ";
                cin >> contrasenia;

                if (proxy.autenticar(correo, contrasenia)) {
                    cuenta = cuentas.obtenerCuenta(correo);
                    autenticacionExitosa = true;
                } else {
                    cout << "Error: Credenciales incorrectas.\n";
                }
                break;
            }
            case 3:
                GestorArchivos::obtenerInstancia()->guardarCuentas(cuentas);
                return;
            default:
                cout << "Opción inválida. Por favor, elija una opción válida. " << endl;
        }
    }

    if (cuenta) {
        Streaming streaming;
        streaming.systemOn(cuenta);
    }
}

int main() {
    GestorCuentas *cuentas = GestorCuentas::obtenerInstancia();
    GestorArchivos::obtenerInstancia()->cargarCuentas(*cuentas);
    ProxyAutenticacion proxy;
    const auto &todasLasCuentas = cuentas->obtenerTodasLasCuentas();
    for (const auto &pair: todasLasCuentas) {
        proxy.agregarCuenta(pair.second);
    }

    menu(*cuentas, proxy);

    return 0;
}
