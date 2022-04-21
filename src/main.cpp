#include <wx/wx.h>
#include "MyFrame.h"

class MyApp: public wxApp
{
    bool OnInit() override;
    int OnExit() override;
    wxFrame* frame;
};

wxIMPLEMENT_APP(MyApp);

bool MyApp::OnInit() {
    wxInitAllImageHandlers();
    frame = new MyFrame("Hello wxDC", wxDefaultPosition, wxSize(800, 600));
    frame->Show();
    return true;
}

int MyApp::OnExit() {
}
