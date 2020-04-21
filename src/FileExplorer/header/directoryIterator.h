//
// Created by Anmol Chugh on 4/10/20.
//

#ifndef FACETY_DIRECTORYITERATOR_H
#define FACETY_DIRECTORYITERATOR_H

#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

using namespace std;

vector<string> list_all_directories(const std::filesystem::path& path);

#endif //FACETY_IMAGEITERATOR_H