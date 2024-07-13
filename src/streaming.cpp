#include "inverted_trie/inverted.cpp"
#include "pelicula.cpp"
#include "functions.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

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
            //generar un set de todas las palabras en el titulo y Sinopsis
            trie.insert(pelicula.getTitulo(), pelicula.getSinopsis(), pelicula.getImdb_id());
            insertTags(pelicula.getImdb_id(), pelicula.getCategorias());
        }
        file.close();
    }

    vector<pair<int,int>> buscarPorSubcadena(const string &subcadena) {
      string subNormalizado = normalizarTxt(subcadena);
      unordered_set<string> palabras = convertSet(subNormalizado);
      unordered_map<int, int> peliculasScores;
      
      for(const auto& palabra: palabras){
        unordered_set<int> temp = trie.buscarPorSubcadena(palabra);
        for(const auto& id: temp){
          const Pelicula& pelicula = peliculas.at(id);
          int score = 0;
          if(pelicula.getConteoPalabrasTitulo().count(palabra)){
            score += pelicula.getConteoPalabrasTitulo().at(palabra) * 3;
          }
          if(pelicula.getConteoPalabrasSinopsis().count(palabra)){
            score += pelicula.getConteoPalabrasSinopsis().count(palabra);
          }
          peliculasScores[id] += score;
        }
      }
      
      vector<pair<int,int>> sortedPeliculas(peliculasScores.begin(), peliculasScores.end());
      sort(sortedPeliculas.begin(), sortedPeliculas.end(), [](const pair<int, int>& a, const pair<int, int>& b){return a.second > b.second;});

      return sortedPeliculas;
    }

    unordered_set<int> buscarPorCategoria(const string &tag) {
        return tagsMap[tag];
    }

    void printTags() {
        for (const auto &tag: tagsMap) {
            cout << tag.first << endl;
        }
    }

    void printEncontrados(const vector<pair<int,int>> &idEncontrados) {
        cout << "Películas encontadas: " << endl;
        
        int count = 0;

        for (const auto &id: idEncontrados) {
            if(count == 50) break;
            cout << "ID: " << id.first << endl;
            cout << "Título: " << peliculas[id.first].getTitulo() << endl;
            cout << "Conteo importancia: " << id.second << endl;
            count++;
            //cout << "Sinopsis: " << peliculas[id].getSinopsis() << endl;
            //cout << "Categorias: " << printContainer(peliculas[id].getCategorias()) << endl;
        }

        cout << "Cantidad: " << idEncontrados.size() << endl;
    }
};

