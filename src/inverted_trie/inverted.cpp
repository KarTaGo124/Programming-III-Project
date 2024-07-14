#include "nodo.cpp"
#include "../functions.h"

#include <cctype>
#include <unordered_set>


using namespace std;

class InvertedTrie {
private:
    NodoTrie *raiz;

    void insertString(const unordered_set<string> &words, const int &movieId) {
        for (const auto &word: words) {
            for (size_t i = 0; i < word.length(); i++) {
                NodoTrie *nodo = raiz; // Crea nodo
                for (size_t j = i; j < word.length(); j++) {
                    char c = word[j]; // asigan el valor de letra en minuscula
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
    }

public:
    InvertedTrie() : raiz(new NodoTrie()) {}

    void insert(const string &titulo, const string &sinopsis, const int &id) {
        string tituloNormalizado = normalizarTxt(titulo);
        string sinopsisNormalizado = normalizarTxt(sinopsis);
        unordered_set<string> palabrasTitulo = convertSet(tituloNormalizado);
        unordered_set<string> palabrasSinopsis = convertSet(sinopsisNormalizado);
        insertString(palabrasTitulo, id);
        insertString(palabrasSinopsis, id);
    }

    unordered_set<int> buscarPorSubcadena(string subcadena) {
        NodoTrie *nodo = raiz;
        for (const char &c: subcadena) {
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
