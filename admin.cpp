#include "admin.h"
#include"menu.h"
#include"fstream"
Admin::Admin(string id, string name, string password)
    : id(id), name(name), password(password), adminData{"admin123","admin","adminPassword" }
{
    
}

bool Admin::login()
{
    return (adminData[0] == id &&adminData[2] == password);
}


void Admin::updatePrice()
{
    Menu M;
    vector<string> items = M.getItems();
    vector<int> prices = M.getPrice();

    if (items.empty())
    {
        cout << "Menu is empty. Nothing to update." << endl;
        return;
    }

    int itemNum;
    cout << "Enter the item number to update price: ";
    cin >> itemNum;
    cin.ignore();

    if (itemNum >= 1 && static_cast<size_t>(itemNum) <= items.size())
    {
        int newPrice;
        itemNum -= 1;
        cout << "Enter the new price for " << items[itemNum] << ": ";
        cin >> newPrice;
        cin.ignore();

        prices[itemNum] = newPrice;

        ofstream writeFile("menuData.txt");
        if (!writeFile.is_open())
        {
            cout << "Error opening file for writing." << endl;
            return;
        }

        for (size_t i = 0; i < items.size(); ++i)
        {
            writeFile << items[i] << " " << prices[i] << endl;
        }

        writeFile.close();

        cout << "Price updated successfully." << endl;
    }
    else
    {
        cout << "Invalid item number." << endl;
    }
}

void Admin::addMoneyToUser()
{
    string userRollNo, userName;
    cout << "Enter the Roll No and name of the user to add money: ";
    cin >> userRollNo;
    cin.ignore();
    cin >> userName;

    ifstream readFile("usersData.txt");
    if (!readFile.is_open())
    {
        cout << "Error opening users file for reading." << endl;
        return;
    }

    string name, rollNo, password;
    int balance;
    bool found = false;
    string updatedData;

    while (readFile >> name >> rollNo >> password >> balance)
    {
        if (rollNo == userRollNo && password == userName)
        {
            int amount;
            cout << "Enter the amount to add to user's balance: ";
            cin >> amount;
            cin.ignore();

            balance += amount;
            found = true;
        }

        updatedData += name + " " + rollNo + " " + password + " " + to_string(balance) + "\n";
    }

    readFile.close();

    if (!found)
    {
        cout << "User with Roll No " << userRollNo << " not found." << endl;
        return;
    }

    // Rewrite the entire file with the updated data
    ofstream writeFile("usersData.txt");
    if (!writeFile.is_open())
    {
        cout << "Error opening users file for writing." << endl;
        return;
    }

    writeFile << updatedData;

    cout << "Money added to the user's balance. Updated balance: " << balance << " INR" << endl;
}
