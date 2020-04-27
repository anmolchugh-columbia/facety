//
// Created by Anmol Chugh on 4/10/20.
//

#ifndef FACETY_IMAGEITERATOR_H
#define FACETY_IMAGEITERATOR_H

#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

using namespace std;

std::vector<string> list_all_images(const std::filesystem::path& path);

#endif //FACETY_IMAGEITERATOR_H
