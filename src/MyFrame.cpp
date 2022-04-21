#include "MyFrame.h"

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
        : wxFrame(nullptr, -1, title, pos, size){

    auto* sizer = new wxBoxSizer(wxHORIZONTAL);

    image = new wxImage("../test-images/test.png");
    canvas = new Canvas(this, image);
    dragController = new DragController(canvas);

    sizer->Add(canvas, 1, wxEXPAND);
    SetSizer(sizer);
    SetAutoLayout(true);

    canvas->Bind(wxEVT_RIGHT_DOWN, &MyFrame::rightMouseHandler, this);
    canvas->Bind(wxEVT_RIGHT_UP, &MyFrame::rightMouseHandler, this);
}

void MyFrame::rightMouseHandler(wxMouseEvent &event) {
    if(event.RightDown())
        dragController->start();
    else
        dragController->stop();
}


