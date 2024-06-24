#include <iostream>
#include <unordered_set>

using namespace std;

class Pelicula {
  private:
    string imdb_id; // codigo unico de paícula
    string titulo; // titulo de pelicula
    string sinopsis; // descripcion de pelicula
    unordered_set<string> categorias; // tipo de pelicula
  public:
    Pelicula(){}
    Pelicula(const string& imdb_id, const string& titulo, const string& sinopsis, const unordered_set<string>& categorias):imdb_id(imdb_id), titulo(titulo), sinopsis(sinopsis), categorias(categorias){} 
    
    string getTitulo() const {
      return titulo;
    }

    string getSinopsis() const {
      return sinopsis;
    } 

    unordered_set<string> getCategorias() const {
      return categorias;
    }

    string getImdb_id() const {
      return imdb_id;
    }
};
