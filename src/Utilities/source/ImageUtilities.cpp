//
// Created by Anmol Chugh on 4/10/20.
//

#include "../header/ImageUtilities.h"

bool is_image_path(string extension){
    return IMAGE_EXTENSIONS.find(extension) != IMAGE_EXTENSIONS.end();
}