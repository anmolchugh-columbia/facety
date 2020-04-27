//
// Created by Anmol Chugh on 4/10/20.
//

#include "../header/ImageIterator.h"
#include "../../Utilities/header/ImageUtilities.h"

std::vector<string> list_all_images(const std::filesystem::path& path) {
    std::vector<string> images;
    for(const auto& p: std::filesystem::recursive_directory_iterator(path)) {
        if (!std::filesystem::is_directory(p)) {
            string extension_string(p.path().extension());
            if(is_image_path(extension_string)) {
                string path_string(p.path().c_str());
                images.emplace_back(path_string);
            }
        }
    }
    return images;
}