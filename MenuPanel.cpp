#include "MenuPanel.h"

MenuPanel::MenuPanel(wxWindow* parent) : wxPanel(parent)
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL); // Main vertical sizer

    wxStaticText* TOP = new wxStaticText(this, wxID_ANY, "TODAY'S MENU", wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER);
    wxFont topFont(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD); // Customize the font for the title
    TOP->SetFont(topFont);
    TOP->SetForegroundColour(wxColour(0, 0, 0));
    mainSizer->Add(TOP, 0, wxALIGN_CENTER_HORIZONTAL | wxALL, 10); // Add the title text to the main sizer

    wxGridSizer* buttonSizer = new wxGridSizer(2, 5, 5); // 2 columns, 2 rows, 5 pixel gaps

    Menu M;

    vector<string> items = M.getItems();
    vector<int> prices = M.getPrice();

    wxFont buttonFont(18, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    for (size_t i = 0; i < items.size(); ++i)
    {
        wxString buttonText = wxString::FromUTF8(items[i] + " - Rs" + to_string(prices[i]));
        wxButton* itemButton = new wxButton(this, wxID_ANY, buttonText, wxDefaultPosition, wxSize(-1, 75));

        itemButton->SetFont(buttonFont);
        itemButton->SetForegroundColour(wxColour(0, 0, 0));
        itemButton->SetBackgroundColour(wxColour(150, 150, 150));

        // events to change text color on hovering
        itemButton->Bind(wxEVT_ENTER_WINDOW, &MenuPanel::OnButtonHoverEnter, this, wxID_ANY);
        itemButton->Bind(wxEVT_LEAVE_WINDOW, &MenuPanel::OnButtonHoverLeave, this, wxID_ANY);

        buttonSizer->Add(itemButton, 1, wxALL, 15); // Add the button to the button sizer
    }

    mainSizer->Add(buttonSizer, 1, wxEXPAND); // Add the button sizer to the main sizer
    SetSizerAndFit(mainSizer); // Set the main sizer for the panel and fit the content
}

void MenuPanel::OnButtonHoverEnter(wxMouseEvent& event)
{
    wxButton* button = wxDynamicCast(event.GetEventObject(), wxButton);
    if (button)
    {
        button->SetForegroundColour(wxColour(0, 0, 0));
        button->SetBackgroundColour(wxColour(255, 255, 255));
    }
}

void MenuPanel::OnButtonHoverLeave(wxMouseEvent& event)
{
    wxButton* button = wxDynamicCast(event.GetEventObject(), wxButton);
    if (button)
    {
        button->SetForegroundColour(wxColour(0, 0, 0));
        button->SetBackgroundColour(wxColour(150, 150, 150));
    }
}
