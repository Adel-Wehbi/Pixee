#include "Canvas.h"

Canvas::Canvas(wxFrame *parent, Image image) : wxPanel(parent), image(image) {
    Bind(wxEVT_PAINT, &Canvas::paintEvent, this);
}

void Canvas::paintEvent(wxPaintEvent &event) {
    wxPaintDC dc(this);
    render(dc);
}

void Canvas::paintNow() {
    wxClientDC dc(this);
    render(dc);
}

void Canvas::render(wxDC &dc) {
    dc.SetPen(wxNullPen);
    wxSize pixelSize(20, 20);
    for(int x = 0; x < image.getWidth(); x++) {
        for(int y = 0; y < image.getHeight(); y++){
            dc.SetBrush(wxBrush(image.getPixelAt(x, y)));
            dc.DrawRectangle(wxPoint(x * pixelSize.GetWidth(), y * pixelSize.GetHeight()), pixelSize);
        }
    }
}

void Canvas::setImage(Image image) {
    this->image = image;
}
