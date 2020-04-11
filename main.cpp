#include <iostream>
#include "src/FileExplorer/header/ImageIterator.h"

int main() {
    const std::filesystem::path path = "/Users/mansikhemka/Desktop/images";
    vector<string> images;
    try {
        images = list_all_images(path);
    }
    catch (...){
        cout<<"Caught an exception\n";
    }

    for(const auto& image: images){
        cout<<image<<endl;
    }
    return 0;
}
