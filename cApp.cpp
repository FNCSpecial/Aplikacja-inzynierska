
#include"cApp.h"
#include "obliczenia.h"






//Startowe okno
bool cApp::OnInit()
{

    //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

   

    MyFrame* frame = new MyFrame("Aplikacja do modelowania nieparzystych modów TE", wxPoint(800, 600), wxSize(1080, 720), wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxRESIZE_BORDER);


    frame->SetBackgroundColour(wxColor(200, 200, 200));

    SetTopWindow(frame);
    frame->Show(true);


  
    

    return true;

}


//parametry okna
MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size, const long& style)
    : wxFrame(NULL, wxID_ANY, title, pos, size,style)
{
   
  
    
  //  lambda = 1.3E-6;
  //  dom1 = 1;
  //  dom2 = 1;
  //  N = 1;

    panel->SetBackgroundColour(wxColour(54,53,55));

    //domieszkowanie lista
    domieszkowanie_lista1.Add("Domieszkowanie1");
    domieszkowanie_lista1.Add("n_GeO2_3_1");
    domieszkowanie_lista1.Add("n_SiO2");



    domieszkowanie_lista2.Add("Domieszkowanie2");
    domieszkowanie_lista2.Add("n_SiO2");
    domieszkowanie_lista2.Add("n_F_1");


    Domieszkowanie1 = new wxChoice(this, ID_Domieszkowanie1, wxPoint(10, 10), wxSize(100, 20), domieszkowanie_lista1);
    Domieszkowanie2 = new wxChoice(this, ID_Domieszkowanie2, wxPoint(10, 10), wxSize(100, 20), domieszkowanie_lista2);

    Domieszkowanie1->SetSelection(0);
    Domieszkowanie2->SetSelection(0);

 

    //menu Plik 
    menuPlik->Append(ID_SAVE_SCREENSHOT, "Zrzut ekranu\tCtrl-S", "zapisano");
    menuPlik->AppendSeparator();
    menuPlik->Append(ID_BLACK_THEME, "Ciemny graf");
    menuPlik->AppendSeparator();
    menuPlik->Append(ID_White_theme, "Jasny graf");
    menuPlik->AppendSeparator();
    menuPlik->Append(wxID_EXIT, "&Wyjdz");


    
    //menu Pomocy
    
    menuPomoc->Append(wxID_ABOUT,"Instrukcja");


    //menu Grafu

    menuGraf->Append(ID_Graf1, "&Wykres Miejsc zerowych");
    menuGraf->AppendSeparator();
    menuGraf->Append(ID_Graf2, "&Wykres E01 V/m");
    menuGraf->AppendSeparator();
    menuGraf->Append(ID_Graf3, "&Wykres H01 A/m");
    menuGraf->AppendSeparator();
    menuGraf->Append(ID_Graf4, "&Wykres H02 A/m");
    menuGraf->AppendSeparator();
    menuGraf->Append(ID_Graf5, "&Wykres E02 V/m");
    menuGraf->AppendSeparator();
    menuGraf->Append(ID_Graf6, "&Wykres E0/E0max");
    menuGraf->AppendSeparator();
    menuGraf->Append(ID_Graf7, "&Wykres H0/H0max");
  
    //menu Wynik
    menuWynik->Append(ID_Wynik1, "&Zmienne");
    menuWynik->AppendSeparator();
    menuWynik->Append(ID_Wynik2, "&Argumenty poprzedzające wystąpienie miejsca zerowego");
    menuWynik->AppendSeparator();
    menuWynik->Append(ID_Wynik3, "&BetaC, HDBetaC oraz miejsca zerowe");
    menuWynik->AppendSeparator();
    menuWynik->Append(ID_Wynik4, "&Miejsca zerowe");
    menuWynik->AppendSeparator();
    menuWynik->Append(ID_Wynik5, "&AH,CH1 i CH2");
    menuWynik->AppendSeparator();
    menuWynik->Append(ID_Wynik6, "&E01 oraz H01 max");
    menuWynik->AppendSeparator();
    menuWynik->Append(ID_Wynik7, "&E01,E02,H01,H02");
    //pasek menu 
   
    menuBar->Append(menuPlik, "&Plik");
    menuBar->Append(menuPomoc, "&Pomoc");
    menuBar->Append(menuGraf, "&Wykresy");
    menuBar->Append(menuWynik, "&Wniki");
  
    
    SetMenuBar(menuBar);
    CreateStatusBar();
    //dolny napis
    SetStatusText("Daniel Łataś");
   


    //graf
    

  


    wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);




    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);
    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);


    graf->SetMargins(10, 10, 50, 100);

    graf->AddLayer(xaxis);
    graf->AddLayer(yaxis);
    graf->AddLayer(vectorLayer);

    
    graf->AddLayer(nfo = new mpInfoCoords(wxRect(0,535,10,10), wxTRANSPARENT_BRUSH)); //&hatch));
    nfo->SetVisible(true);

    
   
  


    SetAutoLayout(TRUE);


    


    zmiennesizer->Add(Dlugosc_Fali, 1, wxEXPAND);
    zmiennesizer->AddSpacer(2);
    zmiennesizer->Add(Domieszkowanie1, 1, wxEXPAND);
    zmiennesizer->AddSpacer(2);


    zmiennesizer2->Add(Podaj_N, 1, wxEXPAND);
    zmiennesizer2->AddSpacer(2);
    zmiennesizer2->Add(Domieszkowanie2, 1, wxEXPAND);
    zmiennesizer2->AddSpacer(2);


    horizontalsizer->Add(zmiennesizer, 1, wxEXPAND);
    horizontalsizer->AddSpacer(2);
    horizontalsizer->Add(zmiennesizer2, 1, wxEXPAND);
    horizontalsizer->AddSpacer(5);
    horizontalsizer->Add(licz,3, wxSHAPED);
  
    topsizer->Add(horizontalsizer, 0, wxEXPAND);
    topsizer->Add(graf, 1, wxEXPAND);



    SetSizer(topsizer);
    axesPos[0] = 0;
    axesPos[1] = 0;
    ticks = true;




    graf->EnableDoubleBuffer(true);
    graf->SetMPScrollbars(false);
    



}

MyFrame1::MyFrame1(const wxString& title, const wxPoint& pos, const wxSize& size, const long& style)
    : wxFrame(NULL, wxID_ANY, title, pos, size, style)
{
    SetBackgroundColour(wxColor(200, 200, 200));
   
    menuBarWynik->Append(menuPLikWynik, "&Plik");
    SetMenuBar(menuBarWynik);
    CreateStatusBar();
    SetStatusText("Daniel Łataś");
   
   
    

}


//grafy

void MyFrame::OnGraf1(wxCommandEvent& event) {
    if (zmienne == true) {
        std::auto_ptr <Obliczenia> obliczenia(new Obliczenia(N, lambda, dom1, dom2));




        graf->DelLayer(vectorLayer);
        graf->DelLayer(xaxis);
        graf->DelLayer(yaxis);

        wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

        xaxis->SetName(wxT("β/βmin"));
        yaxis->SetName(wxT("HD(β)"));

        xaxis->SetFont(graphFont);
        yaxis->SetFont(graphFont);
        xaxis->SetDrawOutsideMargins(false);
        yaxis->SetDrawOutsideMargins(false);



        graf->SetMargins(10, 10, 50, 100);



        vectorx.clear();
        vectory.clear();

        obliczenia->Wykres1();





        for (int i = 0; i < 999; i++) {

            xcoord = obliczenia->xcord[i];
            ycoord = obliczenia->ycord[i];

            vectorx.push_back(xcoord);
            vectory.push_back(ycoord);
            //  cout << vectory[i] << endl;
        }

        vectorLayer->SetData(vectorx, vectory);
        vectorLayer->SetContinuity(true);
        wxPen vectorpen(*wxBLUE, 2, wxPENSTYLE_SOLID);
        vectorLayer->SetPen(vectorpen);
        vectorLayer->SetDrawOutsideMargins(false);


        graf->AddLayer(xaxis);
        graf->AddLayer(yaxis);
        graf->AddLayer(vectorLayer);

        graf->Fit();
    }

    else {
        wxMessageBox("podaj dane");
    }

}

void MyFrame::OnGraf2(wxCommandEvent& event) {
    if (zmienne == true) {
        std::auto_ptr <Obliczenia> obliczenia(new Obliczenia(N, lambda, dom1, dom2));


        graf->DelLayer(vectorLayer);
        graf->DelLayer(xaxis);
        graf->DelLayer(yaxis);

        wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);



        xaxis->SetName(wxT("x/a"));
        yaxis->SetName(wxT("E01(x/a) [V/m]"));


        xaxis->SetFont(graphFont);
        yaxis->SetFont(graphFont);
        xaxis->SetDrawOutsideMargins(false);
        yaxis->SetDrawOutsideMargins(false);



        graf->SetMargins(10, 10, 50, 100);



        vectorx.clear();
        vectory.clear();

        obliczenia->Wykres3();


        for (int i = 0; i < 1000; i++) {

            xcoord = obliczenia->xcord[i];
            ycoord = obliczenia->ycord[i];

            vectorx.push_back(xcoord);
            vectory.push_back(ycoord);
            //  cout << vectory[i] << endl;
        }

        vectorLayer->SetData(vectorx, vectory);
        vectorLayer->SetContinuity(true);
        wxPen vectorpen(*wxBLUE, 2, wxPENSTYLE_SOLID);
        vectorLayer->SetPen(vectorpen);
        vectorLayer->SetDrawOutsideMargins(false);

        graf->AddLayer(vectorLayer);
        graf->AddLayer(xaxis);
        graf->AddLayer(yaxis);

        graf->Fit();
    }
    else {
        wxMessageBox("podaj dane");
    }
}

void MyFrame::OnGraf3(wxCommandEvent& event) {
    if (zmienne == true) {
    std::auto_ptr <Obliczenia> obliczenia(new Obliczenia(N, lambda, dom1, dom2));

    graf->DelLayer(vectorLayer);
    graf->DelLayer(xaxis);
    graf->DelLayer(yaxis);

    wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    xaxis->SetName(wxT("x/a"));
    yaxis->SetName(wxT("H01(x/a) [A/m]"));

    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);
    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);



    graf->SetMargins(10, 10, 50, 100);



    vectorx.clear();
    vectory.clear();

    obliczenia->Wykres2();

    for (int i = 0; i < 1000; i++) {

        xcoord = obliczenia->xcord[i];
        ycoord = obliczenia->ycord[i];

        vectorx.push_back(xcoord);
        vectory.push_back(ycoord);
        //  cout << vectory[i] << endl;
    }

    vectorLayer->SetData(vectorx, vectory);
    vectorLayer->SetContinuity(true);
    wxPen vectorpen(*wxBLUE, 2, wxPENSTYLE_SOLID);
    vectorLayer->SetPen(vectorpen);
    vectorLayer->SetDrawOutsideMargins(false);
    graf->AddLayer(vectorLayer);
    graf->AddLayer(xaxis);
    graf->AddLayer(yaxis);
    graf->Fit();
}
      else {
      wxMessageBox("podaj dane");
    }
}

void MyFrame::OnGraf4(wxCommandEvent& event) {
    if (zmienne == true) {
    std::auto_ptr <Obliczenia> obliczenia(new Obliczenia(N, lambda, dom1, dom2));

    graf->DelLayer(vectorLayer);
    graf->DelLayer(xaxis);
    graf->DelLayer(yaxis);

    wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    
    xaxis->SetName(wxT("x/a"));
    yaxis->SetName(wxT("H02(x/a) [A/m]"));

    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);
    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);



    graf->SetMargins(10, 10, 50, 100);



    vectorx.clear();
    vectory.clear();

    obliczenia->Wykres4();

    for (int i = 0; i < 1000; i++) {

        xcoord = obliczenia->xcord[i];
        ycoord = obliczenia->ycord[i];

        vectorx.push_back(xcoord);
        vectory.push_back(ycoord);
        //  cout << vectory[i] << endl;
    }

    vectorLayer->SetData(vectorx, vectory);
    vectorLayer->SetContinuity(true);
    wxPen vectorpen(*wxBLUE, 2, wxPENSTYLE_SOLID);
    vectorLayer->SetPen(vectorpen);
    vectorLayer->SetDrawOutsideMargins(false);
    graf->AddLayer(vectorLayer);
    graf->AddLayer(xaxis);
    graf->AddLayer(yaxis);
    graf->Fit();

}
      else {
      wxMessageBox("podaj dane");
    }
}

void MyFrame::OnGraf5(wxCommandEvent& event) {
    if (zmienne == true) {
    std::auto_ptr <Obliczenia> obliczenia(new Obliczenia(N, lambda, dom1, dom2));
    graf->DelLayer(vectorLayer);
    graf->DelLayer(xaxis);
    graf->DelLayer(yaxis);

    wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
   
    xaxis->SetName(wxT("x/a"));
    yaxis->SetName(wxT("E02(x/a) [V/m]]"));

    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);
    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);



    graf->SetMargins(10, 10, 50, 100);



    vectorx.clear();
    vectory.clear();

    obliczenia->Wykres5();

    for (int i = 0; i < 1000; i++) {

        xcoord = obliczenia->xcord[i];
        ycoord = obliczenia->ycord[i];

        vectorx.push_back(xcoord);
        vectory.push_back(ycoord);
        //  cout << vectory[i] << endl;
    }

    vectorLayer->SetData(vectorx, vectory);
    vectorLayer->SetContinuity(true);
    wxPen vectorpen(*wxBLUE, 2, wxPENSTYLE_SOLID);
    vectorLayer->SetPen(vectorpen);
    vectorLayer->SetDrawOutsideMargins(false);
    graf->AddLayer(vectorLayer);
    graf->AddLayer(xaxis);
    graf->AddLayer(yaxis);
    graf->Fit();
    }
    else {
        wxMessageBox("podaj dane");
    }
}

void MyFrame::OnGraf6(wxCommandEvent& event) {
    if (zmienne == true) {
    std::auto_ptr <Obliczenia> obliczenia(new Obliczenia(N, lambda, dom1, dom2));
    graf->DelLayer(vectorLayer);
    graf->DelLayer(xaxis);
    graf->DelLayer(yaxis);

    wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);

    xaxis->SetName(wxT("x/a"));
    yaxis->SetName(wxT("E0/E0max"));

    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);
    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);



    graf->SetMargins(10, 10, 50, 100);



    vectorx.clear();
    vectory.clear();
    
    obliczenia->Wykres6();

    for (int i = 0; i < 2000; i++) {

        xcoord = obliczenia->xcord[i];
        ycoord = obliczenia->ycord[i];

        vectorx.push_back(xcoord);
        vectory.push_back(ycoord);
        //  cout << vectory[i] << endl;
    }

    vectorLayer->SetData(vectorx, vectory);
    vectorLayer->SetContinuity(true);
    wxPen vectorpen(*wxBLUE, 2, wxPENSTYLE_SOLID);
    vectorLayer->SetPen(vectorpen);
    vectorLayer->SetDrawOutsideMargins(false);
    graf->AddLayer(vectorLayer);
    graf->AddLayer(xaxis);
    graf->AddLayer(yaxis);
    graf->Fit();

}
      else {
      wxMessageBox("podaj dane");
    }
}

void MyFrame::OnGraf7(wxCommandEvent& event) {
    if (zmienne == true) {
    std::auto_ptr <Obliczenia> obliczenia(new Obliczenia(N, lambda, dom1, dom2));
    graf->DelLayer(vectorLayer);
    graf->DelLayer(xaxis);
    graf->DelLayer(yaxis);

    wxFont graphFont(11, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL);
    

    xaxis->SetName(wxT("x/a"));
    yaxis->SetName(wxT("H0/H0 max"));

    xaxis->SetFont(graphFont);
    yaxis->SetFont(graphFont);
    xaxis->SetDrawOutsideMargins(false);
    yaxis->SetDrawOutsideMargins(false);



    graf->SetMargins(10, 10, 50, 100);



    vectorx.clear();
    vectory.clear();
    obliczenia->Wykres7();

    for (int i = 0; i < 2000; i++) {

        xcoord = obliczenia->xcord[i];
        ycoord = obliczenia->ycord[i];

        vectorx.push_back(xcoord);
        vectory.push_back(ycoord);
        //  cout << vectory[i] << endl;
    }

    vectorLayer->SetData(vectorx, vectory);
    vectorLayer->SetContinuity(true);
    wxPen vectorpen(*wxBLUE, 2, wxPENSTYLE_SOLID);
    vectorLayer->SetPen(vectorpen);
    vectorLayer->SetDrawOutsideMargins(false);
    graf->AddLayer(vectorLayer);
    graf->AddLayer(xaxis);
    graf->AddLayer(yaxis);
    graf->Fit();
    }
    else {
        wxMessageBox("podaj dane");
    }
}

//wyniki

void MyFrame::OnWynik1(wxCommandEvent& event) {
    if (zmienne == true) {
    
    MyFrame1* wynik1 = new MyFrame1("Zmienne ", wxPoint(400, 600), wxSize(500, 500), wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxRESIZE_BORDER);



    


    wynik1->menuPLikWynik->Append(ID_OnZapisz_1, "&Zapisz\tCtrl-S", "zapisano");
    wynik1->menuPLikWynik->AppendSeparator();
    wynik1->menuPLikWynik->Append(wxID_EXIT, "&Wyjdz");
    

    

   
   
    std::auto_ptr <Obliczenia> obliczenia(new Obliczenia(N, lambda, dom1, dom2));

    wynik1->lambda = lambda;
    wynik1->dom1 = dom1;
    wynik1->dom2 = dom2;
    wynik1->N = N;

    wxGrid* grid = new wxGrid(wynik1->mainPane, wxID_ANY);
    grid->CreateGrid(1, 4);

    //ustawniane kolumny po lewej od 1 do potrzebnego zakresu 
    for (int n = 0; n < 1; n++)
    {
        grid->SetRowLabelValue(n, wxString::Format("%i", n + 1));


    }





    grid->SetColLabelValue(0, "L");
    grid->SetColLabelValue(1, "n1");
    grid->SetColLabelValue(2, "n2");
    grid->SetColLabelValue(3, "pi");




   
    
    

    std::stringstream Lstream;
    Lstream << std::fixed << std::setprecision(9) << obliczenia->lambda;
    std::string L = Lstream.str();


    std::stringstream n1stream;
    n1stream << std::fixed << std::setprecision(17) << obliczenia->n1;
    std::string n1 = n1stream.str();


    std::stringstream n2stream;
    n2stream << std::fixed << std::setprecision(17) << obliczenia->n2;
    std::string n2 = n2stream.str();


    grid->SetCellValue(0, 0, L);
    grid->SetCellValue(0, 1, n1);
    grid->SetCellValue(0, 2, n2);
    grid->SetCellValue(0, 3, "3.14159265358979323846");





    grid->Fit();
    wynik1->sizer->Add(grid,1, wxEXPAND);
    
    wynik1->mainPane->SetSizerAndFit(wynik1->sizer);
    
  


    wynik1->Show(true);

}
      else {
      wxMessageBox("podaj dane");
    }
 

}

void MyFrame::OnWynik2(wxCommandEvent& event) {
    if (zmienne == true) {
    MyFrame1* wynik2 = new MyFrame1("argumenty poprzedzajace wystapienie miejsca zerowego ", wxPoint(400, 600), wxSize(500, 500), wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxRESIZE_BORDER);

    wynik2->menuPLikWynik->Append(ID_OnZapisz_2, "&Zapisz\tCtrl-S", "zapisano");
    wynik2->menuPLikWynik->AppendSeparator();
    wynik2->menuPLikWynik->Append(wxID_EXIT, "&Wyjdz");

    Obliczenia obliczenia(N, lambda, dom1, dom2);
    obliczenia.wynik2();
   
    wynik2->lambda = lambda;
    wynik2->dom1 = dom1;
    wynik2->dom2 = dom2;
    wynik2->N = N;


    wxGrid* grid = new wxGrid(wynik2->mainPane, wxID_ANY);
    grid->CreateGrid(obliczenia.licznik2 , 1);

    //ustawniane kolumny po lewej od 1 do potrzebnego zakresu 
    for (int n = 0; n < obliczenia.licznik2; n++)
    {
        grid->SetRowLabelValue(n, wxString::Format("%i", n + 1));


    }





    grid->SetColLabelValue(0, "argumenty poprzedzajace wystapienie miejsca zerowego");


    std::stringstream wynik2stream;

    for (obliczenia.licznik = 1; obliczenia.licznik <= obliczenia.licznik2; obliczenia.licznik++)
    {
        
        wynik2stream << std::fixed << std::setprecision(13) << obliczenia.tablica3[obliczenia.licznik];
        std::string wynik2 = wynik2stream.str();

        grid->SetCellValue(obliczenia.licznik -1, 0, wynik2);
     
        wynik2stream.str(std::string());
    }
    
 
    




    grid->Fit();
    wynik2->sizer->Add(grid, 1, wxEXPAND);
    wynik2->mainPane->SetSizerAndFit(wynik2->sizer);




    wynik2->Show(true);


    }
    else {
        wxMessageBox("podaj dane");
    }


}

void MyFrame::OnWynik3(wxCommandEvent& event) {
    if (zmienne == true) {

    MyFrame1* wynik3 = new MyFrame1(" BetaC i HDBetaC oraz miejsca zerowe ", wxPoint(400, 600), wxSize(500, 500), wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxRESIZE_BORDER);

    wynik3->menuPLikWynik->Append(ID_OnZapisz_3, "&Zapisz\tCtrl-S", "zapisano");
    wynik3->menuPLikWynik->AppendSeparator();
    wynik3->menuPLikWynik->Append(wxID_EXIT, "&Wyjdz");

    Obliczenia obliczenia(N, lambda, dom1, dom2);
    obliczenia.wynik3();

    wynik3->lambda = lambda;
    wynik3->dom1 = dom1;
    wynik3->dom2 = dom2;
    wynik3->N = N;


    wxGrid* grid = new wxGrid(wynik3->mainPane, wxID_ANY);
    grid->CreateGrid(obliczenia.LicznikPom1, 4);

    //ustawniane kolumny po lewej od 1 do potrzebnego zakresu 
    for (int n = 0; n < obliczenia.LicznikPom1; n++)
    {
        grid->SetRowLabelValue(n, wxString::Format("%i", n + 1));


    }





    grid->SetColLabelValue(0, "BetaC");
    grid->SetColLabelValue(1, "HDBetaC");
    grid->SetColLabelValue(2, "Miejsce 0 : BetaC");
    grid->SetColLabelValue(3, "Miejsce 0 : HDBetaC");


    std::stringstream wynik3stream;
    std::stringstream wynik3stream_2;

    for (obliczenia.licznik = 1; obliczenia.licznik < obliczenia.LicznikPom1; obliczenia.licznik++)
    {

        wynik3stream << std::fixed << std::setprecision(13) << obliczenia.TablicaPom1[obliczenia.licznik];

        std::string wynik3 = wynik3stream.str();


        grid->SetCellValue(obliczenia.licznik - 1, 0, wynik3);

        wynik3stream.str(std::string());


        wynik3stream_2 << std::fixed << std::setprecision(13) << obliczenia.TablicaPom2[obliczenia.licznik];

        std::string wynik3_2 = wynik3stream_2.str();


        grid->SetCellValue(obliczenia.licznik - 1, 1, wynik3_2);

        wynik3stream_2.str(std::string());



    }


    std::stringstream wynik3stream_3;
    std::stringstream wynik3stream_4;


     for (obliczenia.licznik = 1; obliczenia.licznik < obliczenia.LicznikPom2; obliczenia.licznik++)
    {

         wynik3stream_3 << std::fixed << std::setprecision(13) << obliczenia.tablica4[obliczenia.licznik];

        std::string wynik3_3 = wynik3stream_3.str();


        grid->SetCellValue(obliczenia.licznik - 1, 2, wynik3_3);

        wynik3stream_3.str(std::string());





        wynik3stream_4 << std::fixed << std::setprecision(13) << obliczenia.TablicaPom3[obliczenia.licznik];

        std::string wynik3_4 = wynik3stream_4.str();


        grid->SetCellValue(obliczenia.licznik - 1, 3, wynik3_4);

        wynik3stream_4.str(std::string());



    }






    grid->Fit();
    wynik3->sizer->Add(grid, 1, wxEXPAND);
    wynik3->mainPane->SetSizerAndFit(wynik3->sizer);




    wynik3->Show(true);

    }
      else {
      wxMessageBox("podaj dane");
    }

}

void MyFrame::OnWynik4(wxCommandEvent& event) {
    if (zmienne == true) {
    MyFrame1* wynik4 = new MyFrame1("Miejsca zerowe ", wxPoint(400, 600), wxSize(500, 500), wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxRESIZE_BORDER);

    wynik4->menuPLikWynik->Append(ID_OnZapisz_4, "&Zapisz\tCtrl-S", "zapisano");
    wynik4->menuPLikWynik->AppendSeparator();
    wynik4->menuPLikWynik->Append(wxID_EXIT, "&Wyjdz");


    Obliczenia obliczenia(N, lambda, dom1, dom2);
    obliczenia.wynik4();

    wynik4->lambda = lambda;
    wynik4->dom1 = dom1;
    wynik4->dom2 = dom2;
    wynik4->N = N;


    wxGrid* grid = new wxGrid(wynik4->mainPane, wxID_ANY);
    
    grid->CreateGrid(obliczenia.licznik2, 1);

    //ustawniane kolumny po lewej od 1 do potrzebnego zakresu 
    for (int n = 0; n < obliczenia.licznik2; n++)
    {
        grid->SetRowLabelValue(n, wxString::Format("%i", n + 1));


    }





    grid->SetColLabelValue(0, "Miejsca zerowe");


    std::stringstream wynik2stream;

    for (obliczenia.licznik = 1; obliczenia.licznik <= obliczenia.licznik2; obliczenia.licznik++)
    {

        wynik2stream << std::fixed << std::setprecision(13) << obliczenia.tablica3[obliczenia.licznik];
        std::string wynik2 = wynik2stream.str();

        grid->SetCellValue(obliczenia.licznik - 1, 0, wynik2);

        wynik2stream.str(std::string());
    }







    grid->Fit();
    wynik4->sizer->Add(grid, 1, wxEXPAND);
    wynik4->mainPane->SetSizerAndFit(wynik4->sizer);




    wynik4->Show(true);



    }
    else {
        wxMessageBox("podaj dane");
    }

}

void MyFrame::OnWynik5(wxCommandEvent& event) {
    if (zmienne == true) {
    MyFrame1* wynik5 = new MyFrame1("AH, CH1 i CH2 ", wxPoint(400, 600), wxSize(500, 500), wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxRESIZE_BORDER);

    wynik5->menuPLikWynik->Append(ID_OnZapisz_5, "&Zapisz\tCtrl-S", "zapisano");
    wynik5->menuPLikWynik->AppendSeparator();
    wynik5->menuPLikWynik->Append(wxID_EXIT, "&Wyjdz");


    Obliczenia obliczenia(N, lambda, dom1, dom2);
    obliczenia.wynik5();

    wynik5->lambda = lambda;
    wynik5->dom1 = dom1;
    wynik5->dom2 = dom2;
    wynik5->N = N;

    wxGrid* grid = new wxGrid(wynik5->mainPane, wxID_ANY);
    grid->CreateGrid(1, 3);

    //ustawniane kolumny po lewej od 1 do potrzebnego zakresu 
    for (int n = 0; n < 1; n++)
    {
        grid->SetRowLabelValue(n, wxString::Format("%i", n + 1));


    }





    grid->SetColLabelValue(0, "AH");
    grid->SetColLabelValue(1, "CH1");
    grid->SetColLabelValue(2, "CH2");
  








    std::stringstream AHstream;
    AHstream << std::fixed << std::setprecision(9) << obliczenia.AH;
    std::string AH = AHstream.str();


    std::stringstream CH1stream;
    CH1stream << std::fixed << std::setprecision(17) << obliczenia.CH1;
    std::string CH1 = CH1stream.str();


    std::stringstream CH2stream;
    CH2stream << std::fixed << std::setprecision(17) << obliczenia.CH2;
    std::string CH2 = CH2stream.str();


    grid->SetCellValue(0, 0, AH);
    grid->SetCellValue(0, 1, CH1);
    grid->SetCellValue(0, 2, CH2);
    





    grid->Fit();
    wynik5->sizer->Add(grid, 1, wxEXPAND);
    wynik5->mainPane->SetSizerAndFit(wynik5->sizer);




    wynik5->Show(true);


}
      else {
      wxMessageBox("podaj dane");
    }

}

void MyFrame::OnWynik6(wxCommandEvent& event) {
    if (zmienne == true) {
    MyFrame1* wynik6 = new MyFrame1("E01 oraz H01 max ", wxPoint(400, 600), wxSize(500, 500), wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxRESIZE_BORDER);

    wynik6->menuPLikWynik->Append(ID_OnZapisz_6, "&Zapisz\tCtrl-S", "zapisano");
    wynik6->menuPLikWynik->AppendSeparator();
    wynik6->menuPLikWynik->Append(wxID_EXIT, "&Wyjdz");

    Obliczenia obliczenia(N, lambda, dom1, dom2);
    obliczenia.wynik6_7();

    wynik6->lambda = lambda;
    wynik6->dom1 = dom1;
    wynik6->dom2 = dom2;
    wynik6->N = N;

    wxGrid* grid = new wxGrid(wynik6->mainPane, wxID_ANY);
    grid->CreateGrid(1, 2);

    //ustawniane kolumny po lewej od 1 do potrzebnego zakresu 
    for (int n = 0; n < 1; n++)
    {
        grid->SetRowLabelValue(n, wxString::Format("%i", n + 1));


    }





    grid->SetColLabelValue(0, "E01max");
    grid->SetColLabelValue(1, "H01max");
   








    std::stringstream E01maxstream;
    E01maxstream << std::fixed << std::setprecision(9) << obliczenia.E01max;
    std::string E01max = E01maxstream.str();


    std::stringstream H01maxstream;
    H01maxstream << std::fixed << std::setprecision(17) << obliczenia.H01max;
    std::string H01max = H01maxstream.str();





    grid->SetCellValue(0, 0, E01max);
    grid->SetCellValue(0, 1, H01max);
    



    grid->Fit();
    wynik6->sizer->Add(grid, 1, wxEXPAND);
    wynik6->mainPane->SetSizerAndFit(wynik6->sizer);




    wynik6->Show(true);

    }
    else {
        wxMessageBox("podaj dane");
    }

}

void MyFrame::OnWynik7(wxCommandEvent& event) {
    if (zmienne == true) {
    MyFrame1* wynik7 = new MyFrame1("E01,E02,H01,H02 ", wxPoint(400, 600), wxSize(500, 500), wxMINIMIZE_BOX | wxSYSTEM_MENU | wxCAPTION | wxCLOSE_BOX | wxCLIP_CHILDREN | wxRESIZE_BORDER);

    wynik7->menuPLikWynik->Append(ID_OnZapisz_7, "&Zapisz\tCtrl-S", "zapisano");
    wynik7->menuPLikWynik->AppendSeparator();
    wynik7->menuPLikWynik->Append(wxID_EXIT, "&Wyjdz");

    Obliczenia obliczenia(N,lambda,dom1,dom2);
    obliczenia.wynik6_7();

    wynik7->lambda = lambda;
    wynik7->dom1 = dom1;
    wynik7->dom2 = dom2;
    wynik7->N = N;
    wxGrid* grid = new wxGrid(wynik7->mainPane, wxID_ANY);
    grid->CreateGrid(1, 4);

    //ustawniane kolumny po lewej od 1 do potrzebnego zakresu 
    for (int n = 0; n < 1; n++)
    {
        grid->SetRowLabelValue(n, wxString::Format("%i", n + 1));


    }





    grid->SetColLabelValue(0, "E01(a)");
    grid->SetColLabelValue(1, "E02(a)");
    grid->SetColLabelValue(2, "H01(a)");
    grid->SetColLabelValue(3, "H02(a)");









    std::stringstream E01stream;
    E01stream << std::fixed << std::setprecision(17) << obliczenia.E01_TAB[999];
    std::string E01 = E01stream.str();


    std::stringstream E02stream;
    E02stream << std::fixed << std::setprecision(17) << obliczenia.E02_TAB[0];
    std::string E02 = E02stream.str();


    std::stringstream H01stream;
    H01stream << std::fixed << std::setprecision(17) << obliczenia.H01_TAB[999];
    std::string H01 = H01stream.str();


    std::stringstream H02stream;
    H02stream << std::fixed << std::setprecision(17) << obliczenia.H02_TAB[0];
    std::string H02 = H02stream.str();




    grid->SetCellValue(0, 0, E01);
    grid->SetCellValue(0, 1, E02);
    grid->SetCellValue(0, 2, H01);
    grid->SetCellValue(0, 3, H02);




    grid->Fit();
    wynik7->sizer->Add(grid, 1, wxEXPAND);
    wynik7->mainPane->SetSizerAndFit(wynik7->sizer);




    wynik7->Show(true);

}
      else {
      wxMessageBox("podaj dane");
    }



}

void MyFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("W miejscu długość fali proszę podać długość fali w mikrometrach, zakres to od 0.9 do 1.89 mikrometra, dla domieszkowania n_GeO2_3_1 i n_F_1 od 1.4 do 1.89. W polu miejsce zerowe podajemy liczbę określającą które miejsce zerowe od prawej strony badamy. Z listy domieszkowań upewnijmy się że domieszkowania nie są identyczne. aby wyświetlić wykresy klikamy w menu wyresy i wybieramy wykres, natomiast jeżeli chcemy zobaczyć wyniki klikamy w menu wynik oraz wyświetlamy interesujący nas wynik. Aby zapisać zrzut ekranu wykresu lub któryś z wyników klikamy plik -> zapisz oraz wybieramy nazwę i miejsce do zapisania pliku. ","Pomoc",wxOK | wxICON_INFORMATION);
}

void MyFrame::OnOblicz(wxCommandEvent& event)
{

    graf->DelLayer(vectorLayer);
    zmienne = false;
    wxString stringFala = Dlugosc_Fali->GetValue();
    wxString stringN = Podaj_N->GetValue();
  

    
 
    
    dom1 = Domieszkowanie1->GetSelection();
    dom2 = Domieszkowanie2->GetSelection();
    if (!stringFala.ToDouble(&lambda)) {
    
        wxMessageBox("Błednie wprowadzona długość fali");
    
    }

    else  if (lambda < 0.9) {

        wxMessageBox("Błednie wprowadzona długość fali upewnij się że długość fali wynosi conajmniej 0.9 mikrometra");

    }

    else  if (lambda >= 1.89) {

        wxMessageBox("Błednie wprowadzona długość fali upewnij się że długość fali wynosi poniżej 1.9 mikrometra");

    }

    else  if (!stringN.ToInt(&N) || N <= 0 ) {

        wxMessageBox("Błednie podane miejsce zerowe upewnij sie że jest to liczba dodatnia większa od 0");

    }

    

    else   if (dom1 == 0 || dom2 == 0) {

        wxMessageBox("Błednie wprowadzone domieszkowanie, prosze wybrać domieszkowanie z listy");


    }

    else   if (dom1 == 1 && dom2 == 2 && lambda <1.4) {

        wxMessageBox("Jeżeli wybrane jest domieszkowanie n_GeO2_3_1 i n_F_1 upewnij sie że długość fali wynosi conajmniej 1.4 mikrometra");


    }

    else   if (dom1 ==  dom2 +1) {

        wxMessageBox("Domieszkowania nie moga być takie same ");


    }
    else {
        
        zmienne = true;
        OnGraf1(event);
    }
   
    
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

       // int size = wynik->GetNumberOfLines();
         
       

       // for (int i = 0; i < size; i++) {
        //    file.AddLine(wynik->GetLineText(i));
            file.Write();
       // }

        file.Close();

        wxLogMessage("zapisano");
        
    }

    if (response != wxID_OK) {
        wxLogMessage("Zapisywanie przerwane");
    }



}


// Zapisy dla każdego wyniku 

void MyFrame1::OnZapisz_1(wxCommandEvent & event){
    Obliczenia obliczenia(N, lambda, dom1, dom2);

    wxString firstFilename = wxT("material");
    wxString caption = wxT("Nazwa:");
    wxString wildcard = wxT("Material (*.txt)");
    wxString defaultDir = wxT("c:\\temp");
    wxString saveFilename = wxEmptyString;

    wxFileDialog* OnSaveFileMaterial = new wxFileDialog(mainPane, wxT("Podaj nazwe oraz lokalizacje pliku:"),
        wxT(""), wxT(""), wxT("Material (*.txt)|*.txt"), wxFD_SAVE); // | wxFD_OVERWRITE_PROMPT );

    int response = OnSaveFileMaterial->ShowModal();
    if (response == wxID_OK)
    {
        saveFilename = OnSaveFileMaterial->GetPath();

        wxTextFile file(saveFilename);
       
        if (file.Exists() == true ) 
        {
            wxLogMessage("plik o takiej nazwie istnieje prosze podaj inna nazwe");
            
        }


        else {

            file.Create();
            file.Open();




            std::stringstream Lstream;
            Lstream << std::fixed << std::setprecision(9) << obliczenia.lambda;
            std::string L = "L = " + Lstream.str();


            std::stringstream n1stream;
            n1stream << std::fixed << std::setprecision(17) << obliczenia.n1;
            std::string n1 = "n1 = " + n1stream.str();


            std::stringstream n2stream;
            n2stream << std::fixed << std::setprecision(17) << obliczenia.n2;
            std::string n2 = "n2 = " +  n2stream.str();

        


            file.AddLine(L);
            file.AddLine(n1);
            file.AddLine(n2);
            file.AddLine("Pi = 3.14159265358979323846");


            file.Write();


            file.Close();

            wxLogMessage("zapisano");
        }
    }

    if (response != wxID_OK) {
        wxLogMessage("Zapisywanie przerwane");
    }
    delete OnSaveFileMaterial;
}

void MyFrame1::OnZapisz_2(wxCommandEvent& event)
{

    Obliczenia obliczenia(N, lambda, dom1, dom2);
    obliczenia.wynik2();

    wxString firstFilename = wxT("material");
    wxString caption = wxT("Nazwa:");
    wxString wildcard = wxT("Material (*.txt)");
    wxString defaultDir = wxT("c:\\temp");
    wxString saveFilename = wxEmptyString;

    wxFileDialog* OnSaveFileMaterial = new wxFileDialog(mainPane, wxT("Podaj nazwe oraz lokalizacje pliku:"),
        wxT(""), wxT(""), wxT("Material (*.txt)|*.txt"), wxFD_SAVE); // | wxFD_OVERWRITE_PROMPT );

    int response = OnSaveFileMaterial->ShowModal();
    if (response == wxID_OK)
    {
        saveFilename = OnSaveFileMaterial->GetPath();

        wxTextFile file(saveFilename);

        if (file.Exists() == true)
        {
            wxLogMessage("plik o takiej nazwie istnieje prosze podaj inna nazwe");

        }


        else {

            file.Create();
            file.Open();




            




            file.AddLine("argumenty poprzedzajace wystapienie miejsca zerowego");



            std::stringstream wynik2stream;

            for (obliczenia.licznik = 1; obliczenia.licznik <= obliczenia.licznik2; obliczenia.licznik++)
            {

                wynik2stream << std::fixed << std::setprecision(13) << obliczenia.tablica3[obliczenia.licznik];
                std::string wynik2 = wynik2stream.str();

   
                wynik2stream.str(std::string());


                file.AddLine(wynik2);
               
            }

          

            file.Write();
            file.Close();

            wxLogMessage("zapisano");
        }
    }

    if (response != wxID_OK) {
        wxLogMessage("Zapisywanie przerwane");
    }

    delete OnSaveFileMaterial;
}

void MyFrame1::OnZapisz_3(wxCommandEvent& event) {


    Obliczenia obliczenia(N, lambda, dom1, dom2);
    obliczenia.wynik3();

    wxString firstFilename = wxT("material");
    wxString caption = wxT("Nazwa:");
    wxString wildcard = wxT("Material (*.txt)");
    wxString defaultDir = wxT("c:\\temp");
    wxString saveFilename = wxEmptyString;

    wxFileDialog* OnSaveFileMaterial = new wxFileDialog(mainPane, wxT("Podaj nazwe oraz lokalizacje pliku:"),
        wxT(""), wxT(""), wxT("Material (*.txt)|*.txt"), wxFD_SAVE); // | wxFD_OVERWRITE_PROMPT );

    int response = OnSaveFileMaterial->ShowModal();
    if (response == wxID_OK)
    {
        saveFilename = OnSaveFileMaterial->GetPath();

        wxTextFile file(saveFilename);

        if (file.Exists() == true)
        {
            wxLogMessage("plik o takiej nazwie istnieje prosze podaj inna nazwe");

        }


        else {

            file.Create();
            file.Open();


            file.AddLine("BetaC");


            std::stringstream wynik3stream;
            std::stringstream wynik3stream_2;

            for (obliczenia.licznik = 1; obliczenia.licznik < obliczenia.LicznikPom1; obliczenia.licznik++)
            {

                wynik3stream << std::fixed << std::setprecision(13) << obliczenia.TablicaPom1[obliczenia.licznik];

                std::string wynik3 = wynik3stream.str();

                wynik3stream.str(std::string());

                file.AddLine(wynik3);
            }


            file.AddLine("HDBetaC");

            for (obliczenia.licznik = 1; obliczenia.licznik < obliczenia.LicznikPom1; obliczenia.licznik++) {

                wynik3stream_2 << std::fixed << std::setprecision(13) << obliczenia.TablicaPom2[obliczenia.licznik];

                std::string wynik3_2 = wynik3stream_2.str();


              

                wynik3stream_2.str(std::string());


                file.AddLine(wynik3_2);
            }


            
            
            

            file.AddLine("Miejsce 0 : BetaC");

            std::stringstream wynik3stream_3;
            std::stringstream wynik3stream_4;


            for (obliczenia.licznik = 1; obliczenia.licznik < obliczenia.LicznikPom2; obliczenia.licznik++)
            {

                wynik3stream_3 << std::fixed << std::setprecision(13) << obliczenia.tablica4[obliczenia.licznik];

                std::string wynik3_3 = wynik3stream_3.str();


                

                wynik3stream_3.str(std::string());

                file.AddLine(wynik3_3);

            }


            file.AddLine("Miejsce 0 : HDBetaC");

            for (obliczenia.licznik = 1; obliczenia.licznik < obliczenia.LicznikPom2; obliczenia.licznik++)
            {


                wynik3stream_4 << std::fixed << std::setprecision(13) << obliczenia.TablicaPom3[obliczenia.licznik];

                std::string wynik3_4 = wynik3stream_4.str();


                

                wynik3stream_4.str(std::string());

                file.AddLine(wynik3_4);

            }



            file.Write();
            file.Close();

            wxLogMessage("zapisano");
        }


        if (response != wxID_OK) {
            wxLogMessage("Zapisywanie przerwane");
        }
    }
    delete OnSaveFileMaterial;
}
    
void MyFrame1::OnZapisz_4(wxCommandEvent& event){

    Obliczenia obliczenia(N, lambda, dom1, dom2);
    obliczenia.wynik4();

    wxString firstFilename = wxT("material");
    wxString caption = wxT("Nazwa:");
    wxString wildcard = wxT("Material (*.txt)");
    wxString defaultDir = wxT("c:\\temp");
    wxString saveFilename = wxEmptyString;

    wxFileDialog* OnSaveFileMaterial = new wxFileDialog(mainPane, wxT("Podaj nazwe oraz lokalizacje pliku:"),
        wxT(""), wxT(""), wxT("Material (*.txt)|*.txt"), wxFD_SAVE); // | wxFD_OVERWRITE_PROMPT );

    int response = OnSaveFileMaterial->ShowModal();
    if (response == wxID_OK)
    {
        saveFilename = OnSaveFileMaterial->GetPath();

        wxTextFile file(saveFilename);

        if (file.Exists() == true)
        {
            wxLogMessage("plik o takiej nazwie istnieje prosze podaj inna nazwe");

        }


        else {

            file.Create();
            file.Open();




           file.AddLine("Miejsca zerowe");


            std::stringstream wynik2stream;

            for (obliczenia.licznik = 1; obliczenia.licznik <= obliczenia.licznik2; obliczenia.licznik++)
            {

                wynik2stream << std::fixed << std::setprecision(13) << obliczenia.tablica3[obliczenia.licznik];
                std::string wynik2 = wynik2stream.str();

               

                wynik2stream.str(std::string());

                file.AddLine(wynik2);
            }






            file.Write();


            file.Close();

            wxLogMessage("zapisano");
        }
    }

    if (response != wxID_OK) {
        wxLogMessage("Zapisywanie przerwane");
    }
    delete OnSaveFileMaterial;
}

void MyFrame1::OnZapisz_5(wxCommandEvent& event){

    Obliczenia obliczenia(N, lambda, dom1, dom2);
    obliczenia.wynik5();

    wxString firstFilename = wxT("material");
    wxString caption = wxT("Nazwa:");
    wxString wildcard = wxT("Material (*.txt)");
    wxString defaultDir = wxT("c:\\temp");
    wxString saveFilename = wxEmptyString;

    wxFileDialog* OnSaveFileMaterial = new wxFileDialog(mainPane, wxT("Podaj nazwe oraz lokalizacje pliku:"),
        wxT(""), wxT(""), wxT("Material (*.txt)|*.txt"), wxFD_SAVE); // | wxFD_OVERWRITE_PROMPT );

    int response = OnSaveFileMaterial->ShowModal();
    if (response == wxID_OK)
    {
        saveFilename = OnSaveFileMaterial->GetPath();

        wxTextFile file(saveFilename);

        if (file.Exists() == true)
        {
            wxLogMessage("plik o takiej nazwie istnieje prosze podaj inna nazwe");

        }


        else {

            file.Create();
            file.Open();




            std::stringstream AHstream;
            AHstream << std::fixed << std::setprecision(9) << obliczenia.AH;
            std::string AH ="AH = " + AHstream.str();


            std::stringstream CH1stream;
            CH1stream << std::fixed << std::setprecision(17) << obliczenia.CH1;
            std::string CH1 = "CH1 = "+ CH1stream.str();


            std::stringstream CH2stream;
            CH2stream << std::fixed << std::setprecision(17) << obliczenia.CH2;
            std::string CH2 = "CH2 = " + CH2stream.str();




            file.AddLine(AH);
            file.AddLine(CH1);
            file.AddLine(CH2);

            file.Write();


            file.Close();

            wxLogMessage("zapisano");
        }
    }

    if (response != wxID_OK) {
        wxLogMessage("Zapisywanie przerwane");
    }
    delete OnSaveFileMaterial;
}

void MyFrame1::OnZapisz_6(wxCommandEvent& event){

    Obliczenia obliczenia(N, lambda, dom1, dom2);
    obliczenia.wynik6_7();

    wxString firstFilename = wxT("material");
    wxString caption = wxT("Nazwa:");
    wxString wildcard = wxT("Material (*.txt)");
    wxString defaultDir = wxT("c:\\temp");
    wxString saveFilename = wxEmptyString;

    wxFileDialog* OnSaveFileMaterial = new wxFileDialog(mainPane, wxT("Podaj nazwe oraz lokalizacje pliku:"),
        wxT(""), wxT(""), wxT("Material (*.txt)|*.txt"), wxFD_SAVE); // | wxFD_OVERWRITE_PROMPT );

    int response = OnSaveFileMaterial->ShowModal();
    if (response == wxID_OK)
    {
        saveFilename = OnSaveFileMaterial->GetPath();

        wxTextFile file(saveFilename);

        if (file.Exists() == true)
        {
            wxLogMessage("plik o takiej nazwie istnieje prosze podaj inna nazwe");

        }


        else {

            file.Create();
            file.Open();




            std::stringstream E01maxstream;
            E01maxstream << std::fixed << std::setprecision(9) << obliczenia.E01max;
            std::string E01max = "E01max = "+E01maxstream.str();


            std::stringstream H01maxstream;
            H01maxstream << std::fixed << std::setprecision(17) << obliczenia.H01max;
            std::string H01max = "H01max = " + H01maxstream.str();





           


            file.AddLine(E01max);
            file.AddLine(H01max);
           


            file.Write();


            file.Close();

            wxLogMessage("zapisano");
        }
    }

    if (response != wxID_OK) {
        wxLogMessage("Zapisywanie przerwane");
    }
    delete OnSaveFileMaterial;
}

void MyFrame1::OnZapisz_7(wxCommandEvent& event){

    Obliczenia obliczenia(N, lambda, dom1, dom2);
    obliczenia.wynik6_7();

    wxString firstFilename = wxT("material");
    wxString caption = wxT("Nazwa:");
    wxString wildcard = wxT("Material (*.txt)");
    wxString defaultDir = wxT("c:\\temp");
    wxString saveFilename = wxEmptyString;

    wxFileDialog* OnSaveFileMaterial = new wxFileDialog(mainPane, wxT("Podaj nazwe oraz lokalizacje pliku:"),
        wxT(""), wxT(""), wxT("Material (*.txt)|*.txt"), wxFD_SAVE); // | wxFD_OVERWRITE_PROMPT );

    int response = OnSaveFileMaterial->ShowModal();
    if (response == wxID_OK)
    {
        saveFilename = OnSaveFileMaterial->GetPath();

        wxTextFile file(saveFilename);

        if (file.Exists() == true)
        {
            wxLogMessage("plik o takiej nazwie istnieje prosze podaj inna nazwe");

        }


        else {

            file.Create();
            file.Open();




            std::stringstream E01stream;
            E01stream << std::fixed << std::setprecision(17) << obliczenia.E01_TAB[999];
            std::string E01 = "E01 = " + E01stream.str();


            std::stringstream E02stream;
            E02stream << std::fixed << std::setprecision(17) << obliczenia.E02_TAB[0];
            std::string E02 = "E02 = " + E02stream.str();


            std::stringstream H01stream;
            H01stream << std::fixed << std::setprecision(17) << obliczenia.H01_TAB[999];
            std::string H01 = "H01 = " + H01stream.str();


            std::stringstream H02stream;
            H02stream << std::fixed << std::setprecision(17) << obliczenia.H02_TAB[0];
            std::string H02 = "H02 = " + H02stream.str();





            file.AddLine(E01);
            file.AddLine(E02);
            file.AddLine(H01);
            file.AddLine(H02);


            file.Write();


            file.Close();

            wxLogMessage("zapisano");
        }
    }

    if (response != wxID_OK) {
        wxLogMessage("Zapisywanie przerwane");
    }
    delete OnSaveFileMaterial;
}


void MyFrame::OnBlackTheme(wxCommandEvent& event)
{
    wxColor black(0,0,0);
    wxColor white(255, 255, 255);
    wxColour grey(96, 96, 96);
 
    graf->SetColourTheme(*wxBLACK, *wxWHITE, grey);
    graf->UpdateAll();
}

void MyFrame::OnWhiteTheme(wxCommandEvent& event)
{
    wxColor black(0, 0, 0);
    wxColor white(255, 255, 255);
    wxColour grey(96, 96, 96);

    graf->SetColourTheme(*wxWHITE, *wxBLACK, grey);
    graf->UpdateAll();
}

void MyFrame::OnSaveScreenshot(wxCommandEvent& event)
{
    wxFileDialog fileDialog(this, _("Zrzut ekranu"), wxT(""), wxT(""), wxT("BMP image (*.bmp) | *.bmp|JPEG image (*.jpg) | *.jpeg;*.jpg|PNG image (*.png) | *.png"), wxFD_SAVE);
    if (fileDialog.ShowModal() == wxID_OK) {
        wxFileName namePath(fileDialog.GetPath());
        int fileType = wxBITMAP_TYPE_BMP;
        if (namePath.GetExt().CmpNoCase(wxT("jpeg")) == 0) fileType = wxBITMAP_TYPE_JPEG;
        if (namePath.GetExt().CmpNoCase(wxT("jpg")) == 0)  fileType = wxBITMAP_TYPE_JPEG;
        if (namePath.GetExt().CmpNoCase(wxT("png")) == 0)  fileType = wxBITMAP_TYPE_PNG;
        wxSize imgSize(500, 500);
        graf->SaveScreenshot(fileDialog.GetPath(), fileType, imgSize, false);
    }
    event.Skip();
}

void MyFrame::OnExit(wxCommandEvent& event)
{
    
    delete panel;
    delete Dlugosc_Fali;
    delete Podaj_N;
    delete Domieszkowanie1;
    delete Domieszkowanie2;
    delete graf;
//    delete xaxis;
//    delete yaxis;
//    delete l;
//    delete vectorLayer;
    delete licz;
//    delete menuPlik;
//    delete menuPomoc;
 //   delete menuGraf;
//    delete menuBar;
//    delete menuWynik;

//    delete topsizer;
//    delete horizontalsizer;
//    delete zmiennesizer;
//    delete zmiennesizer2;
    

//    delete nfo;
    

    
    
    Close(true);
  
    
}

void MyFrame1::OnExit(wxCommandEvent& event)
{
   
    delete mainPane;
 
//    delete menuPLikWynik;
 //   delete menuBarWynik;

   
    Close(true);
}

