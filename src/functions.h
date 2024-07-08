// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <unordered_set>

std::string normalizarTxt(std::string str);
std::unordered_set<std::string> convertSet(const std::string &txt);
std::string toLower(const std::string& str);

#endif // FUNCTIONS_H

