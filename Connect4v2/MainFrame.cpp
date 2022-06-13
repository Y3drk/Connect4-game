#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/spinctrl.h>
#include "Player.h"
#include "Gameboard.h" 
#include <wx/grid.h>
#include <string>


MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	this->startingPanel = new wxPanel(this, wxID_ANY, wxPoint(0,0));

	wxButton* playBtn = new wxButton(startingPanel, wxID_ANY, "PLAY", wxPoint(250, 245), wxSize(100, 45));

	wxStaticText* beginningText = new wxStaticText(startingPanel, wxID_ANY, "Let's play Conntect 4 together! Write the names of the players and begin the game!", wxPoint(100, 50));

	wxStaticText* playersNameLabel = new wxStaticText(startingPanel, wxID_ANY, "Players names: ", wxPoint(50, 175));

	this->player1NameInput = new wxTextCtrl(startingPanel, wxID_ANY, "Player1", wxPoint(150, 150), wxSize(150, -1));

	this->player2NameInput = new wxTextCtrl(startingPanel, wxID_ANY, "Player2", wxPoint(150, 200), wxSize(150, -1));

	playBtn->Bind(wxEVT_BUTTON, &MainFrame::onPlayBtnClicked, this);

	wxStaticText* colorRed = new wxStaticText(this->startingPanel, wxID_ANY, "color: RED", wxPoint(320, 155));

	wxStaticText* colorBlue = new wxStaticText(this->startingPanel, wxID_ANY, "color: BLUE", wxPoint(320, 205));


	//playing panel
	this->playingPanel = new wxPanel(this, wxID_ANY, wxPoint(0, 0));


	moveChoice = new wxSpinCtrl(this->playingPanel, wxID_ANY, "0", wxPoint(100, 80), wxSize(80, -1), 16384L, 0, 6);

	moveBtn = new wxButton(playingPanel, wxID_ANY, "MOVE", wxPoint(180, 80), wxSize(100, 20));

	moveBtn->Bind(wxEVT_BUTTON, &MainFrame::onMoveBtnClicked, this);

	wxButton* restartBtn = new wxButton(playingPanel, wxID_ANY, "RESTART", wxPoint(200, 450), wxSize(100, 20));

	restartBtn->Bind(wxEVT_BUTTON, &MainFrame::onRestartBtnClicked, this);

	wxStaticText* xd = new wxStaticText(this->playingPanel, wxID_ANY, "playing ->", wxPoint(100, 20));


	this->whoseTurn = new wxStaticText(this->playingPanel, wxID_ANY, "test", wxPoint(155, 20));

	wxStaticText* gamestate = new wxStaticText(this->playingPanel, wxID_ANY, "gamestate ->", wxPoint(100, 40));

	this->currentGamestate = new wxStaticText(this->playingPanel, wxID_ANY, "test", wxPoint(170, 40));

	grid = new wxGrid(this->playingPanel, wxID_ANY, wxPoint(100, 120), wxSize(400, 300));
	
	grid->CreateGrid(6, 7);

	for (int i = 0; i < 6; i++) {
		grid->SetRowSize(i, 40);
		grid->DisableRowResize(i);
		std::string number = std::to_string(6 - i - 1);
		wxString mystring = wxString::FromUTF8(number);
		grid->SetRowLabelValue(i, mystring);
	}

	for (int i = 0; i < 7; i++) {
		grid->SetColSize(i, 40);
		std::string number = std::to_string(i);
		wxString mystring = wxString::FromUTF8(number);
		grid->SetColLabelValue(i, mystring);
		grid->DisableColResize(i);
	}

	grid->DisableDragGridSize();
	grid->DisableCellEditControl();


	//panel sizer
	panel_sizer = new wxBoxSizer(wxVERTICAL);

	panel_sizer->Add(this->startingPanel, 1, wxEXPAND | wxALL | wxTOP | wxCENTER, 0);
	panel_sizer->Add(this->playingPanel, 1, wxEXPAND | wxALL | wxTOP | wxCENTER, 0);

	this->SetSizerAndFit(panel_sizer);

	startingPanel->Show();
	playingPanel ->Hide();

}

void MainFrame::secondPanel()
{	
	this->startingPanel->Hide();


	this->playingPanel->Show();
}

void MainFrame::onPlayBtnClicked(wxCommandEvent& evt)
{	
	secondPanel();
	initializeGame();

}

void MainFrame::onRestartBtnClicked(wxCommandEvent& evt)
{
	this->playingPanel->Hide();
	this->startingPanel->Show();
	this->grid->ClearGrid();
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 7; j++) {
			this->grid->SetCellBackgroundColour(i, j, *wxWHITE);
		}
	}

	this->gameboard->resetBoard();
	moveBtn->Bind(wxEVT_BUTTON, &MainFrame::onMoveBtnClicked, this);
}

void MainFrame::onMoveBtnClicked(wxCommandEvent& evt) {

	int whichColumn = this->moveChoice->GetValue();
	int flag = 1;
	wxStaticText* errorText = new wxStaticText(this->playingPanel, wxID_ANY, "...", wxPoint(100, 60));

	try {
		Vector2D whereNewTile = this->gameboard->placeTile(whichColumn);
		Player p = this->gameboard->getPlayerFromIndex(this->gameboard->getMove());
		if (p.getColor() == RED) grid->SetCellBackgroundColour(5 - whereNewTile.getY(), whichColumn, *wxRED);
		else grid->SetCellBackgroundColour(5 - whereNewTile.getY(), whichColumn, *wxBLUE);
		grid->Refresh();
	}
	catch (std::invalid_argument error) {
		errorText->SetLabel("Try another move!!!   ");
		flag = 0;
	}



	if (flag == 1) {
		std::string result;
		switch (this->gameboard->checkGameState()) {
		case 0:
			this->currentGamestate->SetLabel("ongoing...");
			break;
		case 1:
			result = this->gameboard->getPlayerFromIndex(0).getName() + " won!";
			this->currentGamestate->SetLabel(result);
			moveBtn->Unbind(wxEVT_BUTTON, &MainFrame::onMoveBtnClicked, this);
			break;
		case 2:
			result = this->gameboard->getPlayerFromIndex(1).getName() + " won!";
			this->currentGamestate->SetLabel(result);
			moveBtn->Unbind(wxEVT_BUTTON, &MainFrame::onMoveBtnClicked, this);
			break;
		default:
			this->currentGamestate->SetLabel("draw.");
			moveBtn->Unbind(wxEVT_BUTTON, &MainFrame::onMoveBtnClicked, this);
			break;
		}

		errorText->SetLabel("The move was legit :)");
		errorText->Refresh();
		this->gameboard->newTurn();

		this->whoseTurn->SetLabel(this->gameboard->getPlayerFromIndex(this->gameboard->getMove()).getName());

		this->whoseTurn->Refresh();
		this->currentGamestate->Refresh();
	}
}


void MainFrame::initializeGame()
{
	wxString player1Name = this->player1NameInput->GetValue();
	wxString player2Name = this->player2NameInput->GetValue();

	Player p1 = Player((std::string)player1Name, RED);
	Player p2 = Player((std::string)player2Name, BLUE);

	this->gameboard = new Gameboard(p1, p2);
	this->gameboard->decideStarter();

	this->currentGamestate->SetLabel("ongoing...");
	this->whoseTurn->SetLabel(this->gameboard->getPlayerFromIndex(this->gameboard->getMove()).getName());
}

