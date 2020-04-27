#include "../header/ImageIterator.h"
#include "../../Utilities/header/ImageUtilities.h"

std::vector<string> list_all_directories(const std::filesystem::path& path) {
    std::vector<string> directories;
    for(const auto& p: std::filesystem::recursive_directory_iterator(path)) {
        if (std::filesystem::is_directory(p)) {
            string path_string(p.path().c_str());
            directories.emplace_back(path_string);
        }
    }
    return directories;
}