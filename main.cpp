#include <wx/wx.h>
#include <stb/stb_image.h>
#include "Canvas.h"
#include "Image.h"

unsigned char * data;

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
    : wxFrame(nullptr, -1, title, pos, size){}

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    auto* sizer = new wxBoxSizer(wxHORIZONTAL);
    frame = new MyFrame("Hello wxDC", wxDefaultPosition, wxSize(800, 600));



    int w, h, n;
    data = stbi_load("../test-images/test.png", &w, &h, &n, 4);
    Image image(w, h, n, data);

    canvas = new Canvas(frame, image);
    sizer->Add(canvas, 1, wxEXPAND);

    frame->SetSizer(sizer);
    frame->SetAutoLayout(true);
    canvas->setImage(image);
    frame->Show();

    return true;
}

int MyApp::OnExit() {
    stbi_image_free(data);
}