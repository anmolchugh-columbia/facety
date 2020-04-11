//
// Created by Bhavya Gupta on 4/11/20.
//

#ifndef FACETY_FACECLUSTERING_H
#define FACETY_FACECLUSTERING_H
#include <dlib/dnn.h>
#include <dlib/gui_widgets.h>
#include <dlib/clustering.h>
#include <dlib/string.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>

using namespace dlib;
using namespace std;

std::unordered_map<int, std::vector<string>> getFaces(std::vector<string> imagePaths);
#endif //FACETY_FACECLUSTERING_H
