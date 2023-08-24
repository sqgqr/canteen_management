#pragma once
#include <wx/wx.h>
#include <vector>
#include <string>

class TransactionHistory : public wxFrame {
public:
    TransactionHistory(wxWindow* parent, const wxString& title, const std::vector<std::string>& transactions);

private:
    void OnBackButtonClick(wxCommandEvent& event);
};

