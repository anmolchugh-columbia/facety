//
// Created by Bhavya Gupta on 4/11/20.
//

#ifndef FACETY_FACECLUSTERING_H
#define FACETY_FACECLUSTERING_H
#include <dlib/dnn.h>
#include <dlib/clustering.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <filesystem>
#include "../../Utilities/header/Constants.h"
#include "../../FileExplorer/header/directoryIterator.h"
#include <unordered_set>

using namespace dlib;
using namespace std;

std::unordered_map<int, std::vector<string>> clustering(std::vector<string> imagePaths);
#endif //FACETY_FACECLUSTERING_H
