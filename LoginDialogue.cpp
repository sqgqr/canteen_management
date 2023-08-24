#include "LoginDialogue.h"
#include "user.h"
LoginDialog::LoginDialog(wxWindow* parent, wxWindowID id, const wxString& title)
    : wxDialog(parent, id, title,wxDefaultPosition,wxSize(800,800)) {
    // Initialize and position controls
    rollNoField = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    passwordField = new wxTextCtrl(this, wxID_ANY, "", wxDefaultPosition, wxDefaultSize, wxTE_PASSWORD);
    loginButton = new wxButton(this, wxID_OK, "Login");

    // Add controls to a sizer
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(new wxStaticText(this, wxID_ANY, "Username:"), 0, wxALL, 5);
    sizer->Add(rollNoField, 0, wxEXPAND | wxALL, 5);
    sizer->Add(new wxStaticText(this, wxID_ANY, "Password:"), 0, wxALL, 5);
    sizer->Add(passwordField, 0, wxEXPAND | wxALL, 5);
    sizer->Add(loginButton, 0, wxALIGN_CENTER | wxALL, 5);

    loginButton->Bind(wxEVT_BUTTON, &LoginDialog::OnLogin, this);

    SetSizerAndFit(sizer);
}

void LoginDialog::OnLogin(wxCommandEvent& evt) {

    wxString rollNo = rollNoField->GetValue();
    wxString password = passwordField->GetValue();

    std::string RollNo = rollNo.ToStdString();
    std::string Password = password.ToStdString();

    std::cout << "Entered RollNo: " << RollNo << std::endl; 
    std::cout << "Entered Password: " << Password << std::endl;

    User user("", RollNo, Password);
    if (user.loadUserData()) {
        wxMessageDialog dialog(this, "User Login Dialog", "Login Successful", wxOK);
        dialog.ShowModal();
        dialog.Close();
        EndModal(wxID_OK);
    }
    else {
        wxMessageDialog dialog(this, "Login Failed! Incorrect Username or Password.", "Login Error", wxOK | wxICON_ERROR);
        dialog.ShowModal();
        dialog.Close();
    }
}