//
// Created by Anmol Chugh on 4/11/20.
//

#include "../header/makeClusterDirectories.h"
#include <unordered_set>

using namespace std;

void createClusterDirectories(filesystem::path parentDirectory, const unsigned long num_clusters){
    for(int i=0; i<num_clusters; i++) {
        filesystem::path galleryPath = parentDirectory;
        string clusterName = to_string(i);
        galleryPath += "/";
        galleryPath += clusterName;
        if (!std::filesystem::is_directory(galleryPath)) {
            filesystem::create_directory(galleryPath);
        }
    }

    filesystem::path no_faces_path = parentDirectory;
    no_faces_path += "/-1";
    if(!std::filesystem::is_directory(no_faces_path)){
        filesystem::create_directory(no_faces_path);
    }
}
