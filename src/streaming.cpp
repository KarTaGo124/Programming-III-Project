#include "inverted_trie/inverted.cpp"
#include "pelicula.cpp"
#include "functions.h"

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <cstdlib>

using namespace std;

class Streaming {
private:
    unordered_map<int, Pelicula> peliculas;
    InvertedTrie trie;
    unordered_map<string, unordered_set<int>> tagsMap;
    unordered_set<int> verMasTarde;
    unordered_map<string, int> likesMap;

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
      
      vector<pair<int,int>> sortedPeliculas = sorted(peliculasScores);
      //vector<pair<int,int>> sortedPeliculas(peliculasScores.begin(), peliculasScores.end());
      //sort(sortedPeliculas.begin(), sortedPeliculas.end(), [](const pair<int, int>& a, const pair<int, int>& b){return a.second > b.second;});

      return sortedPeliculas;
    }

    unordered_set<int> buscarPorCategoria(const string &tag) {
        return tagsMap[tag];
    }

    void insertLike(int currentId){
      unordered_set<string> tagsTemp; 
      for(const auto& pelicula: peliculas){
        if(pelicula.first == currentId){
        tagsTemp = pelicula.second.getCategorias();
        }
      }

      for(const auto& tag: tagsTemp){
        likesMap[tag]++;
      }
    }

    void printTags(int limit) {
        for (const auto& tag: tagsMap) {
          if(limit-- == 0) break;
          cout << tag.first << endl;
        }
    }

    void printTitulo(const unordered_set<int>& idPeliculas, int limit){
      for(const auto& id: idPeliculas){
        if(limit-- == 0) break;
        cout << "ID: " << id << endl;
        cout << "Titulo: " << peliculas[id].getTitulo() << endl;
      }
    }

    void printEncontrados(const vector<pair<int,int>> &idEncontrados, int limit) {
        cout << "Películas o series para elegir: " << endl;

        for (int i  = 0; i < limit; i++) {
            cout << "ID: " << idEncontrados[i].first << endl;
            cout << "Título: " << peliculas[idEncontrados[i].first].getTitulo() << endl;
            cout << "Conteo importancia: " << idEncontrados[i].second << endl;
        }
        cout << "Cantidad: " << idEncontrados.size() << endl;
    }

    void printPelicula(int id){
      clearTerminal();
      cout << "Titulo: " << peliculas[id].getTitulo() << endl;
      cout << "Sinopsis: " << peliculas[id].getSinopsis() << endl;
    } 

    void systemOn(){
      string filename = "/home/leo/Documents/UTEC/Ciclos/3er_ciclo/Programacion_III/2024-I/Proyecto/Proyecto-Progra-3/data/data.csv";
      
      cout << "Subiendo peliculas..." << endl;
      loadMovies(filename);
      cout << "Carga terminada" << endl;

      bool encontrada = false;
      int limit = 5;
      int currentId;

      if(!verMasTarde.empty()){
        cout << "Continuar Viendo: " << endl;
        printTitulo(verMasTarde, limit);
      }

      int opcion = printMenu(); 

      if(opcion == 1){
        //Buscar por subcadenas
        clearTerminal();
        string subcadena;
        cout << "Ingrese nombre de serie o película: ";
        cin.ignore();
        getline(cin, subcadena);

        cout << subcadena << endl;

        vector<pair<int,int>> idEncontrados = buscarPorSubcadena(subcadena);
      
        while(!encontrada){
          clearTerminal();
          
          printEncontrados(idEncontrados,limit);

          int opcion1;
          cout << "1. Elegir película" << endl;
          cout << "2. Ver mas" << endl;
          cout << "Elegir opción: "; cin >> opcion1;
          
          if(opcion1 == 1){
            unordered_set<int> idLista;
            for(int i = 0; i < limit; i++){
              idLista.insert(idEncontrados[i].first);
            }

            int id;
            cout << "Escoger película por ID: "; cin >> id;
            if(idLista.find(id) != idLista.end()){
              currentId = id;
              printPelicula(id);
              encontrada = true;
            }
            else
              cout << "Película no se encuentra entre las mostradas" << endl;
          }
          else if(opcion1 == 2){
            limit += 5;
          }
        }
      }
      else if(opcion == 2){

        while(!encontrada){
          clearTerminal();

          printTags(limit);
          
          int opcion2;
          cout << "1. Elegir categoría" << endl;
          cout << "2. Ver más" << endl;
          cout << "Elegir opcion: "; cin >> opcion2;

          if(opcion2 == 1){

            string tag;
            cout << "Ingrese categoria: ";
            cin.ignore();
            getline(cin, tag);

            cout << tag << endl;

            unordered_set<int> idEncontrados = buscarPorCategoria(tag);
            limit = 5;
          
            while(!encontrada){
              clearTerminal();
              
              printTitulo(idEncontrados, limit);

              int opcion3;
              cout << "1. Elegir pelicula" << endl;
              cout << "2. Ver más" << endl;
              cout << "Elegir opcion: "; cin >> opcion3;

              if(opcion3 == 1){
                int id;
                cout << "Escoger película por ID: "; cin >> id;
                if(ifExist(idEncontrados, id, limit)){
                  currentId = id;
                  printPelicula(id);
                  encontrada = true;
                }
                else
                 cout << "Película no se encuentra entre las mostradas" << endl; 
              }
              else if(opcion3 == 2){
                limit += 5;
              }
            }
          }
          else if(opcion2 == 2){
            limit += 5;
          }
        }
      }

      else if(opcion == 3){
        while(!encontrada){
          clearTerminal();

          cout << "Continuar viendo: " << endl;
          printTitulo(verMasTarde, limit);

          int opcion4;
          cout << "1. Elegir pelicula" << endl;
          cout << "2. Ver más" << endl;
          cout << "Elegir opcion: "; cin >> opcion4;

          if(opcion4 == 1){
            int id;
            cout << "Escoger película por ID: "; cin >> id;
            if(ifExist(verMasTarde, id, limit)){
              currentId = id;
              printPelicula(id);
              encontrada = true;
            }
            else
              cout << "Película no se encuentra entre las mostradas" << endl; 
          }
          else if(opcion4 == 2){
            limit += 5;
          }
        }
      }
      
      int opcion5;
      do{
        cout << "1. Me gusta" << endl;
        cout << "2. Ver más tarde" << endl;
        cin >> opcion5;
      }while(opcion5 != 1 || opcion5 != 2);

      if(opcion5 == 1){
        insertLike(currentId);
      }
      else if(opcion5 == 2){
        verMasTarde.insert(currentId);
      }
    }
};

