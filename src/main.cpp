#include "streaming.cpp"

#include <string>

using namespace std;

int main() {

    Streaming streaming;

    string filename = "./data/data.csv";

    cout << "Subiendo peliculas..." << endl;
    streaming.loadMovies(filename);
    cout << "Carga terminada" << endl;

    //Buscar por subcadenas
    string subcadena;
    cout << "Ingrese nombre de serie o película: ";
    getline(cin, subcadena);

    // Generar subcadenas
    vector<string> subcadenas = generarSubcadenas(subcadena);

    // Iterar sobre las subcadenas y buscar cada una
    for (const string& s : subcadenas) {
        unordered_set<int> idEncontrados = streaming.buscarPorSubcadena(s);
        streaming.printEncontrados(idEncontrados);
    }

    //Buscar por categorias
    /*
    streaming.printTags();

    string tag;
    cout << "Ingrese categoria: ";
    getline(cin, tag);

    unordered_set<int> idEncontrados = streaming.buscarPorCategoria(tag);
    streaming.printEncontrados(idEncontrados);
    */

}
