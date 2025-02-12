#include "functions.h"
#include <cctype>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <sstream>
#include <algorithm>
#include <string>

using namespace std;

string toLower(const string &str) {
    string txt = str;
    transform(txt.begin(), txt.end(), txt.begin(), [](unsigned char c) { return tolower(c); });
    return txt;
}

string normalizarTxt(string str) {
    unordered_map<char, char> mapNormalizado = {
            // Usar caracteres Unicode para reconocer caracteres especiales como char
            {'\xE1', 'a'},
            {'\xE9', 'e'},
            {'\xED', 'i'},
            {'\xF3', 'o'},
            {'\xFA', 'u'},
            {'\xC1', 'a'},
            {'\xC9', 'e'},
            {'\xCD', 'i'},
            {'\xD3', 'o'},
            {'\xDA', 'u'},
            {'\xF1', 'n'},
            {'\xD1', 'n'}
    };

    string txtNormalizado;

    for (char c : str) {
        if (mapNormalizado.find(c) != mapNormalizado.end()) {
            txtNormalizado += mapNormalizado[c];
        } else if (isalnum(c) || isspace(c)) {
            txtNormalizado += tolower(c);
        }
    }

    return txtNormalizado;
}

unordered_set<string> convertSet(const string &txt) {
    unordered_set<string> result;
    string temp;
    istringstream ss(txt);
    while (getline(ss, temp, ' ')) {
        if (!temp.empty() && isspace(temp.front())) {
            temp.erase(temp.begin());
        }
        result.insert(temp);
    }
    return result;
}

bool ifExist(const unordered_set<int> &ids, int id, int limit) {
    for (auto it = ids.begin(); it != ids.end() && limit > 0; ++it) {
        if (*it == id) return true;
        --limit;
    }
    return false;
}

int printMenu() {
    int opcion;
    do {
        cout << "1. Buscar por nombre " << endl;
        cout << "2. Buscar por categoría " << endl;
        cout << "3. Explorar mi lista de películas y series " << endl;
        cout << "4. Explorar mi lista de recomendados" << endl;
        cout << "5. Cerrar sesión" << endl;
        cout << "Elegir entre las opciones: ";
        cin >> opcion;
        cin.ignore();
    } while (opcion < 1 || opcion > 5);

    return opcion;
}
