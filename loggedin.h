#pragma once

#include <wx/wx.h>
#include <wx/splitter.h>
#include <iostream>
#include <vector>
#include "User.h"
#include <string>
#include "menu.h"
#include "MenuPanel.h"

class loggedin : public wxFrame
{
public:
    loggedin(const wxString& title, User& u);
    void OnMenuItemButtonClick(wxCommandEvent& evt);

    wxPanel* leftPanel;
    wxButton* removeButton;
    wxSizer* rightBottomSizer;
    wxSizer* rightSizer;
    wxListBox* itemListBox;
    wxBoxSizer* leftSizer;
    wxStaticText* Balance;
    MenuPanel* menuPanel;
    wxPanel* rightBottomPanel;

    void OnLogout(wxCommandEvent& evt);
    static int ExtractPriceFromText(const wxString& buttonText);
private:
    User U;
    std::vector<std::string> billItems;
    int totalCost = 0;

    void OnBuy(wxCommandEvent& evt);
    void writeTransactions();
    void OnCheckTransaction(wxCommandEvent& evt);
    void OnRemoveButtonClick(wxCommandEvent& evt);
    
};
