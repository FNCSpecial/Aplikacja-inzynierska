#include "cApp.h"




//Startowe okno
bool cApp::OnInit()
{
	MyFrame* frame = new MyFrame("Aplikacja", wxPoint(800, 600), wxSize(1080, 720), wxMINIMIZE_BOX  | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN);
    
    
    frame->SetBackgroundColour(wxColor(200,200,200));
    
    SetTopWindow(frame);
    frame->Show(true);
	return true;
}



//parametry okna
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size, const long& style)
    : wxFrame(NULL, wxID_ANY, title, pos, size,style)
{

    panel->SetBackgroundColour(wxColour(54,53,55));

   

    //menu Plik
    menuPlik->Append(ID_Zapisz, "&Zapisz\tCtrl-S","zapisano");
    menuPlik->AppendSeparator();
    menuPlik->Append(ID_Wczytaj, "&Wczytaj\tCtrl-H","wczytano");
    menuPlik->AppendSeparator();
    menuPlik->Append(wxID_EXIT);
    
    //menu Pomocy
    
    menuPomoc->Append(wxID_ABOUT);

    //pasek menu 
   
    menuBar->Append(menuPlik, "&Plik");
    menuBar->Append(menuPomoc, "&Pomoc");
    
    SetMenuBar(menuBar);
    CreateStatusBar();
    //dolny napis
    SetStatusText("Daniel £ataœ");
   


    //graf


    mpLayer* l;

    // Create a mpFXYVector layer
    mpFXYVector* vectorLayer = new mpFXYVector;
    // Create two vectors for x,y and fill them with data
    std::vector<double> vectorx, vectory;
    double xcoord;
    double ycoord;
    for (int i = -50; i < 60; i++) {
        xcoord = i;
        ycoord =i*i;
        vectorx.push_back(xcoord);
        vectory.push_back(ycoord);
    }



    vectorLayer->SetData(vectorx, vectory);
    vectorLayer->SetContinuity(true);
    wxPen vectorpen(*wxBLUE, 2, wxPENSTYLE_SOLID);
    vectorLayer->SetPen(vectorpen);
    vectorLayer->SetDrawOutsideMargins(false);






    wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);
    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);

    graf->SetMargins(30, 30, 50, 100);

    graf->AddLayer(xaxis);
    graf->AddLayer(yaxis);
    graf->AddLayer(vectorLayer);

    mpInfoCoords* nfo;
    graf->AddLayer(nfo = new mpInfoCoords(wxRect(10, 10, 10, 10), wxTRANSPARENT_BRUSH)); //&hatch));
    nfo->SetVisible(true);
 


    

    SetAutoLayout(TRUE);
 




    graf->EnableDoubleBuffer(true);
    graf->SetMPScrollbars(false);
    graf->Fit();

    
}








void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("tutaj informacje jak program dziala","Pomoc",wxOK | wxICON_INFORMATION);
}

void MyFrame::OnOblicz(wxCommandEvent& event)
{
    wynik->Clear();

    wxString stringwynikmulti;
    wxString stringx = zmiennax->GetValue();
    wxString stringy = zmiennay->GetValue();
   

    stringx.ToDouble(&dx);
    stringy.ToDouble(&dy);


   
        double wynikxy = dx + dy;
       

        for (int i = 0; i < 10; i++) {

            stringwynik[i] = wxString::Format(wxT("%f"),wynikxy);
            stringwynikmulti = stringwynikmulti+ stringwynik[i]+ " ; " + stringwynik[i] + "\n";
        }
        wynik->SetValue(stringwynikmulti);
        
   
    
}

void MyFrame::OnZapisz(wxCommandEvent& event)
{

    wxString firstFilename = wxT("material");
    wxString caption = wxT("Nazwa:");
    wxString wildcard = wxT("Material (*.txt)");
    wxString defaultDir = wxT("c:\\temp");
    wxString saveFilename = wxEmptyString;

    wxFileDialog* OnSaveFileMaterial = new wxFileDialog(panel, wxT("Podaj nazwe oraz lokalizacje pliku:"),
        wxT(""), wxT(""), wxT("Material (*.txt)|*.txt"), wxFD_SAVE); // | wxFD_OVERWRITE_PROMPT );

    int response = OnSaveFileMaterial->ShowModal();
    if (response == wxID_OK)
    {
        saveFilename = OnSaveFileMaterial->GetPath();

        wxTextFile file(saveFilename);
        file.Create();
        file.Open();

        int size = wynik->GetNumberOfLines();
         
       

        for (int i = 0; i < size; i++) {
            file.AddLine(wynik->GetLineText(i));
            file.Write();
        }

        file.Close();

        wxLogMessage("zapisano");
        
    }

    if (response != wxID_OK) {
        wxLogMessage("Zapisywanie przerwane");
    }
}

void MyFrame::OnWczytaj(wxCommandEvent& event)
{
    wxLogMessage("Tu bedzie wczytywanie");
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

