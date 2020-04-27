//
// Created by Anmol Chugh on 4/11/20.
//

#include "../header/ImageOrganizer.h"
#include <unordered_set>

using namespace std;

void copyImagesToGalleryCluster(filesystem::path galleryClusterPath, std::vector<string> sourceImages){
    for(const auto& sourceImage: sourceImages){
        filesystem::copy(sourceImage, galleryClusterPath, filesystem::copy_options::update_existing);
    }
}

std::unordered_set<string> getClusterNames(std::unordered_map<int, std::vector<string>> clusters){
    std::unordered_set<string> clusterNames;
    for(auto & cluster : clusters){
        clusterNames.insert(to_string(cluster.first));
    }
    return clusterNames;
}

void populateClusters(filesystem::path parentDirectory, std::unordered_map<int, std::vector<string> > clusters){
    std::unordered_set<string> clusterNames = getClusterNames(clusters);
    for(string clusterName : clusterNames){
        filesystem::path galleryPath = parentDirectory;
        clusterName = clusterName;
        filesystem::path directory = galleryPath;
        galleryPath += "/";
        galleryPath += clusterName;
        copyImagesToGalleryCluster(galleryPath, clusters[stoi(clusterName)]);
    }
}
