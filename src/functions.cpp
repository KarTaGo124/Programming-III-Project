#include<iostream>
#include<unordered_map>
#include <vector>
#include <string>
using namespace std;

vector<string> generarSubcadenas(string input) {
    vector<string> subcadenas;
    subcadenas.push_back(input); // Agregamos la cadena completa al principio

    size_t pos;
    while ((pos = input.find_last_of(' ')) != string::npos) {
        input = input.substr(0, pos); // Quitamos la última palabra
        subcadenas.push_back(input); // Agregamos la nueva subcadena
    }

    return subcadenas;
}

string normalizarTxt(string str) {
    unordered_map<char, char> mapNormalizado = {
            //Usar caracteres Unicode para reconocer caracteres especiales como char
            {'\xE1', 'a'},
            {'\xE9', 'e'},
            {'\xED', 'i'},
            {'\xF3', 'o'},
            {'\xFA', 'u'},
            {'\xC1', 'A'},
            {'\xC9', 'E'},
            {'\xCD', 'I'},
            {'\xD3', 'O'},
            {'\xDA', 'U'},
            {'\xF1', 'n'},
            {'\xD1', 'N'}
    };

    string txtNormalizado;

    for (char c: str) {
        if (mapNormalizado.find(c) != mapNormalizado.end()) {
            txtNormalizado += mapNormalizado[c];
        } else if (isalnum(c) || isspace(c)) {
            txtNormalizado += c;
        }
    }

    return txtNormalizado;
}



