#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Memento {
private:
    string nombreCuenta;
    string correo;

public:
    Memento(const string &nombre, const string &email)
            : nombreCuenta(nombre), correo(email) {}

    string getNombreCuenta() const { return nombreCuenta; }
    string getCorreo() const { return correo; }
};

class Cuenta {
private:
    string nombre;
    string correo;
    vector<Memento *> estados;

public:
    Cuenta(const string &nombre, const string &email)
            : nombre(nombre), correo(email) {
        guardarEstado();
    }

    string getNombre() const { return nombre; }
    string getCorreo() const { return correo; }

    void mostrarInfo() const {
        cout << "Cuenta: " << nombre << ", Correo: " << correo << endl;
    }

    void guardarEstado() {
        estados.push_back(new Memento(nombre, correo));
        cout << "Estado guardado." << endl;
    }

    void restaurarEstado() {
        cout << "Estados disponibles:" << endl;
        for (int i = 0; i < estados.size(); i++) {
            cout << i << ": " << estados[i]->getNombreCuenta()
                 << ", " << estados[i]->getCorreo() << endl;
        }
        int opcion;
        cout << "Seleccione el estado a restaurar: ";
        cin >> opcion;
        if (opcion >= 0 && opcion < estados.size()) {
            nombre = estados[opcion]->getNombreCuenta();
            correo = estados[opcion]->getCorreo();
            cout << "Estado restaurado." << endl;
        } else {
            cout << "Opción inválida." << endl;
        }
    }

    ~Cuenta() {
        for (auto estado : estados) {
            delete estado;
        }
    }
};

void menu(vector<Cuenta*> &cuentas) {
    while (true) {
        cout << "\nCuentas existentes:\n";
        for (int i = 0; i < cuentas.size(); i++) {
            cout << i << ": ";
            cuentas[i]->mostrarInfo();
        }
        cout << "\nOpciones:\n";
        cout << "1. Seleccionar cuenta y restaurar estado\n";
        cout << "2. Crear nueva cuenta\n";
        cout << "3. Salir\n";
        cout << "Seleccione una opción: ";

        int opcion;
        cin >> opcion;

        if (opcion == 1) {
            cout << "Seleccione una cuenta: ";
            int seleccion;
            cin >> seleccion;
            if (seleccion >= 0 && seleccion < cuentas.size()) {
                cuentas[seleccion]->restaurarEstado();
                cuentas[seleccion]->mostrarInfo();
            } else {
                cout << "Opción inválida." << endl;
            }
        } else if (opcion == 2) {
            string nombre, correo;
            cout << "Ingrese el nombre de la cuenta: ";
            cin >> nombre;
            cout << "Ingrese el correo de la cuenta: ";
            cin >> correo;
            Cuenta* nuevaCuenta = new Cuenta(nombre, correo);
            cuentas.push_back(nuevaCuenta);
            cout << "Nueva cuenta creada y estado guardado." << endl;
        } else if (opcion == 3) {
            break;
        } else {
            cout << "Opción inválida. Intente de nuevo." << endl;
        }
    }
}

int main() {
    vector<Cuenta*> cuentas;

    //Cuentas random
    cuentas.push_back(new Cuenta("Cuenta1", "correo1@example.com"));
    cuentas.push_back(new Cuenta("Cuenta2", "correo2@example.com"));
    cuentas.push_back(new Cuenta("Cuenta3", "correo3@example.com"));

    menu(cuentas);

    for (auto cuenta : cuentas) {
        delete cuenta;
    }

    return 0;
}
