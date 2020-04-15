#include <iostream>
#include "src/FileExplorer/header/ImageIterator.h"
#include <unordered_map>
#include "src/FaceRec/header/faceClustering.h"
#include "src/FileExplorer/header/ImageOrganizer.h"
#include "src/Utilities/header/Constants.h"

int main() {
    Constants fileConstants = Constants::getInstance();
    const std::filesystem::path path = fileConstants.images_directory;
    std::vector<string> images;
    std::unordered_map<int, std::vector<string>> clusters;
    try {
        images = list_all_images(path);
        clusters = clustering(images);

    }
    catch (...){
        cout<<"Caught an exception\n";
    }

    for(const auto& image: images){
        cout<<image<<endl;
    }
//    int i=0, c=1;
//    for(const auto& image: images){
//        if(i>=5){
//            i = 0;
//            c++;
//        }
//        clusters[c].push_back(image);
//        i++;
//    }

    createClusterDirectories(fileConstants.clusters_directory, clusters);

//    cout<<"********************";
//    for(const auto& image: clusters[2]){
//        cout<<image<<endl;
//    }
//    return 0;
}

/*TODO
 * make a separate library for all directory related functionalities -> create delete update
 * speed up
*/