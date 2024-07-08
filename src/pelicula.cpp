#include "functions.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class Pelicula {
private:
    int imdb_id; // codigo unico de paícula
    string titulo; // titulo de pelicula
    string sinopsis; // descripcion de pelicula
    unordered_set<string> categorias; // tipo de pelicula
    unordered_map<string, int> conteoPalabrasTitulo;
    unordered_map<string, int> conteoPalabraSinopsis;

    static unordered_set<string> convertSet(const string &txt) {
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

    static unordered_map<string, int> countWords(string txt){
      unordered_map<string, int> wordCount;
      string lowerTxt = toLower(txt);
      string temp;
      istringstream ss(lowerTxt);
      while(ss >> temp){ 
        wordCount[temp]++;
      }
      return wordCount;
    }

    static string getNextField(stringstream &ss, bool &inQuotes) {
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

public:
    Pelicula() {}

    Pelicula(int imdb_id, const string &titulo, const string &sinopsis, const unordered_set<string> &categorias)
            : imdb_id(imdb_id), titulo(titulo), sinopsis(sinopsis), categorias(categorias) {
              conteoPalabrasTitulo = countWords(titulo);
              conteoPalabraSinopsis = countWords(sinopsis);
            }

    string getTitulo() const {
        return titulo;
    }

    string getSinopsis() const {
        return sinopsis;
    }

    unordered_set<string> getCategorias() const {
        return categorias;
    }

    int getImdb_id() const {
        return imdb_id;
    }

    unordered_map<string, int> getConteoPalabrasTitulo() const{
      return conteoPalabrasTitulo;
    }

    unordered_map<string, int> getConteoPalabrasSinopsis() const{
      return conteoPalabraSinopsis;
    }

    static Pelicula readCSVLine(ifstream &file, const string &line, int &current_id) {
        stringstream ss(line);
        string title, plot_synopsis, stags;
        bool inQuotes = false;

        getNextField(ss, inQuotes);
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

        return Pelicula(current_id++, title, plot_synopsis, tags);
    }
};
