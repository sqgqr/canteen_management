#pragma once
#include "loggedin.h"
#include "MenuPanel.h"
#include<wx/wx.h>
#include<vector>
#include<string>
#include"MainFrame.h"

class AdminFrame : public wxFrame
{
public:
    AdminFrame(const wxString& title);
    std::vector<string> billItems;
    MenuPanel* menuPanel;
    wxSizer* rightSizer;
    wxScrolledWindow* scrolledWindow;
private:
    void OnAddItem(wxCommandEvent& event);
    void OnAddMoney(wxCommandEvent& event);
    void OnLogout(wxCommandEvent& event);
    void OnMenuItemButtonClick(wxCommandEvent& event);
};

