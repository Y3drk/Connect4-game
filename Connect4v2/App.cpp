#include <wx/wx.h>
#include "App.h"
#include "MainFrame.h"

wxIMPLEMENT_APP(App);

bool App::OnInit()
{
	MainFrame* mainFrame = new MainFrame("Connect4!");
	mainFrame->SetClientSize(600, 300);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}
