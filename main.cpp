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
        cout<<images.size()<<endl;
        clusters = clustering(images);
        cout<<"clustered"<<endl;

    }
    catch (...){
        cout<<"Caught an exception\n";
    }

    populateClusters(fileConstants.clusters_directory, clusters);

    return 0;
}

/*TODO
 * Horizontal images
 * thumbnail as directory icon
 * thumbnail as representation based on confidence score
 * unit tests
 * use case scenario with implementation
 * some quantitative tests
 * Slides–Design/rationale document
 * Tutorial
 * Documentation
 * Working code
 * make a separate library for all directory related functionalities -> create delete update
 * speed up
*/