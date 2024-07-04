#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Memento {
private:
    string correo;
    string contrasenia;

public:
    Memento(const string &email, const string &password){
    this->correo = email;
    this-> contrasenia = password;
    }
    string getCorreo() const {
        return correo;
    }
    string getContrasenia() const {
        return contrasenia;
    }
};

class Cuenta {
private:
    string correo;
    string contrasenia;
    vector<Memento *> estados;

public:
    Cuenta(const string &email, const string &password){
        this->correo = email;
        this->contrasenia = password;
    }

    void guardarCuenta() {
        estados.push_back(new Memento(correo, contrasenia));
        cout << "Cuenta Guardada" << endl;
    }

    string getCorreo() const {
        return correo;
    }
    string getContrasenia() const {
        return contrasenia;
    }

    ~Cuenta() {
        for (auto estado : estados) {
            delete estado;
        }
    }
};

class Autenticacion {
public:
    virtual bool autenticar(const string &correo, const string &contrasenia) const = 0;
    virtual void agregarCuenta(const string &correo, const string &contrasenia) = 0;
};

// Implementación concreta del sistema de autenticación
class AutenticacionReal : public Autenticacion {
private:
    unordered_map<string, string> usuarios; // Almacena pares de correo y contraseña

public:
    AutenticacionReal() {
        // Usuarios simulados
        usuarios["usuario1@example.com"] = "password1";
    }

    bool autenticar(const string &correo, const string &contrasenia) const override {
        auto it = usuarios.find(correo);
        if (it != usuarios.end() && it->second == contrasenia) {
            cout << "Autenticacion exitosa para: " << correo << endl;
            return true;
        }
        cout << "Autenticacion fallida para: " << correo << endl;
        return false;

    }

    void agregarCuenta(const string &correo, const string &contrasenia) override {
        usuarios[correo] = contrasenia;
    }
};

// Proxy para la autenticación
class ProxyAutenticacion : public Autenticacion {
private:
    AutenticacionReal autenticacionReal;

public:
    bool autenticar(const string &correo, const string &contrasenia) const override {
        // Validar el correo y la contraseña a través del proxy
        return autenticacionReal.autenticar(correo, contrasenia);
    }

    void agregarCuenta(const string &correo, const string &contrasenia) override {
        autenticacionReal.agregarCuenta(correo, contrasenia);
    }
};

int main() {
    Cuenta cuenta("correo1@gmail.com", "contrasena_1");
    ProxyAutenticacion proxy;
    bool autenticacionExitosa = false;

    while (!autenticacionExitosa) {
        cout << "1. Registrarse\n";
        cout << "2. Iniciar sesion\n";
        cout << "3. Salir\n";
        cout << "Elija una opcion: ";

        int opcion;
        cin >> opcion;

        switch (opcion) {
            case 1: {
                string nombre, correo, contrasenia;
                cout << "Ingrese el correo: ";
                cin >> correo;
                cout << "Ingrese la contrasena: ";
                cin >> contrasenia;
                cuenta = Cuenta(correo, contrasenia);
                cuenta.guardarCuenta();
                proxy.agregarCuenta(correo, contrasenia);
                break;
            }
            case 2: {
                string correo, contrasenia;
                cout << "Ingrese el correo: ";
                cin >> correo;
                cout << "Ingrese la contrasena: ";
                cin >> contrasenia;
                if (proxy.autenticar(correo, contrasenia)) {
                    autenticacionExitosa = true;
                }
                break;
            }
            case 3:
                return 0;
            default:
                cout << "Opcion invalida. Por favor, elija una opcion valida. " << endl;
        }
    }
}
