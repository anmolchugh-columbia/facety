//
// Created by Anmol Chugh on 4/11/20.
//

#ifndef FACETY_IMAGEORGANIZER_H
#define FACETY_IMAGEORGANIZER_H

#include <filesystem>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

void createClusterDirectories(filesystem::path parentDirectory, std::unordered_map<int, std::vector<string>> clusters);

#endif //FACETY_IMAGEORGANIZER_H
