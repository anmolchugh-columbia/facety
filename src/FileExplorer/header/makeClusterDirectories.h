//
// Created by Anmol Chugh on 4/10/20.
//

#ifndef FACETY_MAKECLUSTERDIRECTORIES_H
#define FACETY_MAKECLUSTERDIRECTORIES_H

#include <stdio.h>
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>

using namespace std;

void createClusterDirectories(filesystem::path parentDirectory, const unsigned long num_clusters);

#endif //FACETY_MAKECLUSTERDIRECTORIES_H