#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<wx/wx.h>
using namespace std;
class Menu
{
private:
    static vector<string> Items;
    static vector<int> Price;
public:
    class MenuItem {
    public:
        string itemName;
        int itemPrice;
        MenuItem() {};
        MenuItem(string, int) {}
    };
    void deleteItem(string item, int price);
    void updatePrice(string item,int price);
    void addItem(string,int);
    vector<string>& getItems();
    vector<int>& getPrice();
};

