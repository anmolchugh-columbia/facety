//
// Created by Anmol Chugh on 4/10/20.
//

#ifndef FACETY_IMAGEUTILITIES_H
#define FACETY_IMAGEUTILITIES_H

#include <string>
#include <set>

using namespace std;

const set<string> IMAGE_EXTENSIONS = {".png", ".jpg", ".jpeg", ".raw", ".bmp"};
bool is_image_path(string extension);

#endif //FACETY_IMAGEUTILITIES_H
