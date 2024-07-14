// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>

std::string normalizarTxt(std::string str);
std::unordered_set<std::string> convertSet(const std::string &txt);
std::string toLower(const std::string& str);
//std::string printContainer(std::unordered_set<std::string> container);
bool ifExist(const std::unordered_set<int>& ids, int id, int limit);
void clearTerminal();
int printMenu();


template<typename T1, typename T2>
std::vector<std::pair<T1, T2>> sorted(const std::unordered_map<T1, T2>& containerIn){
    std::vector<std::pair<T1,T2>> containerOut(containerIn.begin(), containerIn.end());
    sort(containerOut.begin(), containerOut.end(), [](const std::pair<T1, T2>& a, const std::pair<T1, T2>& b){return a.second > b.second;});

    return containerOut;
}

#endif // FUNCTIONS_H

