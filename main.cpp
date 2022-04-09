#include <wx/wx.h>
#include <stb/stb_image.h>
#include "Canvas.h"

class MyApp: public wxApp
{
    bool OnInit() override;
    wxFrame* frame;
    Canvas* canvas;
};

class MyFrame: public wxFrame
{
public:
    MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

};

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(nullptr, -1, title, pos, size){}

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    auto* sizer = new wxBoxSizer(wxHORIZONTAL);
    frame = new MyFrame(wxT("Hello wxDC"), wxDefaultPosition, wxSize(800, 600));

    canvas = new Canvas(frame);
    sizer->Add(canvas, 1, wxEXPAND);

    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);

    frame->Show();

    return true;
}