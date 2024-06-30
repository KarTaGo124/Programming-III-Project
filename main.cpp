#include "streaming.cpp"

#include <string>

using namespace std;

int main(){

  Streaming streaming;

  string filename = "/home/leo/Documents/UTEC/Ciclos/3er_ciclo/Programacion_III/2024-I/Proyecto/Proyecto-Progra-3/data.csv";

  cout << "Subiendo peliculas..." << endl;
  streaming.loadMovies(filename);
  cout << "Carga terminada" << endl;
  /*
  //Buscar por subcadenas
  string subcadena;
  cout << "Ingrese nombre de serie o película: ";
  getline(cin, subcadena);
  //Mostrar Id's
  
  unordered_set<int> idEncontrados = streaming.buscarPorSubcadena(subcadena);
  //Imprimir datos de película
  */

  //Buscar por categorias
  streaming.printTags();

  string tag;
  cout << "Ingrese categoria: ";
  getline(cin, tag);

  unordered_set<int> idEncontrados = streaming.buscarPorCategoria(tag);
  streaming.printEncontrados(idEncontrados);
  
}
