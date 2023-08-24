#include "MainFrame.h"
#include "userlogin.h"
#include "SignupFrame.h"
#include "MenuPanel.h"
#include <wx/wx.h>
#include "adminlogin.h"

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {

    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    wxPanel* leftPanel = new wxPanel(this);
    wxScrolledWindow* scrolledWindow = new wxScrolledWindow(this, wxID_ANY);
    scrolledWindow->SetScrollRate(0, 20);

    leftPanel->SetBackgroundColour(wxColour(200,200, 200));
    scrolledWindow->SetBackgroundColour(wxColour(200, 200,200));

    wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);
    wxButton* adminLoginBtn = new wxButton(leftPanel, wxID_ANY, "Admin Login");
    wxButton* userLoginBtn = new wxButton(leftPanel, wxID_ANY, "User Login");
    wxButton* userRegisterBtn = new wxButton(leftPanel, wxID_ANY, "User Register");

    adminLoginBtn->Bind(wxEVT_BUTTON, &MainFrame::OnAdminLogin, this);
    userLoginBtn->Bind(wxEVT_BUTTON, &MainFrame::OnUserLogin, this);
    userRegisterBtn->Bind(wxEVT_BUTTON, &MainFrame::OnUserRegister, this);

    leftSizer->Add(adminLoginBtn, 0, wxALL, 10);
    leftSizer->Add(userLoginBtn, 0, wxALL, 10);
    leftSizer->Add(userRegisterBtn, 0, wxALL, 10);
    leftPanel->SetSizer(leftSizer);


    mainSizer->Add(leftPanel, 0, wxEXPAND | wxALL, 10);
    mainSizer->Add(scrolledWindow, 1, wxEXPAND | wxTOP | wxLEFT | wxLEFT, 10);

    wxBoxSizer* scrolledSizer=new wxBoxSizer(wxVERTICAL);
 
    MenuPanel *menuPanel=new MenuPanel(scrolledWindow);

    scrolledSizer->Add(menuPanel,1,wxEXPAND);
    scrolledWindow->SetSizer(scrolledSizer);

    this->SetSizer(mainSizer);
    mainSizer->Layout();

    CreateStatusBar();
}

 void MainFrame::OnUserLogin(wxCommandEvent & evt) {
     Close();
     userlogin* userloginframe = new userlogin("login page");
     userloginframe->SetClientSize(500, 500);
     userloginframe->Center();
     userloginframe->Show();
    }

void MainFrame::OnAdminLogin(wxCommandEvent& evt) {
    Close();
    adminlogin* adminFrame = new adminlogin("Admin Login");
    adminFrame->SetClientSize(500, 500);
    adminFrame->Center();
    adminFrame->Show();
}

void MainFrame::OnUserRegister(wxCommandEvent& evt) 
{   
    Close();
    wxLogStatus("User Register Button Clicked");
    SignupFrame* signupframe= new SignupFrame("register");
    signupframe->SetClientSize(500, 500);
    signupframe->Center();
    signupframe->Show();
}