#include "userlogin.h"
#include"loggedin.h"

userlogin::userlogin(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    wxPanel* panel = new wxPanel(this);

    // Create a vertical sizer to arrange controls vertically
    wxBoxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* rollNoTextLabel = new wxStaticText(panel, wxID_ANY, "Rollno");
    rollNoTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200,-1));
    wxStaticText* passwordLabel = new wxStaticText(panel, wxID_ANY, "Password");
    passwordTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200,-1), wxTE_PASSWORD);
    wxButton* submitButton = new wxButton(panel, wxID_ANY, "Login", wxDefaultPosition, wxSize(100, 35));
    wxButton* signupButton = new wxButton(panel, wxID_ANY, "Signup", wxDefaultPosition, wxSize(100, 35));
    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back");
    
    // Add controls to the vertical sizer
    verticalSizer->Add(backButton, 0, wxALL, 10);
    verticalSizer->Add(rollNoTextLabel, 0, wxALL, 5);
    verticalSizer->Add(rollNoTextCtrl, 0,  wxALL, 5);
    verticalSizer->Add(passwordLabel, 0, wxALL, 5);
    verticalSizer->Add(passwordTextCtrl, 0, wxALL, 5);
    verticalSizer->Add(submitButton, 0, wxALL, 5);
    verticalSizer->Add(signupButton, 0, wxALL, 5);
    
    panel->SetSizer(verticalSizer);

    // Bind events
    backButton->Bind(wxEVT_BUTTON, &userlogin::OnBackButtonClick, this);

    submitButton->Bind(wxEVT_BUTTON, &userlogin::OnLoginButtonClicked, this);
    signupButton->Bind(wxEVT_BUTTON, &userlogin::OnSignupButtonClicked, this);

    CreateStatusBar();
}

void userlogin::OnLoginButtonClicked(wxCommandEvent& evt) {
	wxLogStatus("Button clicked");
	wxString rollNo = rollNoTextCtrl->GetValue();
	wxString password = passwordTextCtrl->GetValue();
	std::string RollNo = rollNo.ToStdString();
	std::string Password = password.ToStdString();


	User u1("",RollNo,Password);
	if (u1.loadUserData())
	{
		wxMessageBox("login successful", "Login", wxOK | wxICON_INFORMATION);
		Close();
		loggedin* Loggedin = new loggedin(wxString(u1.getName()),u1);
		Loggedin->SetClientSize(800, 600);
		Loggedin->Center();
		Loggedin->Show();
	}
	else {
		wxMessageBox("wrong username or password", "Login Info", wxOK | wxICON_INFORMATION);
	}
}
void userlogin::OnSignupButtonClicked(wxCommandEvent& evt) {
	Close();
	SignupFrame* signupFrame = new SignupFrame("signup");
	signupFrame->SetClientSize(800, 600);
	signupFrame->Center();
	signupFrame->Show();
}

void userlogin::OnBackButtonClick(wxCommandEvent& evt)
{
    Close();
    MainFrame* mainframe = new MainFrame("Home Page");
    mainframe->SetClientSize(800, 600);
    mainframe->Center();
    mainframe->Show();
}
