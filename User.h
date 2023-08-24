#pragma once
#include<iostream>
#include<vector>
#include<string>
#include<wx/wx.h>
using namespace std;

class User
{
private:
    string name;
    string rollNo;
    string password;
    int balance = 0;

public:
    string transactionFileName;
    int totalcost;
    User() {}
    User(string name, string rollNo, string password);
    bool registerUser();
    int getBalance();
    string getName();
    string getRoll();
    string getPassword();
    void buyItem();
    bool loadUserData();
    bool loadUserForAdmin();
    void addMoney(int amount);
    void updateBalance(const int&);
    std::vector<string> readTransactionFile();
};
