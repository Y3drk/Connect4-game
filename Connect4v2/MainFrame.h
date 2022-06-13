#pragma once
#include <wx/wx.h>
#include <wx/grid.h>
#include <wx/spinctrl.h>
#include "Gameboard.h"

class MainFrame: public wxFrame
{
	public:
		MainFrame(const wxString& title);
		void secondPanel();

	private:
		wxPanel* startingPanel;
		wxPanel* playingPanel;
		wxTextCtrl* player1NameInput;
		wxTextCtrl* player2NameInput;
		wxBoxSizer* panel_sizer;
		wxStaticText* whoseTurn;
		wxStaticText* currentGamestate;
		wxGrid* grid;
		wxSpinCtrl* moveChoice;
		Gameboard* gameboard;
		wxButton* moveBtn;

		void onPlayBtnClicked(wxCommandEvent& evt);
		void onRestartBtnClicked(wxCommandEvent& evt);
		void onMoveBtnClicked(wxCommandEvent& evt);
		void initializeGame();
};

