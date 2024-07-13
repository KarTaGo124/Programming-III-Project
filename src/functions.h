// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <unordered_set>

std::string normalizarTxt(std::string str);
std::unordered_set<std::string> convertSet(const std::string &txt);
std::string toLower(const std::string& str);
//std::string printContainer(std::unordered_set<std::string> container);
bool ifExist(const std::unordered_set<int> ids, int id, int limit);
void clearTerminal();
int printMenu();

#endif // FUNCTIONS_H

