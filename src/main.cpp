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
        cout << "2. Iniciar sesion\n";
        cout << "3. Salir\n";
        cout << "Elija una opcion: ";

        int opcion;
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                string correo, contrasenia;
                cout << "Ingrese el correo: ";
                cin >> correo;
                cout << "Ingrese la contrasena: ";
                cin >> contrasenia;

                if (cuentas.obtenerCuenta(correo) == nullptr) {
                    if (cuentas.agregarCuenta(correo, contrasenia)) {
                        cuenta = cuentas.obtenerCuenta(correo);
                        proxy.agregarCuenta(cuenta);
                        GestorArchivos::obtenerInstancia()->guardarCuenta(*cuenta); // Guardar la nueva cuenta
                        cout << "Registro exitoso.\n";
                    } else {
                        cout << "Error: No se pudo registrar la cuenta.\n";
                    }
                } else {
                    cout << "Error: El correo ya esta registrado.\n";
                }
                break;
            }
            case 2: {
                string correo, contrasenia;
                cout << "Ingrese el correo: ";
                cin >> correo;
                cout << "Ingrese la contrasena: ";
                cin >> contrasenia;

                if (proxy.autenticar(correo, contrasenia)) {
                    cuenta = cuentas.obtenerCuenta(correo);
                    GestorArchivos::obtenerInstancia()->cargarCuenta(*cuenta); // Cargar datos de la cuenta
                    autenticacionExitosa = true;
                } else {
                    cout << "Error: Credenciales incorrectas.\n";
                }
                break;
            }
            case 3:
                return;
            default:
                cout << "Opcion invalida. Por favor, elija una opcion valida. " << endl;
        }
    }

    if (cuenta) {
        Streaming streaming;
        streaming.systemOn(cuenta);
        GestorArchivos::obtenerInstancia()->guardarCuenta(*cuenta); // Guardar la cuenta al cerrar sesión
    }
}

int main() {
    GestorCuentas *cuentas = GestorCuentas::obtenerInstancia();
    GestorArchivos::obtenerInstancia()->cargarCuentas(*cuentas); // Cargar todas las cuentas al inicio
    ProxyAutenticacion proxy;
    const auto &todasLasCuentas = cuentas->obtenerTodasLasCuentas();
    for (const auto &pair : todasLasCuentas) {
        proxy.agregarCuenta(pair.second);
    }

    menu(*cuentas, proxy);

    return 0;
}
