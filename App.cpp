#include "App.h"
#include"MainFrame.h"
#include<wx/wx.h>
wxIMPLEMENT_APP(App);//lets wx widgets know which class represents the APP we made/where to begin the program with
bool App::OnInit() {
	MainFrame* mainFrame = new MainFrame("c++ Gui");
	mainFrame->SetClientSize(800, 600);
	mainFrame->Center();
	mainFrame->Show();
	return true;
}