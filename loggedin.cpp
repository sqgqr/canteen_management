#include "loggedin.h"
#include "MainFrame.h"
#include "userlogin.h"
#include "SignupFrame.h"
#include "User.h"
#include "menu.h"
#include <wx/wx.h>
#include "MenuPanel.h"
#include <wx/regex.h>
#include <fstream>
#include "TransactionHistory.h"

loggedin::loggedin(const wxString& title, User& u) : wxFrame(nullptr, wxID_ANY, title),U(u) { 
    wxBoxSizer* mainSizer = new wxBoxSizer(wxHORIZONTAL);
    totalCost = 0;

    leftPanel = new wxPanel(this);
    leftPanel->SetBackgroundColour(wxColour(200, 200, 200)); // Light grey color for panels

    this->leftSizer = new wxBoxSizer(wxVERTICAL);
    wxString text = "Balance: " + wxString(to_string(U.getBalance()));
    this-> Balance = new wxStaticText(leftPanel, wxID_ANY, text);
    wxButton* logOutBtn = new wxButton(leftPanel, wxID_ANY, "Logout");
    wxButton* Buy = new wxButton(leftPanel, wxID_ANY, "Buy");
    wxButton* checkTransaction = new wxButton(leftPanel, wxID_ANY, "Check Transaction");

    leftSizer->Add(logOutBtn, 0, wxALL, 10);
    leftSizer->Add(checkTransaction, 0, wxALL, 10);
    leftSizer->Add(Buy, 0, wxALL, 10);
    leftSizer->Add(Balance, 0, wxALL, 10);

    leftPanel->SetSizer(leftSizer);

    wxScrolledWindow* scrolledWindow = new wxScrolledWindow(this, wxID_ANY);
    wxBoxSizer* scrolledSizer = new wxBoxSizer(wxVERTICAL);

    scrolledWindow->SetScrollRate(0, 20);
    scrolledWindow->SetSizer(scrolledSizer);

    menuPanel = new MenuPanel(scrolledWindow); // Add your MenuPanel to the scrolled window
    scrolledSizer->Add(menuPanel, 1, wxEXPAND);

    menuPanel->SetBackgroundColour(wxColour(200, 200, 200));
    wxWindowList children = menuPanel->GetChildren();
    for (wxWindow* child : children) {
        wxButton* button = wxDynamicCast(child, wxButton);
        if (button)
            button->Bind(wxEVT_BUTTON, &loggedin::OnMenuItemButtonClick, this);
    }
    rightSizer = new wxBoxSizer(wxVERTICAL);
    rightBottomPanel = new wxPanel(this);
    rightBottomPanel->SetBackgroundColour(wxColour(200, 200, 200));
    itemListBox = new wxListBox(rightBottomPanel, wxID_ANY, wxDefaultPosition, wxDefaultSize, {}, wxLB_MULTIPLE);

    this->rightBottomSizer = new wxBoxSizer(wxVERTICAL);

    //items list box
    rightBottomSizer->Add(itemListBox, 1, wxEXPAND | wxALL, 5);

    //remove Button
    removeButton = new wxButton(rightBottomPanel, wxID_ANY, "Remove Selected");
    rightBottomSizer->Add(removeButton, 0, wxALIGN_LEFT | wxALL, 5);
    removeButton->Bind(wxEVT_BUTTON, &loggedin::OnRemoveButtonClick, this);


    rightBottomPanel->SetSizer(rightBottomSizer);

    rightSizer->Add(scrolledWindow, 2, wxEXPAND | wxALL, 5);  // Expand the menu panel
    rightSizer->Add(rightBottomPanel, 1, wxEXPAND);  // Expand the right bottom panel

    mainSizer->Add(leftPanel, 1, wxEXPAND | wxLEFT | wxTOP | wxBOTTOM, FromDIP(10));
    mainSizer->Add(rightSizer, 2, wxEXPAND | wxALL, 10);

    this->SetSizer(mainSizer);
    mainSizer->Layout();

   checkTransaction->Bind(wxEVT_BUTTON, &loggedin::OnCheckTransaction,this);
    Buy->Bind(wxEVT_BUTTON, &loggedin::OnBuy, this);
    logOutBtn->Bind(wxEVT_BUTTON, &loggedin::OnLogout, this);
    CreateStatusBar();
}

void loggedin::OnLogout(wxCommandEvent& evt) {
    //confirmation dialog
    wxMessageDialog confirmDialog(this, "Do you want to log out?", "Logout Confirmation", wxYES_NO | wxICON_QUESTION);
    int result = confirmDialog.ShowModal();

    if (result == wxID_YES) {
        Close(); // Close the current loggedin frame
        MainFrame* mainframe = new MainFrame("Home Page");
        mainframe->SetClientSize(800, 600);
        mainframe->Center();
        mainframe->Show();
    }
}

void loggedin::OnRemoveButtonClick(wxCommandEvent& event) {
    // Get the selected indices from the wxListBox
    wxArrayInt selectedIndices;
    itemListBox->GetSelections(selectedIndices);
    if (selectedIndices.GetCount() == 0) {
        wxMessageDialog dialog(this, "No items selected to remove", "Purchase Error", wxOK | wxICON_ERROR);
        dialog.ShowModal();
        return;
    }
    // Remove selected items from the billItems list
    for (int i = selectedIndices.GetCount() - 1; i >= 0; --i) {
        int selectedIndex = selectedIndices[i];
        if (selectedIndex >= 0 && selectedIndex < billItems.size()) {

            //deducting total cost
            int itemPrice = ExtractPriceFromText(billItems[selectedIndex]);
            totalCost -= itemPrice;

            //erasing the selected index from billItems
            billItems.erase(billItems.begin() + selectedIndex);
        }
    }

    // Update the wxListBox to reflect the changes
    itemListBox->Clear();
    for (const std::string& updatedItem : billItems) {
        itemListBox->Append(wxString(updatedItem));
    }
}

void loggedin::OnMenuItemButtonClick(wxCommandEvent& event) {
    wxButton* button = wxDynamicCast(event.GetEventObject(), wxButton);
    if (button) {
        wxString buttonText = button->GetLabel();

        billItems.push_back(buttonText.ToStdString());

        int itemPrice = ExtractPriceFromText(buttonText);

        totalCost += itemPrice;  // Update total cost


        itemListBox->Append(buttonText);

    }
}

void loggedin::OnBuy(wxCommandEvent& evt) {
    int balance = 0;
    balance = U.getBalance();

    if (totalCost == 0) {
        wxMessageDialog dialog(this, "No items selected", "Purchase Error", wxOK | wxICON_ERROR);
        dialog.ShowModal();
        return;
    }

    //displaying comfirmation dialog if atleast an item is selected
    wxString confirmationMessage = "Total cost: " + wxString("Rs") + wxString::Format("%d", totalCost)
        + "\nDo you want to proceed with the purchase?";
    wxMessageDialog confirmationDialog(this, confirmationMessage, "Confirm Purchase", wxYES_NO | wxICON_QUESTION);
    int result = confirmationDialog.ShowModal();

    if (result == wxID_YES) {
        wxPasswordEntryDialog passwordDialog(this, "Enter your password to proceed with the purchase", "Password");

        if (passwordDialog.ShowModal() == wxID_OK) {
            wxString enteredPassword = passwordDialog.GetValue();
            
            //password matching
            if (enteredPassword == wxString(U.getPassword())) {
                if (balance < totalCost) {
                    wxMessageDialog balanceDialog(this, "Insufficient balance", "Balance Error", wxOK | wxICON_ERROR);
                    balanceDialog.ShowModal();
                }

                else {
                    int rem = balance - totalCost;
                    U.updateBalance(rem);
                    wxString cost = wxString::Format("%d", rem);
                    wxLogStatus(cost);

                    // Showing a dialog indicating successful purchase
                    wxString purchaseMessage = "Purchase successful!\nTotal cost: " + wxString::FromUTF8("Rs") +
                        wxString::Format("%d", totalCost) + "\nRemaining balance: " +
                        wxString::FromUTF8("Rs") + wxString::Format("%d", rem);
                    wxMessageDialog successDialog(this, purchaseMessage, "Purchase Successful", wxOK | wxICON_INFORMATION);
                    successDialog.ShowModal();

                    //printing bill
                    wxString billDetails="BILL";
                    for (const std::string& item : billItems) {
                        billDetails += wxString(item) + "\n\n";
                    }
                    billDetails += "TOTAL = Rs" + wxString::Format("%d",totalCost) + "\n";
                    wxMessageDialog billDialog(this, billDetails, "Bill Details", wxOK | wxICON_INFORMATION);
                    billDialog.ShowModal();
                    
                    //writing transaction to user file
                    this->writeTransactions();

                    // Clearing the bill and total cost
                    billItems.clear();
                    totalCost = 0;
                    itemListBox->Clear();

                    // returns remaining balance to update the user balance
                    wxString newBalanceText = "balance: " + wxString::FromUTF8(to_string(rem));
                    this->Balance->SetLabel(newBalanceText);

                    //updating layout to display changed balance
                    this->leftSizer->Layout();
                }
            }
        }

    }
}

int loggedin::ExtractPriceFromText(const wxString& buttonText) {

    wxRegEx regex("Rs(\\d+)"); // Regular expression to match "Rs" followed by digits
    if (regex.Matches(buttonText)) {
        wxString priceString = regex.GetMatch(buttonText, 1);
        long price;
        if (priceString.ToLong(&price)) {
            return static_cast<int>(price);
        }
    }
    
    return 0; // Return 0 or handle error as needed
}

void loggedin::writeTransactions() {

    std::ofstream transactionFile(("Transactions/"+(U.transactionFileName)).c_str(), ios::app);
    
    if (!transactionFile.is_open()) {
        cout << "Error opening transactions file for writing." << endl;
        return;
    }

    for (size_t i = 0; i < billItems.size(); i++) {
        transactionFile << "Item bought: ";
        transactionFile.width(50);
        transactionFile.setf(ios::right, ios::adjustfield);
        transactionFile << billItems[i] << endl;
    }

    transactionFile.close();
}

void loggedin::OnCheckTransaction(wxCommandEvent& evt)
{   
    std::vector<string> lines = U.readTransactionFile();
    TransactionHistory* historyFrame = new TransactionHistory(this, "Transaction History", lines);
    historyFrame->SetClientSize(800, 600);
    historyFrame->Center();
    historyFrame->Show();
}
