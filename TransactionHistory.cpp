#include "TransactionHistory.h"
TransactionHistory::TransactionHistory(wxWindow* parent, const wxString& title, const std::vector<std::string>& transactions)
    : wxFrame(parent, wxID_ANY, title) {
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    wxTextCtrl* txnTextControl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition,
        wxDefaultSize, wxTE_MULTILINE | wxTE_READONLY);

    for (const std::string& line : transactions) {
        txnTextControl->AppendText(wxString::FromUTF8(line) + "\n");
    }

    wxButton* backButton = new wxButton(this, wxID_ANY, "<-");
    backButton->Bind(wxEVT_BUTTON, &TransactionHistory::OnBackButtonClick, this);
    mainSizer->Add(backButton, 0, wxALIGN_CENTER | wxALL, 10);
    mainSizer->Add(txnTextControl, 1, wxEXPAND | wxALL, 10);

    SetSizerAndFit(mainSizer);
    Center();
}

void TransactionHistory::OnBackButtonClick(wxCommandEvent& event) {
    Close();
}