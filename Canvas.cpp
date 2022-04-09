#include "Canvas.h"

Canvas::Canvas(wxFrame *parent) : wxPanel(parent) {
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
    wxSize size(dc.GetSize());
    dc.SetPen(*wxThePenList->FindOrCreatePen(*wxWHITE, 10));
    dc.SetBrush(wxNullBrush);
    dc.DrawRectangle(wxRect(size));
}