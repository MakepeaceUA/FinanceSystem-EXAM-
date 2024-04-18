#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include "Function.h"
using namespace std;


class Spending
{

    string category;
    double money;
    string date;
public:
    Spending()
    {
        money = 0;
        category = "";
        date = " ";
    }
    Spending(float mon, string cat,string dt)
    {
        money = mon;
        category = cat;
        date = dt;
    }
    void Output() const;
    void Input();
    float GetMoney() const 
    {
        return money;
    }
    string GetCategory() const 
    {
        return category;
    }
    string GetDate() const
    {
        return date;
    }
    bool operator<(const Spending& other) const
    {
        return money < other.money;
    }
};

class MoneyStorage 
{
protected:
    long long number;
    float TotalMoney;
    multiset<Spending> spend;
    float CreditLimit;
public:
    MoneyStorage()
    {
        number = 0;
        TotalMoney = 0;
        CreditLimit = 0;
    }
    MoneyStorage(long long num, float credit)
    {
        number = num;
        TotalMoney = 0;
        CreditLimit = credit;
    }
    MoneyStorage(const multiset<Spending>& spe, long long num, float money, float credit)
    {
        spend = spe;
        number = num;
        TotalMoney = money;
        CreditLimit = credit;
    }

    virtual void Output() = 0;

    void Input();
    void TopUp();
    void AddSpending();

    int GetNumber() const 
    {
        return number;
    }

    float GetTotalMoney() const 
    {
        return TotalMoney;
    }

    float GetCreditLimit() const 
    {
        return CreditLimit;
    }

    multiset<Spending> GetSpendings() const 
    {
        return spend;
    }

};

class FinanceManagement 
{
    set<MoneyStorage*> storages;
public:
    FinanceManagement() {}

    void AddStorage(MoneyStorage* ptr) 
    {
        storages.insert(ptr);
    }
    void Output();
    void DeleteStorage();
    void TopUpStorage();
    void AddSpendingToStorage();
    void WriteStoragesToFile();
    void CreateStorage();
};


class Card : public MoneyStorage
{
    string BankName;
public:
    Card() 
    {
        BankName = " ";
    }
    Card(long long num, float credit, string name) : MoneyStorage(num,credit)
    {
        BankName = name;
    }
    Card(multiset<Spending>& mlset, long long num, float tl_money, float credit, string name) : MoneyStorage(mlset, num, tl_money, credit)
    {
        BankName = name;
    }

    void Output();
    void Input();
};
class Wallet : public MoneyStorage
{
    string WalletType;
public:
    Wallet()
    {
        WalletType = " ";
    };
    Wallet(long long num, float credit, string type) : MoneyStorage(num,credit)
    {
        WalletType = type;
    }
    Wallet(multiset<Spending>& mlset, long long num, float tl_money, float credit, string type) : MoneyStorage(mlset, num, tl_money, credit)
    {
        WalletType = type;
    }
    
    void Output();
    void Input();
};
