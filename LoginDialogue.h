#pragma once
#include <wx/wx.h>
 class LoginDialog : public wxDialog {
    public:
        LoginDialog(wxWindow* parent, wxWindowID id, const wxString& title);

    private:
        wxTextCtrl* rollNoField;
        wxTextCtrl* passwordField;
        wxButton* loginButton;

        void OnLogin(wxCommandEvent& event);
    };

