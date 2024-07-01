#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class NodoTrie {
private:
    unordered_map<char, NodoTrie *> hijos;
    unordered_set<int> imdb_ids; // Almacena set de ids

public:

    NodoTrie() = default;

    void setHijo(const char &c, NodoTrie *nodo) {
        //Se crea un nodo y se le asigna el último char
        hijos[c] = nodo;
    }

    NodoTrie *getHijo(char c) {
        if (hijos.find(c) != hijos.end()) // Busca el hijo del char c                                        //
            return hijos[c]; // Si lo encuentra trae el hijo
        return nullptr; // Caso contrario nullptr
    }

    void agregarPeliculaId(const int &imdb_id) {
        imdb_ids.insert(imdb_id);
    }

    const unordered_set<int> &getIds() const {
        return imdb_ids;
    }

    ~NodoTrie() {
        for (auto &[c, hijo]: hijos) {
            delete hijo;
        }
    }

};
