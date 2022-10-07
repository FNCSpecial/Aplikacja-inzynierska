#include <wx/wxprec.h>
#include<iostream>
#include<string>
#include "mathplot.h"
#include "mathplot.cpp"
#include <wx/textfile.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

enum {
	ID_Zapisz = 1,
	ID_Wczytaj = 2,
	ID_Oblicz = 3,
};

class cApp : public wxApp
{
	virtual bool OnInit();
};

wxIMPLEMENT_APP(cApp);



class MyFrame : public wxFrame
{
public:


	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size,const long& style );
	wxPanel* panel = new wxPanel(this);
	
	wxTextCtrl* zmiennax = new wxTextCtrl(panel, wxID_ANY, "Zmienna_1", wxPoint(50, 50));
	wxTextCtrl* zmiennay = new wxTextCtrl(panel, wxID_ANY, "Zmienna_2", wxPoint(200, 50));
	wxTextCtrl* wynik = new wxTextCtrl(panel, wxID_ANY, "wynik", wxPoint(350, 50), wxSize(200, 70), wxTE_READONLY | wxTE_MULTILINE);

	
	//graf
	bool ticks;
	mpWindow* graf = new mpWindow(panel, wxID_ANY, wxPoint(55, 175), wxSize(960, 400), 0);
	mpScaleX* xaxis = new mpScaleX(wxT("X"), mpALIGN_BOTTOM, false, mpX_NORMAL);
	mpScaleY* yaxis = new mpScaleY(wxT("Y"), mpALIGN_LEFT, false);
	
	//Chwilowe zmienne
	wxString stringwynik[1000];
	double dx;
	double dy;


	//Deklaracja menu 
	wxButton* licz = new wxButton(panel, ID_Oblicz, "Oblicz", wxPoint(600, 50), wxSize(100, 30), wxBU_EXACTFIT);
	wxMenu* menuPlik = new wxMenu;
	wxMenu* menuPomoc = new wxMenu;
	wxMenuBar* menuBar = new wxMenuBar;

	//Funckje
private:
	void OnZapisz(wxCommandEvent& event);
	void OnWczytaj(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnOblicz(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();
};


wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(ID_Zapisz, MyFrame::OnZapisz)
EVT_MENU(ID_Wczytaj, MyFrame::OnWczytaj)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_BUTTON(ID_Oblicz, MyFrame::OnOblicz)
wxEND_EVENT_TABLE()



