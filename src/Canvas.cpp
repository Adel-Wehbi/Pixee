#include "Canvas.h"
#include <iostream>
#include <wx/dcbuffer.h>

Canvas::Canvas(wxFrame *parent, wxImage *image) :
        wxPanel(parent), image(image), origin(100, 100), pixelSize(20, 20) {

    wxWindow::SetBackgroundStyle(wxBG_STYLE_PAINT);
    wxWindow::SetDoubleBuffered(true);

    Bind(wxEVT_PAINT, &Canvas::paintEvent, this);
    Bind(wxEVT_MOUSEWHEEL, &Canvas::middleMouseHandler, this);
    Bind(wxEVT_SIZE, &Canvas::resizeEvent, this);
}

void Canvas::paintEvent(wxPaintEvent &event) {
    wxBufferedPaintDC dc(this, bitmap);
    dc.Clear();
    render(dc);
}

void Canvas::render(wxDC &dc) {
    wxImage subImage(image->GetSubImage(wxRect(
        0, 0,
        ceil(abs(origin.x - dc.GetSize().GetWidth()) / pixelSize.GetWidth()),
        ceil(abs(origin.y - dc.GetSize().GetHeight()) / pixelSize.GetHeight())
    )));
    dc.SetPen(wxNullPen);
    for(int x = 0; x < subImage.GetWidth(); x++) {
        for(int y = 0; y < subImage.GetHeight(); y++){
            unsigned int alpha = image->HasAlpha() ? (unsigned int) image->GetAlpha(x,y) : 255;
            dc.SetBrush(wxBrush(wxColour(image->GetRed(x, y), image->GetGreen(x, y), image->GetBlue(x, y), alpha)));
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
        dc.DrawLine(wxPoint(0, y), wxPoint(dc.GetSize().GetWidth(), y));
    }
}

void Canvas::setImage(wxImage* image) {
    this->image = image;
}

void Canvas::translateOrigin(int deltaX, int deltaY) {
    origin.x += deltaX;
    origin.y += deltaY;
    Refresh();
}

void Canvas::middleMouseHandler(wxMouseEvent &event) {
    int delta = event.GetWheelRotation() / 10;
    if(delta < 0 && abs(delta) > pixelSize.x) {
       return;
    }
    pixelSize.x += delta;
    pixelSize.y += delta;
    Refresh();
}

void Canvas::resizeEvent(wxSizeEvent& event) {
    bitmap = wxBitmap(event.GetSize().GetWidth(), event.GetSize().GetHeight());
}
