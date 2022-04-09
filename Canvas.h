#ifndef SPRITEEDITOR_CANVAS_H
#define SPRITEEDITOR_CANVAS_H

#include <wx/wx.h>


class Canvas : public wxPanel {
public:
    explicit Canvas(wxFrame* parent);

    void paintEvent(wxPaintEvent& event);
    void paintNow();
    void render(wxDC& dc);

};

#endif //SPRITEEDITOR_CANVAS_H
