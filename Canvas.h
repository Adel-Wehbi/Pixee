#ifndef SPRITEEDITOR_CANVAS_H
#define SPRITEEDITOR_CANVAS_H

#include <wx/wx.h>
#include "Image.h"


class Canvas : public wxPanel {
private:
    Image image;
    wxPoint origin;
    wxSize pixelSize;
public:
    explicit Canvas(wxFrame* parent, Image image);

    void setImage(Image image);

    void mouseMoveHandler(wxMouseEvent& event);
    void middleMouseHandler(wxMouseEvent& event);

    void paintEvent(wxPaintEvent& event);
    void paintNow();
    void render(wxDC& dc);

};

#endif //SPRITEEDITOR_CANVAS_H
