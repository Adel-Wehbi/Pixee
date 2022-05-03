#ifndef PIXEE_CANVAS_H
#define PIXEE_CANVAS_H

#include <wx/wx.h>
#include <wx/dcbuffer.h>


class Canvas : public wxPanel {
private:
    wxImage* image;
    wxBitmap bufferBitmap;
    wxPoint imagePosition;
    wxSize pixelSize;
    wxAffineMatrix2D imageCoordMatrix;
public:
    explicit Canvas(wxFrame* parent, wxImage*image);

    void setImage(wxImage *image);
    void translateOrigin(int deltaX, int deltaY);

    void middleMouseHandler(wxMouseEvent& event);
    void leftDownHandler(wxMouseEvent& event);

    void render(wxDC& dc);

};

#endif // PIXEE_CANVAS_H
