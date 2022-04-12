#include "Canvas.h"
#include <iostream>

Canvas::Canvas(wxFrame *parent, Image image) :
        wxPanel(parent), image(image), origin(100, 100), pixelSize(20, 20) {

    Bind(wxEVT_PAINT, &Canvas::paintEvent, this);
    Bind(wxEVT_MOTION, &Canvas::mouseMoveHandler, this);
    Bind(wxEVT_MOUSEWHEEL, &Canvas::middleMouseHandler, this);
}

void Canvas::paintEvent(wxPaintEvent &event) {
    wxPaintDC dc(this);
    render(dc);
}

void Canvas::paintNow() {
    wxClientDC dc(this);
    Refresh();
    render(dc);
}

void Canvas::render(wxDC &dc) {
    dc.SetPen(wxNullPen);
    for(int x = 0; x < image.getWidth(); x++) {
        for(int y = 0; y < image.getHeight(); y++){
            dc.SetBrush(wxBrush(image.getPixelAt(x, y)));
            dc.DrawRectangle(
                    wxPoint(
                    origin.x + x * pixelSize.GetWidth(), origin.y + y * pixelSize.GetHeight()
                    ),
                 pixelSize
                 );
        }
    }
}

void Canvas::setImage(Image image) {
    this->image = image;
}

void Canvas::mouseMoveHandler(wxMouseEvent& event) {
    if(event.RightIsDown()) {
        origin = event.GetPosition();
        paintNow();
    }
}

void Canvas::middleMouseHandler(wxMouseEvent &event) {
    int delta = event.GetWheelRotation() / 10;
    std::cout << delta << std::endl;
    if(delta < 0 && abs(delta) > pixelSize.x) {
       return;
    }
    pixelSize.x += delta;
    pixelSize.y += delta;
    paintNow();
}
