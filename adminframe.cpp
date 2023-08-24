#include "adminframe.h"
#include<fstream>
AdminFrame::AdminFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
    
    wxPanel* leftPanel = new wxPanel(this);
    wxButton* logOutBtn = new wxButton(leftPanel, wxID_ANY, "Logout");
    wxButton* AddMoneyBtn = new wxButton(leftPanel, wxID_ANY, "Add Money");
    wxButton* addItemBtn = new wxButton(leftPanel, wxID_ANY, "Add Item");

    logOutBtn->Bind(wxEVT_BUTTON, &AdminFrame::OnLogout, this);
    AddMoneyBtn->Bind(wxEVT_BUTTON, &AdminFrame::OnAddMoney, this);
    addItemBtn->Bind(wxEVT_BUTTON, &AdminFrame::OnAddItem, this);

    wxBoxSizer* leftSizer = new wxBoxSizer(wxVERTICAL);

    leftSizer->Add(logOutBtn, 0, wxALL, 10);
    leftSizer->Add(AddMoneyBtn, 0, wxALL, 10);
    leftSizer->Add(addItemBtn, 0, wxALL, 10);
    leftPanel->SetSizer(leftSizer);
    
    scrolledWindow = new wxScrolledWindow(this, wxID_ANY);
    scrolledWindow->SetScrollRate(0, 20); // Set vertical scrolling step

    // Create a sizer for the scrolled window
    wxBoxSizer* scrolledSizer = new wxBoxSizer(wxVERTICAL);
    scrolledWindow->SetSizer(scrolledSizer);

    menuPanel = new MenuPanel(scrolledWindow); // Add your MenuPanel to the scrolled window
    scrolledSizer->Add(menuPanel, 1, wxEXPAND);

    menuPanel->SetBackgroundColour(wxColour(200, 200, 200));
    wxWindowList children = menuPanel->GetChildren();
    for (wxWindow* child : children) {
        wxButton* button = wxDynamicCast(child, wxButton);
        if (button)
            button->Bind(wxEVT_BUTTON, &AdminFrame::OnMenuItemButtonClick, this);
    }

    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);

    mainSizer->Add(leftPanel, 1, wxEXPAND | wxLEFT | wxTOP | wxBOTTOM, FromDIP(10));
    mainSizer->Add(scrolledWindow, 2, wxEXPAND | wxALL, 10);

    this->SetSizer(mainSizer);
    mainSizer->Layout();
}

void AdminFrame::OnAddItem(wxCommandEvent& event)
{
    wxString itemName = wxGetTextFromUser("Enter item name:", "Add Item", "");
    if (itemName.IsEmpty())
        return;

    wxString itemPriceStr = wxGetTextFromUser("Enter item price:", "Add Item", "");
    if (itemPriceStr.IsEmpty())
        return;

    int itemPrice;
    if (!itemPriceStr.ToInt(&itemPrice)) {
        wxMessageBox("Invalid item price.", "Error", wxOK | wxICON_ERROR);
        return;
    }

    Menu M;
    M.addItem(string(itemName),itemPrice);

    Close();
    AdminFrame* adminframe = new AdminFrame(wxString("admin"));
    adminframe->SetClientSize(800, 600);
    adminframe->Center();
    adminframe->Show();
}

void AdminFrame::OnAddMoney(wxCommandEvent& event)
{
    wxString rollNo = wxGetTextFromUser("Enter roll no :", "Add Money", "");
    if (rollNo.IsEmpty())
        return;

    User U("", rollNo.ToStdString(), "");
    U.loadUserForAdmin();

    wxString amount = wxGetTextFromUser("Enter amount to add", "Add Money", "");
    if (amount.IsEmpty())
        return;
    int Amount;
    amount.ToInt(&Amount);
    //wxLogStatus(wxString(to_string(Amount)));
    int newAmount =Amount+ U.getBalance();
    U.updateBalance(newAmount);

   ofstream transactionFile("Transactions/"+U.transactionFileName, ios::app);
    if (!transactionFile.is_open())
    {
        wxLogError("transaction file couldn't be opened");
        return;
    }

    transactionFile << Amount << " Rs added to the account." << endl;
    transactionFile.close();
}

void AdminFrame::OnLogout(wxCommandEvent& event)
{
    wxMessageDialog confirmDialog(this, "Do you want to log out?", "Logout Confirmation", wxYES_NO | wxICON_QUESTION);
    int result = confirmDialog.ShowModal();

    if (result == wxID_YES) {
        Close(); // Close the current loggedin frame
        MainFrame* mainFrame = new MainFrame("c++ Gui");
        mainFrame->SetClientSize(800, 600);
        mainFrame->Center();
        mainFrame->Show();
    }
}

void AdminFrame::OnMenuItemButtonClick(wxCommandEvent& event) {
    wxButton* button = wxDynamicCast(event.GetEventObject(), wxButton);
    if (button) {
        wxString buttonText = button->GetLabel();

        wxMessageDialog dialog(this, "Select an action for the item:", "Menu Item Action", wxYES_NO | wxCANCEL | wxCANCEL_DEFAULT);
        dialog.SetYesNoLabels("Update Price", "Delete Item");

        int result = dialog.ShowModal();

        Menu M;

        if (result == wxID_YES) {
            wxString newPrice = wxGetTextFromUser("Enter New Price", "Menu Update", "");
            if (newPrice.IsEmpty())
                return;
            int NewPrice;
            std::string ButtonText;
            ButtonText=buttonText.ToStdString();
            ButtonText = ButtonText.substr(0, ButtonText.find(' '));
            newPrice.ToInt(&NewPrice);

            M.updatePrice(ButtonText,NewPrice);

        }
        else if (result == wxID_NO) {
            std::string item;
            item = buttonText.ToStdString();
            item = item.substr(0, item.find(' '));
            int itemPrice=loggedin::ExtractPriceFromText(buttonText);
            M.deleteItem(item,itemPrice);
        }

        this->Close();
        AdminFrame* adminframe = new AdminFrame(wxString("admin"));
        adminframe->SetClientSize(800, 600);
        adminframe->Center();
        adminframe->Show();
    }
}
