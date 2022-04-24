#ifndef PIXEE_MYFRAME_H
#define PIXEE_MYFRAME_H


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


#endif // PIXEE_MYFRAME_H
