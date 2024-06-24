#include "nodo.cpp"

#include <cctype>
#include <vector>

using namespace std;

class InvertedTrie{
  private:
    NodoTrie* raiz;

    void insertarString(const string& str,const string& pelicula){
      for (size_t i = 0; i < str.length(); i++) {
       NodoTrie* nodo = raiz; // Crea nodo
       for (size_t j = i; j < str.length(); j++) {
         char c = tolower(str[j]); // asigan el valor de letra
         NodoTrie* hijo = nodo->getHijo(c); // asigna el valor de hijo
         if(!hijo){ // en le caso no exista char hijo
           hijo = new NodoTrie(); // crea un nuevo nodo hijo
           nodo->setNodo(c,hijo); // coloca el valor del último char en el nodo
         }
         nodo = hijo; // nodo apunta al hijo
         nodo->agregarPelicula(pelicula); // agrega pelicula en set de peliculas
       }
      }
    }

  public:
    InvertedTrie(): raiz(new NodoTrie()){}

    void insertar(const string& titulo, const string& sinopsis){
      insertarString(titulo, titulo);
      insertarString(sinopsis, titulo);
    }

    template<typename T> // Permite trabajar con la clase películas Pelicula y testear con strings
    vector<T> buscarPorSubcadena(const string& subcadena){
      NodoTrie* nodo = raiz;
      for(const char& c: subcadena){
        nodo = nodo->getHijo(c);
        if(!nodo)
          return {};
      }
      return vector<T>(nodo->getPeliculas().begin(),nodo->getPeliculas().end());
    }

    ~InvertedTrie(){
      delete raiz;
    }
};
