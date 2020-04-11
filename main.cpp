#include <iostream>
#include "src/FileExplorer/header/ImageIterator.h"
#include<unordered_map>
#include "src/faceRec/header/faceClustering.h"

int main() {
    const std::filesystem::path path = "/Users/bhavyagupta/Documents/Columbia/sem2/design using c++/project/facety/src/Resources/Faces";
    std::vector<string> images;
    std::unordered_map<int, std::vector<string>> clusters;
    try {
        images = list_all_images(path);
        clusters = getFaces(images);
//        cout<<"yayyayay"<<endl;
    }
    catch (...){
        cout<<"Caught an exception\n";
    }

    for(const auto& image: images){
        cout<<image<<endl;
    }
    cout<<"********************";
    for(const auto& image: clusters[2]){
        cout<<image<<endl;
    }
    return 0;
}

/*TODO
 * speed up
*/