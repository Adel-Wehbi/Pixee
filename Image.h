#ifndef SPRITEEDITOR_IMAGE_H
#define SPRITEEDITOR_IMAGE_H


#include <wx/colour.h>

class Image {
    int width;
    int height;
    int nChannels;
    unsigned char* data;

public:
    Image(int width, int height, int n, unsigned char* data);
    int getWidth() const;
    int getHeight() const;
    wxColour getPixelAt(int x, int y) const;
};


#endif //SPRITEEDITOR_IMAGE_H
