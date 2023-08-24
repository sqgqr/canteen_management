#pragma once
#include"user.h"
#include"SignupFrame.h"
#include"MainFrame.h"
#include<wx/wx.h>
class userlogin:public wxFrame
{
private:
	wxTextCtrl* rollNoTextCtrl;
	wxTextCtrl* passwordTextCtrl;
	void OnLoginButtonClicked(wxCommandEvent& evt);
	void OnSignupButtonClicked(wxCommandEvent& evt);
	void OnBackButtonClick(wxCommandEvent& evt);

public:
	userlogin(const wxString& title);

};
