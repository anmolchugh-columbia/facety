//
// Created by Bhavya Gupta on 4/26/20.
//

#ifndef FACETY_CLUSTERING_H
#define FACETY_CLUSTERING_H

#include <dlib/dnn.h>
#include <dlib/clustering.h>
#include <dlib/image_io.h>
#include <dlib/image_processing/frontal_face_detector.h>
#include <filesystem>
#include "../../FileExplorer/header/directoryIterator.h"
#include "../../FileExplorer/header/makeClusterDirectories.h"
#include <unordered_set>
#include <chrono>

using namespace dlib;
using namespace std;

class Clustering {

    std::vector<string> imagePaths;

    filesystem::path project_directory = filesystem::current_path().parent_path();
    filesystem::path models;
    string resources_path_string;
    filesystem::path path_to_existing_clusters;
    frontal_face_detector detector = get_frontal_face_detector();
    shape_predictor sp;

    std::vector<int> faceID;
    std::vector<matrix<rgb_pixel>> faces;
    std::vector<string> no_faces;
    int oldFaceStartIndex = -1;
    std::vector<string> oldFacePaths;

    void getFaces();
    int getOldFaces();
    std::unordered_map<int, std::vector<string>> getClusters();
    int detectFaces(string imagePath);


    public :
        Clustering(std::vector<string> imagePaths, filesystem::path clusters_directory){
            this->imagePaths = imagePaths;
            this->path_to_existing_clusters = clusters_directory;
            models = project_directory / "resources/model";
            resources_path_string = models.c_str();
            faceID.resize(imagePaths.size(), 0);
            detector = get_frontal_face_detector();
            deserialize( resources_path_string + "/shape_predictor_5_face_landmarks.dat") >> sp;
            cout<<filesystem::current_path()<<endl;

        }
        std::unordered_map<int, std::vector<string>> cluster();
};

#endif //FACETY_CLUSTERING_H
