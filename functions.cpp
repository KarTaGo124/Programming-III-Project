#include<iostream>
#include<unordered_map>

using namespace std;

string normalizarTxt(string str){
  unordered_map<char, char> mapNormalizado = {
    //Usar caracteres Unicode para reconocer caracteres especiales como char
        {'\xE1', 'a'}, {'\xE9', 'e'}, {'\xED', 'i'}, {'\xF3', 'o'}, {'\xFA', 'u'},
        {'\xC1', 'A'}, {'\xC9', 'E'}, {'\xCD', 'I'}, {'\xD3', 'O'}, {'\xDA', 'U'},
        {'\xF1', 'n'}, {'\xD1', 'N'}
    };

  string txtNormalizado;

  for(char c: str){
    if(mapNormalizado.find(c) != mapNormalizado.end()){
      txtNormalizado += mapNormalizado[c];
    }
    else if(isalnum(c) || isspace(c)){
      txtNormalizado += c;
    }
  }

  return txtNormalizado;
}



