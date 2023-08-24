#pragma once
#include"admin.h"
#include"MainFrame.h"
#include<wx/wx.h>

class adminlogin : public wxFrame
{
private:
	wxTextCtrl* adminIdTextCtrl;
	wxTextCtrl* passwordTextCtrl;
	void OnLoginButtonClicked(wxCommandEvent& evt);
	void OnBackButtonClick(wxCommandEvent& evt);

public:
	adminlogin(const wxString& title);
};

