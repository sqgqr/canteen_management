#pragma once
#include<wx/wx.h>
class SignupFrame :public wxFrame
{
private:
	wxTextCtrl* nameTextCtrl;
	wxTextCtrl* RollNoTextCtrl;
	wxTextCtrl* passwordTextCtrl;
	void OnSubmitButtonClicked(wxCommandEvent& evt);
	void OnLoginButtonClicked(wxCommandEvent& evt);
	void OnBackButtonClick(wxCommandEvent& evt);
public:
	SignupFrame(const wxString& title);
};
