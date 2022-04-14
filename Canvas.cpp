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
    // drawing gridlines
    dc.SetPen(wxPen(*wxBLACK, 1));
    int startingX = origin.x - ceil(origin.x / pixelSize.GetWidth()) * pixelSize.GetWidth();
    int startingY = origin.y - ceil(origin.y / pixelSize.GetHeight()) * pixelSize.GetHeight();
    for(int x = startingX; x < dc.GetSize().GetWidth(); x += pixelSize.GetWidth()) {
        dc.DrawLine(wxPoint(x, 0), wxPoint(x, dc.GetSize().GetHeight()));
    }
    for(int y = startingY; y < dc.GetSize().GetHeight(); y += pixelSize.GetHeight()) {
        dc.DrawLine(wxPoint(0, y), wxPoint(dc.GetSize().GetHeight(), y));
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
    if(delta < 0 && abs(delta) > pixelSize.x) {
       return;
    }
    pixelSize.x += delta;
    pixelSize.y += delta;
    paintNow();
}
