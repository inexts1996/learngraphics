//
// Created by iNeXTs on 2021/1/15.
//

#include <iostream>
#include <fstream>
#include <cstring>
#include "tgaimage.h"

void TGAImage::set(const int x, const int y, const TGAColor &c) {
    if(!data.size() || x < 0 || y < 0 || x >= width || y >= height)
        return;
    memccpy(data.data()+(x+y * width)*bytespp, c.bgra, bytespp);
}