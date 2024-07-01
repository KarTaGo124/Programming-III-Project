#include "nodo.cpp"
#include "../functions.cpp"

#include <cctype>
#include <vector>
#include <unordered_set>

using namespace std;

class InvertedTrie {
private:
    NodoTrie *raiz;

    void insertString(const string &str, const int &movieId) {
        string strNormalizado = normalizarTxt(str);
        for (size_t i = 0; i < strNormalizado.length(); i++) {
            NodoTrie *nodo = raiz; // Crea nodo
            for (size_t j = i; j < strNormalizado.length(); j++) {
                char c = tolower(strNormalizado[j]); // asigan el valor de letra en minuscula
                NodoTrie *hijo = nodo->getHijo(c); // si existe -> asigna el nodo de hijo o nullptr
                if (!hijo) { // en el caso sea nullptr
                    hijo = new NodoTrie();
                    nodo->setHijo(c, hijo);
                }
                nodo = hijo; // nodo apunta al hijo
                nodo->agregarPeliculaId(movieId); // agrega id de película en el set para ese nodo
            }
        }
    }

public:
    InvertedTrie() : raiz(new NodoTrie()) {}

    void insert(const string &titulo, const string& sinopsis, const int &id) {
        insertString(titulo, id);
        //insertString(sinopsis, id); // explota al cargar las sinopsis
    }

    unordered_set<int> buscarPorSubcadena(string subcadena) {
        string subNormalizado = normalizarTxt(subcadena);
        NodoTrie *nodo = raiz;
        for (const char &c: subNormalizado) {
            nodo = nodo->getHijo(c);
            if (!nodo)
                return {};
        }
        return unordered_set<int>(nodo->getIds().begin(), nodo->getIds().end());
    }

    ~InvertedTrie() {
        delete raiz;
    }
};
