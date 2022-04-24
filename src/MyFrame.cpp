#include "MyFrame.h"

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
        : wxFrame(nullptr, -1, title, pos, size){

    auto* sizer = new wxBoxSizer(wxHORIZONTAL);

    wxFileDialog fileDialog(this, "OPEN FILE", "", "", "PNG files (*.png)|*.png", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if(fileDialog.ShowModal() == wxID_CANCEL) {
        exit(0);
    }


    image = new wxImage(fileDialog.GetPath());
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


