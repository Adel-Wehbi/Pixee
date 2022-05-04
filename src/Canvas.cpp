#include "Canvas.h"
#include <wx/wfstream.h>
#include <iostream>

Canvas::Canvas(wxFrame *parent, wxImage *image) :
        wxPanel(parent), image(image), imagePosition(100, 100), pixelSize(20, 20), selectedColor(*wxBLACK){

    imageCoordMatrix.Translate(imagePosition.x, imagePosition.y);
    imageCoordMatrix.Scale(pixelSize.x, pixelSize.y);

    wxWindow::SetBackgroundStyle(wxBG_STYLE_PAINT);
    wxWindow::SetDoubleBuffered(true);

    Bind(wxEVT_PAINT, [this](wxPaintEvent& event) {
        wxBufferedPaintDC dc(this, bufferBitmap);
        dc.Clear();
        render(dc);
    });
    Bind(wxEVT_MOUSEWHEEL, &Canvas::middleMouseHandler, this);
    Bind(wxEVT_SIZE, [this](wxSizeEvent& event) {
        this->bufferBitmap = wxBitmap(event.GetSize().GetWidth(), event.GetSize().GetHeight());
    });
    Bind(wxEVT_MOTION, &Canvas::leftDownHandler, this);
    Bind(wxEVT_LEFT_DOWN, &Canvas::leftDownHandler, this);
    Bind(wxEVT_KEY_DOWN, [this](wxKeyEvent& event) {
        if(tolower(event.GetUnicodeKey()) == 's' && event.ControlDown()) {
            wxFileDialog fileDialog(this->GetParent(), "Save Image", "", "", "PNG files (*.PNG) |*.png", wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
            if(fileDialog.ShowModal() == wxID_CANCEL)
                return;
            this->image->SaveFile(fileDialog.GetPath());
        } else if(tolower(event.GetUnicodeKey()) == 'c') {
            wxColourData data;
            data.SetChooseAlpha(true);
            data.SetColour(selectedColor);
            wxColourDialog dialog(this, &data);
            dialog.ShowModal();
            data = dialog.GetColourData();
            selectedColor = data.GetColour();
        }
    });
}

void Canvas::render(wxDC &dc) {
    dc.SetTransformMatrix(imageCoordMatrix);
    wxBitmap imageBitmap(*image);
    dc.DrawBitmap(imageBitmap, wxPoint());
    dc.ResetTransformMatrix();
    // drawing gridlines
    dc.SetPen(wxPen(*wxBLACK, 1));
    int startingX = imagePosition.x - ceil(imagePosition.x / pixelSize.GetWidth()) * pixelSize.GetWidth();
    int startingY = imagePosition.y - ceil(imagePosition.y / pixelSize.GetHeight()) * pixelSize.GetHeight();
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
    imagePosition.x += deltaX;
    imagePosition.y += deltaY;
    imageCoordMatrix = wxAffineMatrix2D();
    imageCoordMatrix.Translate(imagePosition.x, imagePosition.y);
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
    transformMatrix.Translate(imagePosition.x, imagePosition.y);
    transformMatrix.Scale(pixelSize.x, pixelSize.y);
    wxPoint2DDouble realPos(transformMatrix.TransformPoint(wxPoint2DDouble(positionOnImage.m_x, positionOnImage.m_y)));

    translateOrigin(-(realPos - devicePos).m_x, -(realPos - devicePos).m_y);

    Refresh();
}

void Canvas::leftDownHandler(wxMouseEvent &event) {
    if(!event.LeftIsDown())
        return;
    wxAffineMatrix2D matrix(imageCoordMatrix);
    matrix.Invert();
    wxPoint2DDouble positionOnPicture(matrix.TransformPoint(event.GetPosition()));
    if(positionOnPicture.m_x < 0 || positionOnPicture.m_x >= image->GetWidth() || positionOnPicture.m_y < 0 || positionOnPicture.m_y >= image->GetHeight())
        return;

    image->SetRGB(positionOnPicture.m_x, positionOnPicture.m_y, selectedColor.GetRed(), selectedColor.GetGreen(), selectedColor.GetBlue());
    if(image->HasAlpha())
        image->SetAlpha(positionOnPicture.m_x, positionOnPicture.m_y, selectedColor.GetAlpha());
    Refresh();
}
