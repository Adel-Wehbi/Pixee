#include "Image.h"

Image::Image(int width, int height, int n, unsigned char *data) : width(width), height(height), nChannels(n), data(data){

}

int Image::getWidth() const {
    return width;
}

int Image::getHeight() const {
    return height;
}

wxColour Image::getPixelAt(int x, int y) const {
    int offset = x * nChannels + width * y * nChannels;
    return wxColour(
            data[offset],
            data[offset + 1],
            data[offset + 2],
            data[offset + 3]
    );
}