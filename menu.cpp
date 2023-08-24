#include "menu.h"
#include<fstream>

vector<string>Menu::Items;
vector<int> Menu::Price;

class MenuItem {
public:
    string itemName;
    int itemPrice;
    MenuItem(string name, int price) :itemName(name), itemPrice(price) {}
};

void Menu::addItem(string item, int price)
{
    MenuItem I(item, price);
    ofstream file("menuData.txt", ios::app);
    if (!file.is_open())
    {
        wxLogError("Error opening file for writing.");
        return;
    }

    file << item << " " << price << endl;

    file.close();

    ifstream readFile("menuData.txt");
    if (!readFile.is_open())
    {
        wxLogError("Error opening file for reading.");
        return;
    }

    string itemName;
    int itemPrice;
    Items.clear();
    Price.clear();
    while (readFile >> itemName >> itemPrice)
    {
        Items.push_back(itemName);
        Price.push_back(itemPrice);
    }

    readFile.close();
}



vector<string>& Menu::getItems()
{
    ifstream readFile("menuData.txt");
    if (!readFile.is_open())
    {
        cout << "Error opening file for reading." << endl;
        return Items;
    }

    Items.clear();
    Price.clear();
    string itemName;
    int itemPrice;
    while (readFile >> itemName >> itemPrice)
    {
        Items.push_back(itemName);
        Price.push_back(itemPrice);
    }

    readFile.close();
    return Items;
}

vector<int>& Menu::getPrice()
{
    // Call getItems to ensure that the vectors are initialized.
    getItems();
    return Price;
}

void Menu::deleteItem(string item, int price) {
    getItems();
    for (int i = 0; i < Items.size(); i++) {
        if (item == Items[i])
        {
            Items.erase(Items.begin() + i);
            Price.erase(Price.begin() + i);
            break;

        }
    }
    std::ofstream outFile("menuData.txt", std::ios::out | std::ios::trunc);

    if (!outFile.is_open())
    {
        wxLogError("Error opening file for writing.");
        return;
    }
    for (int i = 0; i < Items.size(); i++) {
        outFile << Items[i] << " " << Price[i] << endl;
    }
}

void Menu::updatePrice(string item, int price)
{
    getItems();
    for (int i = 0; i < Items.size(); i++) {
        if (item == Items[i])
        {
            Price[i] = price;
            break;
        }
    }

    std::ofstream outFile("menuData.txt", std::ios::out | std::ios::trunc);

    if (!outFile.is_open())
    {
        wxLogError("Error opening file for writing.");
        return;
    }
    for (int i = 0; i < Items.size(); i++) {
        outFile << Items[i] << " " << Price[i] << endl;
    }
}