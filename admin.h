#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<wx/wx.h>
using namespace std;

class Admin
{
private:
    string id;
    string name;
    string password;
    string adminData[3];
public:
    Admin() {};
    Admin(string id, string name, string password);
    bool login();
    void display();
    void addItem();
    void updatePrice();
    void addMoneyToUser();
};

