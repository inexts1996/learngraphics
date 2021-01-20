//
// Created by iNeXTs on 2021/1/15.
//

#ifndef MYTINYRENDERER_TGAIMAGE_H
#define MYTINYRENDERER_TGAIMAGE_H

#include <fstream>
#include <vector>

using std::uint8_t;
using std::uint16_t;
using std::vector;

struct TGA_Header {
    uint8_t idlength{};
    uint8_t colormaptype{};
    uint8_t datatypecode{};
    uint8_t colormapdepth{};
    uint8_t bitsperpixel{};
    uint8_t imagedescriptor{};

    uint16_t colormaporigin{};
    uint16_t colormaplength{};
    uint16_t x_origin{};
    uint16_t y_origin{};
    uint16_t width{};
    uint16_t height{};
};

#pragma pack(pop)

struct TGAColor {
    uint8_t bgra[4] = {0, 0, 0, 0};
    uint8_t bytespp = {0};

    TGAColor() = default;

    TGAColor(const uint8_t R, const uint8_t G, const uint8_t B, uint8_t A = 255) : bgra{B, G, R, A}, bytespp(4) {}

    TGAColor(const uint8_t v) : bgra{v, 0, 0, 0}, bytespp(1) {}

    TGAColor(const uint8_t *p, const uint8_t bpp) : bgra{0, 0, 0, 0}, bytespp(bpp) {
        for (int i = 0; i < bpp; ++i) {
            bgra[i] = p[i];
        }
    }

    uint8_t& operator[] (const int i) {
        return bgra[i];
    }

    TGAColor operator *(const double intensity) const{
        TGAColor res = *this;
        double clamped = std::max(0., std::min(intensity, 1.)); // Question: 1后面带个小数点是什么意思
        for (int i = 0; i < 4; ++i) {
           res.bgra[i] = bgra[i] * clamped;
        }

        return res;
    }
};

class TGAImage {
protected:
    vector<uint8_t> data;
    int width;
    int height;
    int bytespp;

    bool load_rle_data(std::ifstream &in);
    bool Unload_rle_data(std::ofstream &out) const;

public:
    enum Format {GRAYSCALE = 1, RGB = 3, RGMA = 4};
    TGAImage();
    TGAImage(const int w, const int h, const int bpp);
    bool read_tga_fiie(const std::string filename);
    bool write_tga_file(const double std::string filename, const bool yfilp = true, const bool rle = true) const;
    void flip_horizontally();
    void flip_vertically();
    void scale(const int w, const int h);
    TGAColor get (const int x, const int y) const;
    void set(const int x, const int y, const TGAColor &c);
    int get_width() const;
    int get_hight() const;
    int get_bytespp();
    uint8_t *buffer();
    void clear();
};

#endif //MYTINYRENDERER_TGAIMAGE_H
