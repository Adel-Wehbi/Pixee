#include "MyFrame.h"

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
        : wxFrame(nullptr, -1, title, pos, size), actionPerformer(this){

    auto* sizer = new wxBoxSizer(wxHORIZONTAL);

    wxFileDialog fileDialog(this, "OPEN FILE", "", "", "PNG files (*.png)|*.png", wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if(fileDialog.ShowModal() == wxID_CANCEL) {
        exit(0);
    }


    image = std::make_unique<wxImage>(fileDialog.GetPath());
    canvas = new Canvas(this, image.get());
    dragController = new DragController(canvas);

    sizer->Add(canvas, 1, wxEXPAND);
    SetSizer(sizer);
    SetAutoLayout(true);

    canvas->Bind(wxEVT_RIGHT_DOWN, &MyFrame::rightMouseHandler, this);
    canvas->Bind(wxEVT_RIGHT_UP, &MyFrame::rightMouseHandler, this);
    canvas->Bind(wxEVT_KEY_DOWN, [this](wxKeyEvent& event){
        if(tolower(event.GetUnicodeKey()) == 'z' && event.ControlDown())  {
            actionPerformer.undo();
            this->canvas->Refresh();
        }
    });
}

void MyFrame::rightMouseHandler(wxMouseEvent &event) {
    if(event.RightDown())
        dragController->start();
    else
        dragController->stop();
}

wxImage& MyFrame::getImage() {
    return *image;
}

ActionPerformer& MyFrame::getActionPerformer() {
    return actionPerformer;
}


