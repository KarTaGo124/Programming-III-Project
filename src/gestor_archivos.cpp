#include "gestor_archivos.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

GestorArchivos* GestorArchivos::instancia = nullptr;

void GestorArchivos::cargarCuentas(GestorCuentas &cuentas) {
    ifstream archivo("../archivos/cuentas.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string temp, correo, contrasenia;

        // Leer correo
        ss >> temp >> correo;

        // Leer contraseña
        ss >> temp >> contrasenia;

        // Crear o actualizar cuenta
        if (cuentas.obtenerCuenta(correo) == nullptr) {
            cuentas.agregarCuenta(correo, contrasenia);
        }
    }
    archivo.close();
}

void GestorArchivos::cargarCuenta(Cuenta &cuenta) {
    ifstream archivo("../archivos/cuentas.txt");
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string temp, correo, contrasenia;

        // Leer correo
        ss >> temp >> correo;
        // Leer contraseña
        ss >> temp >> contrasenia;

        if (correo == cuenta.getCorreo() && contrasenia == cuenta.getContrasenia()) {

            // Leer VerMasTarde
            string verMasTarde;
            ss >> verMasTarde;
            if (verMasTarde.find("VerMasTarde:") == 0) {
                verMasTarde = verMasTarde.substr(12); // Remover "VerMasTarde:"
                stringstream ssVerMasTarde(verMasTarde);
                string id;
                while (getline(ssVerMasTarde, id, ',')) {
                    if (!id.empty()) {
                        try {
                            int idNum = stoi(id);
                            cuenta.agregarVerMasTarde(idNum);
                        } catch (const invalid_argument &e) {
                            cerr << "Error al convertir id '" << id << "' a entero: " << e.what() << endl;
                        } catch (const out_of_range &e) {
                            cerr << "Error: id '" << id << "' fuera de rango: " << e.what() << endl;
                        }
                    }
                }
            }

            // Leer Likes
            string likes;
            ss >> likes;
            if (likes.find("Likes:") == 0) {
                likes = likes.substr(6); // Remover "Likes:"
                stringstream ssLikes(likes);
                string like;
                while (getline(ssLikes, like, ',')) {
                    if (!like.empty()) {
                        size_t sep = like.rfind(':'); // Buscar el último ':'
                        if (sep != string::npos) {
                            string tag = like.substr(0, sep);
                            string countStr = like.substr(sep + 1);
                            try {
                                int count = stoi(countStr);
                                cuenta.getLikes()[tag] += count; // Acumular likes en lugar de sobrescribir
                            } catch (const invalid_argument &e) {
                                cerr << "Error al convertir count '" << countStr << "' a entero: " << e.what() << endl;
                            } catch (const out_of_range &e) {
                                cerr << "Error: count '" << countStr << "' fuera de rango: " << e.what() << endl;
                            }
                        } else {
                            cerr << "Formato invalido de like: " << like << endl;
                        }
                    }
                }
            }
            break; // Encontramos la cuenta, podemos salir del bucle
        }
    }
    archivo.close();
}

void GestorArchivos::guardarCuenta(Cuenta &cuenta) {
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
    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo para escribir." << endl;
        return;
    }

    bool cuentaActualizada = false;

    // Buscar y actualizar la línea correspondiente al correo de la cuenta
    for (auto &linea : lineas) {
        if (linea.find("Correo: " + cuenta.getCorreo()) != string::npos) {
            stringstream nuevaLinea;
            nuevaLinea << "Correo: " << cuenta.getCorreo() << " Contrasenia: " << cuenta.getContrasenia();

            // Guardar ver más tarde
            nuevaLinea << " VerMasTarde:";
            for (auto id : cuenta.getVerMasTarde()) {
                nuevaLinea << id << ",";
            }

            // Guardar likes
            nuevaLinea << " Likes:";
            for (auto &like : cuenta.getLikes()) {
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
        nuevaLinea << "Correo: " << cuenta.getCorreo() << " Contrasenia: " << cuenta.getContrasenia();

        // Guardar ver más tarde
        nuevaLinea << " VerMasTarde:";
        for (auto id : cuenta.getVerMasTarde()) {
            nuevaLinea << id << ",";
        }

        // Guardar likes
        nuevaLinea << " Likes:";
        for (auto &like : cuenta.getLikes()) {
            nuevaLinea << like.first << ":" << like.second << ",";
        }

        lineas.push_back(nuevaLinea.str());
    }

    // Escribir todas las líneas al archivo
    for (const auto &linea : lineas) {
        archivo << linea << endl;
    }
    archivo.close();
}
