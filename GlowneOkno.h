#include <wx/wxprec.h>
#include<iostream>
#include<string>
#include "mathplot.h"
#include "mathplot.cpp"
#include <wx/textfile.h>
#include <wx/grid.h>
#include <wx/wx.h>
#include <wx/log.h>
#include <Windows.h>
#include <cstdio>
#include <wx/choice.h>
#include <wx/arrstr.h>
#include <wx/filename.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

enum {
	ID_Zapisz = 1,
	ID_BLACK_THEME = 2,
	ID_Oblicz = 3,
	ID_SAVE_SCREENSHOT = 55,
	ID_White_theme = 56,

	ID_Graf1 = 4,
	ID_Graf2 = 5,
	ID_Graf3 = 6,
	ID_Graf4 = 7,
	ID_Graf5 = 8,
	ID_Graf6 = 9,
	ID_Graf7 = 10,

	ID_Wynik1 = 11,
	ID_Wynik2 = 12,
	ID_Wynik3 = 13,
	ID_Wynik4 = 14,
	ID_Wynik5 = 15,
	ID_Wynik6 = 16,
	ID_Wynik7 = 17,

	ID_Domieszkowanie1 = 50,
	ID_Domieszkowanie2 = 51
};

class MyFrame : public wxFrame
{
public:


	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size, const long& style);
	wxPanel* panel = new wxPanel(this);

	//zmienne 
	wxTextCtrl* Dlugosc_Fali = new wxTextCtrl(this, wxID_ANY, "D³ugoœæ_Fali");
	wxArrayString domieszkowanie_lista;
	wxChoice* Domieszkowanie1;
	wxChoice* Domieszkowanie2;




	//graf
	bool ticks;
	mpWindow* graf = new mpWindow(this, wxID_ANY, wxPoint(0, 0), wxSize(960, 400), wxSUNKEN_BORDER);
	mpScaleX* xaxis = new mpScaleX(wxT("X"), mpALIGN_BOTTOM, false, mpX_NORMAL);
	mpScaleY* yaxis = new mpScaleY(wxT("Y"), mpALIGN_LEFT, false);
	std::vector<double> vectorx, vectory;
	mpLayer* l;
	mpFXYVector* vectorLayer = new mpFXYVector;
	double xcoord;
	double ycoord;
	int axesPos[2];



	double lambda;
	int dom1;
	int dom2;


	//Chwilowe zmienne
	wxString stringwynik[1000];
	double dx;
	double dy;


	//Deklaracja menu 
	wxButton* licz = new wxButton(this, ID_Oblicz, "Oblicz");
	wxMenu* menuPlik = new wxMenu;
	wxMenu* menuPomoc = new wxMenu;
	wxMenu* menuGraf = new wxMenu;
	wxMenu* menuWynik = new wxMenu;
	wxMenuBar* menuBar = new wxMenuBar;

	//Funckje
private:
	void OnZapisz(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnOblicz(wxCommandEvent& event);
	void OnSaveScreenshot(wxCommandEvent& event);
	void OnBlackTheme(wxCommandEvent& event);
	void OnWhiteTheme(wxCommandEvent& event);

	void OnGraf1(wxCommandEvent& event);
	void OnGraf2(wxCommandEvent& event);
	void OnGraf3(wxCommandEvent& event);
	void OnGraf4(wxCommandEvent& event);
	void OnGraf5(wxCommandEvent& event);
	void OnGraf6(wxCommandEvent& event);
	void OnGraf7(wxCommandEvent& event);


	void OnWynik1(wxCommandEvent& event);
	void OnWynik2(wxCommandEvent& event);
	void OnWynik3(wxCommandEvent& event);
	void OnWynik4(wxCommandEvent& event);
	void OnWynik5(wxCommandEvent& event);
	void OnWynik6(wxCommandEvent& event);
	void OnWynik7(wxCommandEvent& event);

	wxDECLARE_EVENT_TABLE();
};


wxBEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_MENU(ID_Zapisz, MyFrame::OnZapisz)
EVT_MENU(wxID_EXIT, MyFrame::OnExit)
EVT_MENU(wxID_ABOUT, MyFrame::OnAbout)
EVT_BUTTON(ID_Oblicz, MyFrame::OnOblicz)
EVT_MENU(ID_BLACK_THEME, MyFrame::OnBlackTheme)
EVT_MENU(ID_White_theme, MyFrame::OnWhiteTheme)
EVT_MENU(ID_SAVE_SCREENSHOT, MyFrame::OnSaveScreenshot)

EVT_MENU(ID_Graf1, MyFrame::OnGraf1)
EVT_MENU(ID_Graf2, MyFrame::OnGraf2)
EVT_MENU(ID_Graf3, MyFrame::OnGraf3)
EVT_MENU(ID_Graf4, MyFrame::OnGraf4)
EVT_MENU(ID_Graf5, MyFrame::OnGraf5)
EVT_MENU(ID_Graf6, MyFrame::OnGraf6)
EVT_MENU(ID_Graf7, MyFrame::OnGraf7)

EVT_MENU(ID_Wynik1, MyFrame::OnWynik1)
EVT_MENU(ID_Wynik2, MyFrame::OnWynik2)
EVT_MENU(ID_Wynik3, MyFrame::OnWynik3)
EVT_MENU(ID_Wynik4, MyFrame::OnWynik4)
EVT_MENU(ID_Wynik5, MyFrame::OnWynik5)
EVT_MENU(ID_Wynik6, MyFrame::OnWynik6)
EVT_MENU(ID_Wynik7, MyFrame::OnWynik7)

wxEND_EVENT_TABLE()