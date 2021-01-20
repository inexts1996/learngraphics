#include <iostream>
#include "tgaimage.h"

void line(int x0, int y0, int x1, int y1, TGAImage &image, TGAColor color, const char *fileName) {
//    for (float t = 0; t < 1.0f; t+=0.1f) {
//       int x = x0 + (x1 - x0) * t;
//       int y = y0 + (y1 - y0) * t;
//       image.set(x, y, color);
//    }

    bool steep = false;


    if (std::abs(x1 - x0) < std::abs(y1 - y0)) {
        std::swap(x0, y0);
        std::swap(x1, y1);
        steep = true;
    }

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    float derror = std::abs(dy/float(dx));
    float error = 0;
    int y = y0;

    for (int x = x0; x < x1; ++x) {
//        float t = (x - x0) / (float) (x1 - x0);
//        int y = y0 * (1. - t) + y1 * t;

        if(steep)
        {
            image.set(y, x, color);
        }
        else
        {
            image.set(x, y, color);
        }

        error += derror;
        if (error > .5)
        {
            y += (y1 > y0 ? 1 : -1);
            error -= 1;
        }

    }

    image.flip_vertically();
    image.write_tga_file(fileName);
}

int main() {
    TGAImage image(100, 100, TGAImage::RGB);
    TGAColor red = TGAColor(255, 0, 0, 255);
    TGAColor white = TGAColor(255, 255, 255, 255);
    line(13, 20, 80, 40, image, white, "lesson01.tga");
    line(20, 13, 40, 80, image, red, "lesson02.tga");
    line(80, 40, 13, 20, image, red, "lesson03.tga");

    return 0;
}
