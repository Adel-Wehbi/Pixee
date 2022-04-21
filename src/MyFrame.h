#ifndef SPRITEEDITOR_MYFRAME_H
#define SPRITEEDITOR_MYFRAME_H


#include "Canvas.h"
#include "DragController.h"

class MyFrame: public wxFrame
{
    Canvas* canvas;
    DragController* dragController;
    wxImage* image;

public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
    void rightMouseHandler(wxMouseEvent& event);
};


#endif //SPRITEEDITOR_MYFRAME_H
