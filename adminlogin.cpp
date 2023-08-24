#include "adminlogin.h"
#include "userlogin.h"
#include"loggedin.h"
#include"adminframe.h"
#include "User.h"


adminlogin::adminlogin(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    wxPanel* panel = new wxPanel(this);

    // Create a vertical sizer to arrange controls vertically
    wxBoxSizer* verticalSizer = new wxBoxSizer(wxVERTICAL);

    wxStaticText* adminIdTextLabel = new wxStaticText(panel, wxID_ANY, "Admin ID");
    adminIdTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1));
    wxStaticText* passwordLabel = new wxStaticText(panel, wxID_ANY, "Password");
    passwordTextCtrl = new wxTextCtrl(panel, wxID_ANY, "", wxDefaultPosition, wxSize(200, -1), wxTE_PASSWORD);
    wxButton* submitButton = new wxButton(panel, wxID_ANY, "Login", wxDefaultPosition, wxSize(100, 35));
    wxButton* backButton = new wxButton(panel, wxID_ANY, "Back");

    
    // Add controls to the vertical sizer
    verticalSizer->Add(backButton, 0, wxALL, 10);
    verticalSizer->Add(adminIdTextLabel, 0, wxALL, 5);
    verticalSizer->Add(adminIdTextCtrl, 0, wxALL, 5);
    verticalSizer->Add(passwordLabel, 0, wxALL, 5);
    verticalSizer->Add(passwordTextCtrl, 0, wxALL, 5);
    verticalSizer->Add(submitButton, 0, wxALL, 5);

    panel->SetSizer(verticalSizer);

    // Bind events
    backButton->Bind(wxEVT_BUTTON, &adminlogin::OnBackButtonClick, this);
    submitButton->Bind(wxEVT_BUTTON, &adminlogin::OnLoginButtonClicked, this);

    CreateStatusBar();
}

void adminlogin::OnLoginButtonClicked(wxCommandEvent& evt) {
    wxLogStatus("Button clicked");
    wxString adminId = adminIdTextCtrl->GetValue();
    wxString password = passwordTextCtrl->GetValue();
    std::string AdminId = adminId.ToStdString();
    std::string Password = password.ToStdString();


    Admin a1(AdminId,"", Password);
    if (a1.login())
    {
        Close();
        AdminFrame* adminframe = new AdminFrame(wxString("admin"));
        adminframe->SetClientSize(800, 600);
        adminframe->Center();
        adminframe->Show();
    }
    else {
        wxMessageBox("wrong adminId or password", "Login Info", wxOK | wxICON_INFORMATION);
    }
}

void adminlogin::OnBackButtonClick(wxCommandEvent& evt)
{
    Close();
    MainFrame* mainFrame = new MainFrame("c++ Gui");
    mainFrame->SetClientSize(800, 600);
    mainFrame->Center();
    mainFrame->Show();
}
