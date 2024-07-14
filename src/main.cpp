#include "gestor_archivos.h"
#include "Login/credenciales.h"
#include "Login/cuentas.h"
#include "streaming.cpp"

#include <string>

using namespace std;

void menu(vector<Cuenta*>& cuentas, ProxyAutenticacion& proxy) {
    bool autenticacionExitosa = false;

    while (!autenticacionExitosa) {
        cout << "1. Registrarse\n";
        cout << "2. Iniciar sesión\n";
        cout << "3. Salir\n";
        cout << "Elija una opción: ";

        int opcion;
        cin >> opcion;
        cin.ignore();  // Ignorar el salto de línea residual en el buffer

        switch (opcion) {
            case 1: {
                string correo, contrasenia;
                cout << "Ingrese el correo: ";
                getline(cin, correo);
                cout << "Ingrese la contraseña: ";
                getline(cin, contrasenia);
                Cuenta* cuenta = new Cuenta(correo, contrasenia);
                cuentas.push_back(cuenta);
                proxy.agregarCuenta(cuenta);
                GestorArchivos::obtenerInstancia()->guardarCuentas(cuentas);
                break;
            }
            case 2: {
                string correo, contrasenia;
                cout << "Ingrese el correo: ";
                getline(cin, correo);
                cout << "Ingrese la contraseña: ";
                getline(cin, contrasenia);

                if (proxy.autenticar(correo, contrasenia)) {
                    autenticacionExitosa = true;
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

    Streaming streaming;
    streaming.systemOn();
}

int main() {
    vector<Cuenta*> cuentas;
    GestorArchivos::obtenerInstancia()->cargarCuentas(cuentas);
    ProxyAutenticacion proxy;
    for (auto cuenta : cuentas) {
        proxy.agregarCuenta(cuenta);
    }
    menu(cuentas, proxy);

    for (auto cuenta : cuentas) {
        delete cuenta;
    }

    return 0;
}
