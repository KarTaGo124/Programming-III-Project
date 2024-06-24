#include "inverted.cpp"
#include "pelicula.cpp"

#include <sstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Streaming {
  private:
   InvertedTrie* trie;
   unordered_map<string, vector<string>> categorias;
   unordered_set<string> masTarde;
   unordered_map<string, vector<Pelicula>> likes;

   void agregarCategorias(const Pelicula& pelicula){
     istringstream ss(pelicula.); // Problema: espera string, retorn unordered_set
     string categoria;
     while (getline(ss, categoria, ',')){
       categorias[categoria].push_back(pelicula.getImdb_id());
     }
   }

  public:
    
  
   ~Streaming(){
     delete trie;
   }
};
