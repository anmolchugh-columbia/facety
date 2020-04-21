//
// Created by Anmol Chugh on 4/11/20.
//

#ifndef FACETY_CONSTANTS_H
#define FACETY_CONSTANTS_H

#include <filesystem>
using namespace std;

class Constants{
public:
    filesystem::path project_directory;
    filesystem::path images_directory;
    filesystem::path clusters_directory;
    static Constants& getInstance(){
        static Constants instance;
        return instance;
    }
private:
    filesystem::path relative_images = "resources/faces4";
    filesystem::path relative_clusters = "resources/clusters";
    Constants(){
        relative_images = "resources/faces4";
        relative_clusters = "resources/clusters";
        project_directory = filesystem::current_path().parent_path();
        images_directory = project_directory / relative_images;
        clusters_directory = project_directory / relative_clusters;
    }


};
#endif //FACETY_CONSTANTS_H
