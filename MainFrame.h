#pragma once
#include <wx/wx.h>
#include<wx/splitter.h>
#include<iostream>
#include<vector>
#include<string>
class MainFrame : public wxFrame
{
public:
	MainFrame(const wxString& title);
	
	
private:
	void OnUserLogin(wxCommandEvent& evt);
	void OnUserRegister(wxCommandEvent& evt);
	void OnAdminLogin(wxCommandEvent& evt);
};

