#include "inverted_trie/inverted.cpp"
#include "pelicula.cpp"
#include "functions.h"
#include "login/cuenta.h"
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cstdlib>
#include <limits>

using namespace std;

class Streaming {
private:
    unordered_map<int, Pelicula> peliculas;
    InvertedTrie trie;
    unordered_map<string, unordered_set<int>> tagsMap;

    void insertTags(const int &id, const unordered_set<string> &tags) {
        for (const auto &tag : tags) {
            tagsMap[tag].insert(id);
        }
    }

public:
    void loadMovies(const string &filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "No se pudo abrir el archivo: " << filename << endl;
            return;
        }

        string line;
        getline(file, line); // Saltar la primera línea (cabecera)

        int current_id = 1; // Nuevo id de películas

        while (getline(file, line)) {
            Pelicula pelicula = Pelicula::readCSVLine(file, line, current_id);
            peliculas[pelicula.getImdb_id()] = pelicula;
            trie.insert(pelicula.getTitulo(), pelicula.getSinopsis(), pelicula.getImdb_id());
            insertTags(pelicula.getImdb_id(), pelicula.getCategorias());
        }
        file.close();
    }

    vector<pair<int, int>> buscarPorSubcadena(const string &subcadena) {
        string subNormalizado = normalizarTxt(subcadena);
        unordered_set<string> palabras = convertSet(subNormalizado);
        unordered_map<int, int> peliculasScores;

        for (const auto &palabra : palabras) {
            unordered_set<int> temp = trie.buscarPorSubcadena(palabra);
            for (const auto &id : temp) {
                const Pelicula &pelicula = peliculas.at(id);
                int score = 0;
                if (pelicula.getConteoPalabrasTitulo().count(palabra)) {
                    score += pelicula.getConteoPalabrasTitulo().at(palabra) * 3;
                }
                if (pelicula.getConteoPalabrasSinopsis().count(palabra)) {
                    score += pelicula.getConteoPalabrasSinopsis().count(palabra);
                }
                peliculasScores[id] += score;
            }
        }

        vector<pair<int, int>> sortedPeliculas = sorted(peliculasScores);

        return sortedPeliculas;
    }

    unordered_set<int> buscarPorCategoria(const string &tag) {
        return tagsMap[tag];
    }

    void insertLike(Cuenta *cuenta, int currentId) {
        unordered_set<string> tagsTemp;
        for (const auto &pelicula : peliculas) {
            if (pelicula.first == currentId) {
                tagsTemp = pelicula.second.getCategorias();
            }
        }

        for (const auto &tag : tagsTemp) {
            cuenta->agregarLike(tag);
        }
    }

    void printTags(int limit) {
        int count = 0;
        for (const auto &tag : tagsMap) {
            if (count++ == limit) break;
            cout << tag.first << endl;
        }
    }

    void printTitulo(const unordered_set<int> &idPeliculas, int limit) {
        cout << "Se encontraron " << idPeliculas.size() << " películas para elegir: " << endl;
        int count = 0;
        for (const auto &id : idPeliculas) {
            if (count++ == limit) break;
            cout << "ID: " << id << endl;
            cout << "Titulo: " << peliculas[id].getTitulo() << endl;
        }
    }

    void printEncontrados(const vector<pair<int, int>> &idEncontrados, int limit) {
        cout << "Se encontraron " << idEncontrados.size() << " películas para elegir: " << endl;

        for (int i = 0; i < limit && i < idEncontrados.size(); i++) {
            cout << "ID: " << idEncontrados[i].first << endl;
            cout << "Título: " << peliculas[idEncontrados[i].first].getTitulo() << endl;
        }
    }

    void printPelicula(int id) {
        clearTerminal();
        cout << "Titulo: " << peliculas[id].getTitulo() << endl;
        cout << "Sinopsis: " << peliculas[id].getSinopsis() << endl;
    }

    void cargarPeliculas(const string &filename) {
        cout << "Subiendo peliculas..." << endl;
        loadMovies(filename);
        cout << "Carga terminada" << endl;
    }

    void mostrarListaContinuarViendo(const unordered_set<int> &verMasTarde, int limit) {
        if (!verMasTarde.empty()) {
            cout << "Continuar Viendo: " << endl;
            printTitulo(verMasTarde, limit);
        }
    }

    void mostrarListaRecomendadas(const unordered_map<string, int> &likesMap, int limit) {
        if (!likesMap.empty()) {
            cout << "Recomendadas para ti: " << endl;
            vector<pair<string, int>> tagsLikes = sorted(likesMap);
            auto lista = buscarPorCategoria(tagsLikes[0].first);
            printTitulo(lista, limit);
        }
    }

    int obtenerOpcionUsuario(int min, int max) {
        int opcion;
        while (!(cin >> opcion) || opcion < min || opcion > max) {
            cout << "Opción no válida. Intente nuevamente: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return opcion;
    }

    void buscarPorNombre(int &currentId, bool &encontrada, int limit) {
        clearTerminal();
        string subcadena;
        cout << "Ingrese nombre de serie o película: ";
        cin.ignore(); // Ignorar el carácter residual en el buffer de entrada
        getline(cin, subcadena);
        auto idEncontrados = buscarPorSubcadena(subcadena);

        while (!encontrada) {
            clearTerminal();
            printEncontrados(idEncontrados, limit);
            cout << "1. Seleccionar" << endl;
            cout << "2. Ver más" << endl;
            cout << "3. Regresar" << endl;
            cout << "Elegir opción: ";
            int opcion1 = obtenerOpcionUsuario(1, 3);

            if (opcion1 == 1) {
                unordered_set<int> idLista;
                for (int i = 0; i < limit && i < idEncontrados.size(); ++i) {
                    idLista.insert(idEncontrados[i].first);
                }

                int id;
                cout << "Escoger película por ID: ";
                cin >> id;
                if (idLista.find(id) != idLista.end()) {
                    currentId = id;
                    printPelicula(id);
                    encontrada = true;
                } else {
                    cout << "Película no se encuentra entre las mostradas" << endl;
                }
            } else if (opcion1 == 2) {
                limit += 5;
            } else {
                break;
            }
        }
    }

    void buscarPorCategoria(int &currentId, bool &encontrada, int limit) {
        while (!encontrada) {
            clearTerminal();
            printTags(limit);
            cout << "1. Seleccionar" << endl;
            cout << "2. Ver más" << endl;
            cout << "3. Regresar" << endl;
            cout << "Elegir opción: ";
            int opcion2 = obtenerOpcionUsuario(1, 3);

            if (opcion2 == 1) {
                string tag;
                cin.ignore(); // Ignorar el carácter residual en el buffer de entrada
                cout << "Ingrese categoria: ";
                getline(cin, tag);
                auto idEncontrados = buscarPorCategoria(tag);
                limit = 5;

                while (true) {
                    clearTerminal();
                    printTitulo(idEncontrados, limit);
                    cout << "1. Seleccionar" << endl;
                    cout << "2. Ver más" << endl;
                    cout << "3. Regresar" << endl;
                    cout << "Elegir opción: ";
                    int opcion3 = obtenerOpcionUsuario(1, 3);

                    if (opcion3 == 1) {
                        int id;
                        cout << "Escoger película por ID: ";
                        cin >> id;
                        if (ifExist(idEncontrados, id, limit)) {
                            currentId = id;
                            printPelicula(id);
                            encontrada = true;
                        } else {
                            cout << "Película no se encuentra entre las mostradas" << endl;
                        }
                    } else if (opcion3 == 2) {
                        limit += 5;
                    } else {
                        break;
                    }
                }
            } else if (opcion2 == 2) {
                limit += 5;
            } else {
                break;
            }
        }
    }

    void continuarViendo(int &currentId, bool &encontrada, int limit, unordered_set<int> &verMasTarde) {
        while (!encontrada) {
            clearTerminal();
            if (verMasTarde.empty()) {
                cout << "No tienes películas en la lista de ver más tarde." << endl;
                return;
            }
            cout << "Continuar viendo: " << endl;
            printTitulo(verMasTarde, limit);
            cout << "1. Seleccionar" << endl;
            cout << "2. Ver más" << endl;
            cout << "3. Regresar" << endl;
            cout << "Elegir opción: ";
            int opcion4 = obtenerOpcionUsuario(1, 3);

            if (opcion4 == 1) {
                int id;
                cout << "Escoger película por ID: ";
                cin >> id;
                if (ifExist(verMasTarde, id, limit)) {
                    currentId = id;
                    printPelicula(id);
                    encontrada = true;
                } else {
                    cout << "Película no se encuentra entre las mostradas" << endl;
                }
            } else if (opcion4 == 2) {
                limit += 5;
            } else {
                break;
            }
        }
    }

    void seleccionarRecomendada(int &currentId, bool &encontrada, int limit, unordered_map<string, int> &likesMap) {
        while (!encontrada) {
            clearTerminal();
            if (likesMap.empty()) {
                cout << "No tienes películas recomendadas aún." << endl;
                return;
            }
            cout << "Recomendadas para ti: " << endl;
            vector<pair<string, int>> tagsLikes = sorted(likesMap);
            auto lista = buscarPorCategoria(tagsLikes[0].first);
            printTitulo(lista, limit);
            cout << "1. Seleccionar" << endl;
            cout << "2. Ver más" << endl;
            cout << "3. Regresar" << endl;
            cout << "Elegir opción: ";
            int opcion5 = obtenerOpcionUsuario(1, 3);

            if (opcion5 == 1) {
                int id;
                cout << "Escoger película por ID: ";
                cin >> id;
                if (ifExist(lista, id, limit)) {
                    currentId = id;
                    printPelicula(id);
                    encontrada = true;
                } else {
                    cout << "Película no se encuentra entre las mostradas" << endl;
                }
            } else if (opcion5 == 2) {
                limit += 5;
            } else {
                break;
            }
        }
    }

    void gestionarPelicula(int currentId, Cuenta *cuenta) {
        bool volver = false;
        while (!volver) {
            cout << "1. Me gusta" << endl;
            cout << "2. Ver más tarde" << endl;
            cout << "3. Ver ahora" << endl;
            cout << "4. Regresar" << endl;
            cout << "Elegir opción: ";
            int opcion6 = obtenerOpcionUsuario(1, 4);

            if (opcion6 == 1) {
                insertLike(cuenta, currentId);
                volver = true;
            } else if (opcion6 == 2) {
                cuenta->agregarVerMasTarde(currentId);
                volver = true;
            } else if (opcion6 == 3) {
                cuenta->agregarVerAhora(peliculas[currentId].getTitulo());
                volver = true;
            } else {
                volver = true;
            }
        }
    }

    void gestionarVerMasTarde(int currentId, Cuenta *cuenta) {
        bool volver = false;
        while (!volver) {
            cout << "1. Me gusta" << endl;
            cout << "2. Ver ahora" << endl;
            cout << "3. Regresar" << endl;
            cout << "Elegir opción: ";
            int opcion6 = obtenerOpcionUsuario(1, 3);

            if (opcion6 == 1) {
                cuenta->agregarLike(peliculas[currentId].getTitulo());
                volver = true;
            } else if (opcion6 == 2) {
                cuenta->agregarVerAhora(peliculas[currentId].getTitulo());
                volver = true;
            } else {
                volver = true;
            }
        }
    }

    void systemOn(Cuenta *cuenta) {
        string filename = "../data/data.csv";
        cargarPeliculas(filename);

        bool encontrada = false;
        int limit = 5;
        int currentId = 0;

        while (true) {
            int opcion = printMenu();

            switch (opcion) {
                case 1:
                    buscarPorNombre(currentId, encontrada, limit);
                    if (encontrada) gestionarPelicula(currentId, cuenta);
                    break;
                case 2:
                    buscarPorCategoria(currentId, encontrada, limit);
                    if (encontrada) gestionarPelicula(currentId, cuenta);
                    break;
                case 3:
                    mostrarListaContinuarViendo(cuenta->getVerMasTarde(), limit);
                    continuarViendo(currentId, encontrada, limit, cuenta->getVerMasTarde());
                    if (encontrada) gestionarVerMasTarde(currentId, cuenta);
                    break;
                case 4:
                    mostrarListaRecomendadas(cuenta->getLikes(), limit);
                    seleccionarRecomendada(currentId, encontrada, limit, cuenta->getLikes());
                    if (encontrada) gestionarPelicula(currentId, cuenta);
                    break;
                case 5:
                    clearTerminal();
                    cout << "Cerrando sesión..." << endl;
                    exit(0); // Terminar el programa completamente
                default:
                    break;
            }
        }
    }
};
