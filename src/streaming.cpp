#include "inverted_trie/inverted.cpp"
#include "pelicula.cpp"

#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

template<typename T>
string printContainer(unordered_set<T> container) {
    string txt;
    int sz = container.size() - 1;
    for (auto it = container.begin(); it != container.end(); it++) {
        txt += *it;
        if (sz != 0) {
            txt += ", ";
            sz--;
        }
    }
    return txt;
}


class Streaming {
private:
    unordered_map<int, Pelicula> peliculas;
    InvertedTrie trie;
    unordered_map<string, unordered_set<int>> tagsMap;

    void insertTags(const int &id, const unordered_set<string> &tags) {
        for (const auto &tag: tags) {
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

    unordered_set<int> buscarPorSubcadena(const string &subcadena) {
        return trie.buscarPorSubcadena(subcadena);
    }

    unordered_set<int> buscarPorCategoria(const string &tag) {
        return tagsMap[tag];
    }

    void printTags() {
        for (const auto &tag: tagsMap) {
            cout << tag.first << endl;
        }
    }

    void printEncontrados(const unordered_set<int> &idEncontrados) {
        cout << "Películas encontadas: " << endl;

        for (const auto &id: idEncontrados) {
            cout << "Título: " << peliculas[id].getTitulo() << endl;
            //cout << "Sinopsis: " << peliculas[id].getSinopsis() << endl;
            cout << "Categorias: " << printContainer(peliculas[id].getCategorias()) << endl;
        }

        cout << "Cantidad: " << idEncontrados.size() << endl;
    }
};

