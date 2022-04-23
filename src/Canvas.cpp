#include "Canvas.h"
#include <wx/graphics.h>
#include <iostream>

Canvas::Canvas(wxFrame *parent, wxImage *image) :
        wxPanel(parent), image(image), origin(100, 100), pixelSize(20, 20) {

    imageCoordMatrix.Translate(origin.x, origin.y);
    imageCoordMatrix.Scale(pixelSize.x, pixelSize.y);

    wxWindow::SetBackgroundStyle(wxBG_STYLE_PAINT);
    wxWindow::SetDoubleBuffered(true);

    Bind(wxEVT_PAINT, &Canvas::paintEvent, this);
    Bind(wxEVT_MOUSEWHEEL, &Canvas::middleMouseHandler, this);
    Bind(wxEVT_SIZE, &Canvas::resizeEvent, this);
    Bind(wxEVT_MOTION, &Canvas::leftDownHandler, this);
    Bind(wxEVT_LEFT_DOWN, &Canvas::leftDownHandler, this);
}

void Canvas::paintEvent(wxPaintEvent &event) {
    wxBufferedPaintDC dc(this, bufferBitmap);
    dc.Clear();
    render(dc);
}

void Canvas::render(wxBufferedPaintDC &dc) {
    dc.SetTransformMatrix(imageCoordMatrix);
    wxBitmap imageBitmap(*image);
    dc.SetPen(wxNullPen);
    dc.DrawBitmap(imageBitmap, wxPoint());
    dc.ResetTransformMatrix();
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
    imageCoordMatrix = wxAffineMatrix2D();
    imageCoordMatrix.Translate(origin.x, origin.y);
    imageCoordMatrix.Scale(pixelSize.x, pixelSize.y);
    Refresh();
}

void Canvas::middleMouseHandler(wxMouseEvent &event) {
    int delta = event.GetWheelRotation() / 10;
    if(delta < 0 && abs(delta) > pixelSize.x) {
       return;
    }

    wxPoint devicePos(event.GetPosition());
    wxAffineMatrix2D transformMatrix(imageCoordMatrix);
    transformMatrix.Invert();
    wxPoint2DDouble positionOnImage(transformMatrix.TransformPoint(wxPoint2DDouble(devicePos.x, devicePos.y)));

    pixelSize.x += delta;
    pixelSize.y += delta;

    // now we get the real position of the same 'positionOnImage' after scaling
    transformMatrix = wxAffineMatrix2D();
    transformMatrix.Translate(origin.x, origin.y);
    transformMatrix.Scale(pixelSize.x, pixelSize.y);
    wxPoint2DDouble realPos(transformMatrix.TransformPoint(wxPoint2DDouble(positionOnImage.m_x, positionOnImage.m_y)));

    translateOrigin(-(realPos - devicePos).m_x, -(realPos - devicePos).m_y);

    Refresh();
}

void Canvas::resizeEvent(wxSizeEvent& event) {
    bufferBitmap = wxBitmap(event.GetSize().GetWidth(), event.GetSize().GetHeight());
}

void Canvas::leftDownHandler(wxMouseEvent &event) {
    if(!event.LeftIsDown())
        return;
    wxAffineMatrix2D matrix(imageCoordMatrix);
    matrix.Invert();
    wxPoint2DDouble positionOnPicture(matrix.TransformPoint(event.GetPosition()));
    if(positionOnPicture.m_x < 0 || positionOnPicture.m_x >= image->GetWidth() || positionOnPicture.m_y < 0 || positionOnPicture.m_y >= image->GetHeight())
        return;
    image->SetRGB(positionOnPicture.m_x, positionOnPicture.m_y, 0, 255, 0);
    if(image->HasAlpha())
        image->SetAlpha(positionOnPicture.m_x, positionOnPicture.m_y, 255);
    Refresh();
}
