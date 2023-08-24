
#include "SignupFrame.h"
#include "MainFrame.h"
#include"user.h"
#include<wx/wx.h>
#include"userLogin.h"
SignupFrame::SignupFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	wxPanel* panel = new wxPanel(this);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);  // Vertical sizer

	wxStaticText* NameLabel = new wxStaticText(panel, wxID_ANY, "Name");
	nameTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));

	wxStaticText* rollNoLabel = new wxStaticText(panel, wxID_ANY, "Rollno");
	RollNoTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));

	wxStaticText* passwordLabel = new wxStaticText(panel, wxID_ANY, "Password");
	passwordTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1), wxTE_PASSWORD);

	wxButton* submitButton = new wxButton(panel, wxID_ANY, "Signup");
	wxButton* loginButton = new wxButton(panel, wxID_ANY, "Login");
	wxButton* backButton = new wxButton(panel, wxID_ANY, "<-");

	mainSizer->Add(backButton, 0, wxALL, 10);
	mainSizer->Add(NameLabel, 0, wxALL, 10);
	mainSizer->Add(nameTextCtrl, 0, wxALL, 10);
	mainSizer->Add(rollNoLabel, 0, wxALL, 10);
	mainSizer->Add(RollNoTextCtrl, 0, wxALL, 10);
	mainSizer->Add(passwordLabel, 0, wxALL, 10);
	mainSizer->Add(passwordTextCtrl, 0, wxALL, 10);
	mainSizer->Add(submitButton, 0, wxALL, 10);
	mainSizer->Add(loginButton, 0, wxALL, 10);

	panel->SetSizer(mainSizer);

	backButton->Bind(wxEVT_BUTTON, &SignupFrame::OnBackButtonClick, this);
	submitButton->Bind(wxEVT_BUTTON, &SignupFrame::OnSubmitButtonClicked, this);
	loginButton->Bind(wxEVT_BUTTON, &SignupFrame::OnLoginButtonClicked, this);

	CreateStatusBar();
}

void SignupFrame::OnSubmitButtonClicked(wxCommandEvent& evt) {
	wxLogStatus("Button clicked");
	wxString name = nameTextCtrl->GetValue();
	wxString rollNo = RollNoTextCtrl->GetValue();
	wxString password = passwordTextCtrl->GetValue();
	std::string Name = name.ToStdString();
	std::string RollNo = rollNo.ToStdString();
	std::string Password = password.ToStdString();

	User s1(Name,RollNo, Password);
	if(s1.registerUser())
	{
		wxMessageDialog(this,"Signedup successfully", "Signup Info", wxOK | wxICON_INFORMATION);

		Close();
		wxLogDebug("closed signup frame");
		userlogin* userloginframe = new userlogin("Login");
		userloginframe->SetClientSize(800, 600);
		userloginframe->Center();
		userloginframe->Show();
		wxLogStatus(name);
	}

	else
	{
		wxLogDebug("signup unsuccesful");
		wxMessageDialog(this, "Register Failed", "Register Error", wxOK | wxICON_ERROR);
	}

}
void SignupFrame::OnLoginButtonClicked(wxCommandEvent& evt) {
	Close();
	userlogin* userloginframe = new userlogin("Login");
	userloginframe->SetClientSize(800, 600);
	userloginframe->Center();
	userloginframe->Show();
}

void SignupFrame::OnBackButtonClick(wxCommandEvent& evt)
{
	Close();
	MainFrame* mainframe = new MainFrame("Home Page");
	mainframe->SetClientSize(800, 600);
	mainframe->Center();
	mainframe->Show();
}