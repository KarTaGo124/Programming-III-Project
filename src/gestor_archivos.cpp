#include "gestor_archivos.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

GestorArchivos* GestorArchivos::instancia = nullptr;

GestorArchivos* GestorArchivos::obtenerInstancia() {
    if (instancia == nullptr) {
        instancia = new GestorArchivos();
    }
    return instancia;
}

void GestorArchivos::guardarCuentas(const GestorCuentas &cuentas) {
    const auto &todasLasCuentas = cuentas.obtenerTodasLasCuentas();

    // Leer todas las líneas del archivo existente
    vector<string> lineas;
    ifstream archivoLectura("../archivos/cuentas.txt");
    string linea;
    while (getline(archivoLectura, linea)) {
        lineas.push_back(linea);
    }
    archivoLectura.close();

    // Abrir el archivo en modo de escritura
    ofstream archivo("../archivos/cuentas.txt");
    for (const auto &pair : todasLasCuentas) {
        auto cuenta = pair.second;
        bool cuentaActualizada = false;

        // Buscar y actualizar la línea correspondiente al correo de la cuenta
        for (auto &linea : lineas) {
            if (linea.find("Correo: " + cuenta->getCorreo()) != string::npos) {
                stringstream nuevaLinea;
                nuevaLinea << "Correo: " << cuenta->getCorreo() << " Contrasenia: " << cuenta->getContrasenia();

                // Guardar ver más tarde
                nuevaLinea << " VerMasTarde:";
                for (auto id : cuenta->getVerMasTarde()) {
                    nuevaLinea << id << ",";
                }

                // Guardar likes
                nuevaLinea << " Likes:";
                for (auto &like : cuenta->getLikes()) {
                    nuevaLinea << like.first << ":" << like.second << ",";
                }

                linea = nuevaLinea.str();
                cuentaActualizada = true;
                break;
            }
        }

        // Si la cuenta no se encontró en el archivo, agregarla al final
        if (!cuentaActualizada) {
            stringstream nuevaLinea;
            nuevaLinea << "Correo: " << cuenta->getCorreo() << " Contrasenia: " << cuenta->getContrasenia();

            // Guardar ver más tarde
            nuevaLinea << " VerMasTarde:";
            for (auto id : cuenta->getVerMasTarde()) {
                nuevaLinea << id << ",";
            }

            // Guardar likes
            nuevaLinea << " Likes:";
            for (auto &like : cuenta->getLikes()) {
                nuevaLinea << like.first << ":" << like.second << ",";
            }

            lineas.push_back(nuevaLinea.str());
        }
    }

    // Escribir todas las líneas al archivo
    for (const auto &linea : lineas) {
        archivo << linea << endl;
    }
    archivo.close();
}

void GestorArchivos::cargarCuentas(GestorCuentas &cuentas) {
    ifstream archivo("../archivos/cuentas.txt");
    string correo, contrasenia, verMasTarde, likes;
    string line;

    while (getline(archivo, line)) {
        stringstream ss(line);
        string temp;
        ss >> temp >> correo >> temp >> contrasenia;

        Cuenta *cuenta = new Cuenta(correo, contrasenia);

        // Leer ver más tarde
        ss >> verMasTarde;
        if (verMasTarde.find("VerMasTarde:") == 0) {
            verMasTarde = verMasTarde.substr(12); // Remover "VerMasTarde:"
            stringstream ssVerMasTarde(verMasTarde);
            string id;
            while (getline(ssVerMasTarde, id, ',')) {
                if (!id.empty()) {
                    cuenta->agregarVerMasTarde(stoi(id));
                }
            }
        }

        // Leer likes
        ss >> likes;
        if (likes.find("Likes:") == 0) {
            likes = likes.substr(6); // Remover "Likes:"
            stringstream ssLikes(likes);
            string like;
            while (getline(ssLikes, like, ',')) {
                if (!like.empty()) {
                    size_t sep = like.find(':');
                    string tag = like.substr(0, sep);
                    int count = stoi(like.substr(sep + 1));
                    cuenta->getLikes()[tag] = count;
                }
            }
        }

        cuentas.agregarCuenta(correo, contrasenia);
    }
    archivo.close();
}
