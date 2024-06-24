#include <iostream>
#include <unordered_map>
#include <set>

using namespace std;

class NodoTrie {
  private:
    unordered_map<char, NodoTrie*> hijos;
    set<string> peliculas;
  public:
    NodoTrie() = default;
    ~NodoTrie(){
      for (auto& [c, hijo] : hijos){
          delete hijo;
      }
    }

    NodoTrie* getHijo(char c){
      if (hijos.find(c) != hijos.end()) // Busca el hijo del char c                                        //
        return hijos[c]; // Si lo encuentra trae el hijo
      return nullptr; // Caso contrario nullptr
    }

    void setNodo(char c, NodoTrie* nodo){
      hijos[c] = nodo;
    }

    void agregarPelicula(const string& pelicula){
      peliculas.insert(pelicula);
    }

    const set<string>& getPeliculas() const {
      return peliculas;

    }
};
