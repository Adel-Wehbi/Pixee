#ifndef PIXEE_MYFRAME_H
#define PIXEE_MYFRAME_H


#include "Canvas.h"
#include "DragController.h"
#include "ActionPerformer.h"
#include <memory>

class MyFrame: public wxFrame
{
    ActionPerformer actionPerformer;
    Canvas* canvas;
    DragController* dragController;
    std::unique_ptr<wxImage> image;

public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
    wxImage& getImage();
    ActionPerformer& getActionPerformer();
private:
    void rightMouseHandler(wxMouseEvent& event);
};


#endif // PIXEE_MYFRAME_H
