// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

string normalizarTxt(string str);

unordered_set<string> convertSet(const string &txt);

string toLower(const string &str);

bool ifExist(const unordered_set<int> &ids, int id, int limit);

void clearTerminal();

int printMenu();

template<typename T1, typename T2>
vector<pair<T1, T2>> sorted(const unordered_map<T1, T2> &containerIn) {
    vector<pair<T1, T2>> containerOut(containerIn.begin(), containerIn.end());
    sort(containerOut.begin(), containerOut.end(),
         [](const pair<T1, T2> &a, const pair<T1, T2> &b) { return a.second > b.second; });

    return containerOut;
}

#endif // FUNCTIONS_H

