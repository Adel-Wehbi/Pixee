#include <wx/wx.h>
#include "Canvas.h"

wxImage* image;

class MyApp: public wxApp
{
    bool OnInit() override;
    int OnExit() override;
    wxFrame* frame;
    Canvas* canvas;
};

class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

};

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
        : wxFrame(nullptr, -1, title, pos, size){

}

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    auto* sizer = new wxBoxSizer(wxHORIZONTAL);
    frame = new MyFrame("Hello wxDC", wxDefaultPosition, wxSize(800, 600));


    wxInitAllImageHandlers();
    image = new wxImage("../test-images/test.png");

    canvas = new Canvas(frame, image);
    sizer->Add(canvas, 1, wxEXPAND);

    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);
    canvas->setImage(image);
    frame->Show();

    return true;
}

int MyApp::OnExit() {
    delete image;
}