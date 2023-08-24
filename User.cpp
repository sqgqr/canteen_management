#include "user.h"
#include"menu.h"
#include<wx/wx.h>
#include<fstream>
#include<vector>

User::User(string name, string rollNo, string password)
    : name(name), rollNo(rollNo), password(password)
{
    loadUserData();
    transactionFileName = rollNo + "_transactions.txt";
}

bool User::registerUser()
{
    ifstream readFile("usersData.txt");
    if (!readFile.is_open())
    {
        wxLogDebug("readfile not open");
        wxMessageBox("File couldn't be opened",
            "Registration Error", wxOK | wxICON_ERROR);
        cout << "Error opening users file for reading." << endl;
        return false;
    }

    string fname, frollNo, fpassword, fbalance;
    while (readFile >> fname >> frollNo >> fpassword >> fbalance)
    {
        if (frollNo == this->rollNo)
        {
            wxLogDebug("same roll");
            wxMessageBox("A user with the same roll number already exists. Please enter a unique roll number.",
                "Registration Error", wxOK | wxICON_ERROR);
            readFile.close();
            return false;
        }
    }

    readFile.close(); // Close the file after reading

    ofstream writeFile("usersData.txt", ios::app);
    if (!writeFile.is_open())
    {   
        wxLogDebug("file not open");
        cout << "Error opening file for writing." << endl;
        return false;
    }

    wxLogDebug("writing to file");
    writeFile << name << " " << rollNo << " " << password << " " << balance << endl;
    writeFile.close();

    return true;
}

int User::getBalance()
{
    User::loadUserData();
    return(balance);
}

string User::getName()
{
    return(name);
}

string User::getRoll()
{
    return(rollNo);
}

bool User::loadUserForAdmin()
{
    ifstream readFile("usersData.txt");
    if (!readFile.is_open())
    {
        cout << "Error opening users file for reading." << endl;
        return false;
    }

    string fname, frollNo, fpassword;
    int fbalance;
    while (readFile >> fname >> frollNo >> fpassword >> fbalance)
    {
        if (this->rollNo == frollNo)
        {   
            this->password = fpassword;
            this->name = fname;
            if (fbalance > 0)
            {
                balance = fbalance;
            }
            return true;
        }
    }
    readFile.close();
    return false; // User not found
}

void User::buyItem()
{
    Menu M;
    if (M.getItems().empty())
    {
        cout << "Menu is empty. Please contact the admin." << endl;
        return;
    }

    vector<string> items = M.getItems();
    vector<int> prices = M.getPrice();

    vector<int> plate; // Store the indices of selected items in the plate

    cout << "Add items to the plate (Enter 0 when done): " << endl;

    while (true)
    {
        int choice;
        cout << "Enter item number to add (0 to finish): ";
        cin >> choice;
        cin.ignore();

        if (choice == 0)
            break;

        if (choice >= 1 && static_cast<size_t>(choice) <= items.size())
        {
            plate.push_back(choice);
        }
        else
        {
            cout << "Invalid item number. Please try again." << endl;
        }
    }

    if (!plate.empty())
    {
        int totalCost = 0;
        cout << "Items in the plate:" << endl;
        for (int i : plate)
        {
            cout << "- " << items[i - 1] << " - " << "Rs" << prices[i - 1] << endl;
            totalCost += prices[i - 1];
        }

        cout << "Total Cost: " << "Rs" << totalCost << endl;

        if (totalCost > balance)
        {
            cout << "Insufficient balance. Please add money to your account." << endl;
            return;
        }

        cout << "Confirm purchase? (Y/N): ";
        char confirm;
        cin >> confirm;
        cin.ignore();

        if (confirm == 'Y' || confirm == 'y')
        {
            balance -= totalCost;

            ofstream transactionFile(transactionFileName, ios::app);
            if (!transactionFile.is_open())
            {
                cout << "Error opening transactions file for writing." << endl;
                return;
            }

            for (int i : plate)
            {
                transactionFile << "Item bought: ";
                transactionFile.width(10);
                transactionFile.setf(ios::right, ios::adjustfield);
                transactionFile << items[i - 1]
                    << " for " << " Rs";
                transactionFile.width(6);
                transactionFile << prices[i - 1] << endl;

            }

            transactionFile.close();
            updateBalance(balance);
            cout << "Item(s) purchased successfully." << endl;
        }
        else
        {
            cout << "Purchase cancelled." << endl;
        }
    }
    else
    {
        cout << "Plate is empty. No items purchased." << endl;
    }
}

string User::getPassword()
{
    return string(password);
}

bool User::loadUserData()
{
    ifstream readFile("usersData.txt");
    if (!readFile.is_open())
    {
        cout << "Error opening users file for reading." << endl;
        return false;
    }

    string fname, frollNo, fpassword;
    int fbalance;
    while (readFile >> fname >> frollNo >> fpassword >> fbalance)
    {
        if (this->rollNo == frollNo && this->password == fpassword)
        {
            this->name = fname;
            if (fbalance > 0)
            {
                balance = fbalance;
            }
            return true;
        }
    }
    readFile.close();
    return false; // User not found
}

void User::updateBalance(const int &amount) {
    std::string filename = "usersData.txt";
    std::string tempFilename = "temp_usersData.txt";

    std::ifstream inputFile(filename);
    std::ofstream tempFile(tempFilename);

    if (!inputFile || !tempFile) {
        std::cerr << "Error opening files." << std::endl;
        return;
    }
    string fname, froll, fpass, fbal;
    while (inputFile >> fname >> froll >> fpass >> fbal) {
        if (froll == rollNo) {
            fbal = to_string(amount);
        }
        tempFile << fname << " " << froll << " " << fpass << " " << fbal << std::endl;
    }

    inputFile.close();
    tempFile.close();

    if (remove(filename.c_str()) != 0) {
        std::cerr << "Error deleting file." << std::endl;
        return;
    }

    if (rename(tempFilename.c_str(), filename.c_str()) != 0) {
        std::cerr << "Error renaming file." << std::endl;
        return;
    }

}

std::vector<string> User::readTransactionFile()
{
    std::vector<string> lines;
    std::string FilePath = "Transactions/" + transactionFileName;
    ifstream TransactionFile(FilePath);
    if (TransactionFile.is_open())
    {
        string line;
        while ((getline(TransactionFile, line)))
        {
            lines.push_back(line);
        }
        TransactionFile.close();
        return lines;
    }
    else
    {
        wxLogMessage("No transaction history available.");
        return lines;
    }
}