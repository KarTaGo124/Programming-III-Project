#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

struct Pelicula {
    string imdb_id;
    string title;
    string plot_synopsis;
    unordered_set<string> tags;
};

unordered_set<string> convertSet(const string& txt){
    unordered_set<string> result;
    string temp;
    istringstream ss(txt);
    while (getline(ss, temp, ',')) {
        if (!temp.empty() && isspace(temp.front())) {
            temp.erase(temp.begin());
        }
        result.insert(temp);
    }
    return result;
}

string getNextField(stringstream& ss, bool& inQuotes) {
    string field;
    char c;
    while (ss.get(c)) {
        if (c == '"' && (field.empty() || field.back() != '\\')) {
            inQuotes = !inQuotes;
        } else if (c == ',' && !inQuotes) {
            break;
        } else {
            field += c;
        }
    }
    return field;
}

void cargarPeliculas(const string& filename, vector<Pelicula>& peliculas) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "No se pudo abrir el archivo: " << filename << endl;
        return;
    }

    string line;
    getline(file, line); // Saltar la primera línea (cabecera)

    while (getline(file, line)) {
        stringstream ss(line);
        string imdb_id, title, plot_synopsis, stags;
        bool inQuotes = false;

        imdb_id = getNextField(ss, inQuotes);
        title = getNextField(ss, inQuotes);

        // Leer plot_synopsis
        plot_synopsis = getNextField(ss, inQuotes);
        while (inQuotes) {
            string nextLine;
            if (!getline(file, nextLine)) break;
            ss.clear();
            ss.str(nextLine);
            plot_synopsis += "\n" + getNextField(ss, inQuotes);
        }

        // Leer tags
        stags = getNextField(ss, inQuotes);
        while (inQuotes) {
            string nextLine;
            if (!getline(file, nextLine)) break;
            ss.clear();
            ss.str(nextLine);
            stags += "\n" + getNextField(ss, inQuotes);
        }

        // Quitar las comillas del plot_synopsis y tags
        if (!plot_synopsis.empty() && plot_synopsis.front() == '"') plot_synopsis.erase(plot_synopsis.begin());
        if (!plot_synopsis.empty() && plot_synopsis.back() == '"') plot_synopsis.pop_back();
        if (!stags.empty() && stags.front() == '"') stags.erase(stags.begin());
        if (!stags.empty() && stags.back() == '"') stags.pop_back();

        unordered_set<string> tags = convertSet(stags);

        peliculas.push_back({imdb_id, title, plot_synopsis, tags});
    }
    file.close();
}

int main(){
    vector<Pelicula> peliculas;

    string filename = "/home/leo/Documents/UTEC/Ciclos/3er_ciclo/Programacion_III/2024-I/Final/data.csv";

    cargarPeliculas(filename, peliculas);

    cout << peliculas.size() << endl;


    // Imprimir las películas cargadas (opcional)
    for (const auto& pelicula : peliculas) {
        //if(pelicula.plot_synopsis == "tt1270479"){
        cout << "ID: " << pelicula.imdb_id << ", Title: " << pelicula.title
             << ", Synopsis: " << pelicula.plot_synopsis << ", Tags: " << pelicula.tags.size() << endl;
        //}
    }
    return 0;
}
