#ifndef SPRITEEDITOR_CANVAS_H
#define SPRITEEDITOR_CANVAS_H

#include <wx/wx.h>
#include <wx/dcbuffer.h>


class Canvas : public wxPanel {
private:
    wxImage* image;
    wxBitmap bufferBitmap;
    wxPoint origin;
    wxSize pixelSize;
    wxAffineMatrix2D imageCoordMatrix;
public:
    explicit Canvas(wxFrame* parent, wxImage*image);

    void setImage(wxImage *image);
    void translateOrigin(int deltaX, int deltaY);

    void middleMouseHandler(wxMouseEvent& event);
    void resizeEvent(wxSizeEvent& event);

    void paintEvent(wxPaintEvent& event);
    void render(wxBufferedPaintDC& dc);

};

#endif //SPRITEEDITOR_CANVAS_H
