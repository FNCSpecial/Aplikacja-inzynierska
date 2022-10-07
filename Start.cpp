#include "Start.h"



bool Start::OnInit()
{
    MyFrame* frame = new MyFrame("Start Page", wxPoint(800, 400), wxSize(1080, 720));
    frame->Show(true);
    return true;
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets' Hello world sample",
        "About Hello World", wxOK | wxICON_INFORMATION);
}

void MyFrame::OnHello(wxCommandEvent& event)
{
    wxLogMessage("Hello world from wxWidgets!");
}