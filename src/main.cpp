#include "streaming.cpp"
#include "Login/credenciales.h"

#include <string>

using namespace std;

int main() {
  //Cuenta cuenta("correo1@gmail.com", "contrasena_1");
  ProxyAutenticacion proxy;
  bool autenticacionExitosa = false;

  while (!autenticacionExitosa) {
    cout << "1. Registrarse\n";
    cout << "2. Iniciar sesion\n";
    cout << "3. Salir\n";
    cout << "Elija una opcion: ";

    int opcion;
    cin >> opcion;
    cin.ignore();  // Ignorar el salto de línea residual en el buffer

    switch (opcion) {
      case 1: {
        string correo, contrasenia;
        cout << "Ingrese el correo: ";
        getline(cin, correo);
        cout << "Ingrese la contrasena: ";
        getline(cin, contrasenia);
        Cuenta cuenta = Cuenta(correo, contrasenia);
        cuenta.guardarCuenta();
        proxy.agregarCuenta(correo, contrasenia);
        break;
      }
      
      case 2: {
        string correo, contrasenia;
        cout << "Ingrese el correo: ";
        getline(cin, correo);
        cout << "Ingrese la contrasena: ";
        getline(cin, contrasenia);
        
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

  if(autenticacionExitosa) {
      Streaming streaming;

      streaming.systemOn();
  }
}
