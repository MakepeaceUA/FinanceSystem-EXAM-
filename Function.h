#pragma once
#include <iostream>
#include <set>
#include <Windows.h>
#include "Class.h"
#include <fstream>
using namespace std;



void Menu()
{
	FinanceManagement f_system;
	int choose;
	do
	{
		cout << "Choose operation:\n";
		cout << "1 - Create new storage\n";
		cout << "2 - Top up storage\n";  
		cout << "3 - Add spending to storage\n";
		cout << "4 - Storages to file\n";
		cout << "5 - Delete storage\n";
		cout << "6 - Output all storages\n";
		cout << "7 - Exit\n";
		cin >> choose;
		switch (choose)
		{
		case 1:
			f_system.CreateStorage();
			break;
		case 2:
			f_system.TopUpStorage();
			break;
		case 3:
			f_system.AddSpendingToStorage();
			break;
		case 4:
			f_system.WriteStoragesToFile();
			break;
		case 5:
			f_system.DeleteStorage();
			break;
        case 6:
			f_system.Output();
			break;
		case 7:
			system("cls");
			cout << "Bye!";
			break;
		default:
			system("cls");
		}
	} while (choose != 7);
}

void Spending::Output() const
{
	cout << "Money:" << money << "\n" << "Category:" << category << "\n";
}
void Spending::Input()
{
	cout << "Enter money:";
	cin >> money;
	cout << "Enter category:";
	cin >> category;
    system("cls");
}

void Card::Output() 
{
	cout << "Bank name:" << BankName << "\n";
}
void Card::Input() 
{
	system("cls");
	cout << "Enter bank name:";
	cin >> BankName;
	system("cls");
}
void Wallet::Output()
{
	system("cls");
	cout << "Wallet type:" << WalletType << "\n"; Sleep(1000);
	system("cls");
}
void Wallet::Input() 
{
	system("cls");
	cout << "Enter wallet type:";
	cin >> WalletType;
	system("cls");
}

void MoneyStorage::AddSpending()
{
	int amount;
	string category, date;
	cout << "Enter spending category: ";
	cin >> category;
	cout << "Enter spending amount: ";
	cin >> amount;
	cout << "Enter spending date (dd/mm/yyyy): ";
	cin >> date;


	Spending newSpending(amount,category, date);

	spend.insert(newSpending);

	ofstream outfile("spending.txt"); 

	if (!outfile) 
	{
		cout << "Error!\n";
		return; 
	}
	TotalMoney -= amount;

	for (const auto& spending : spend) 
	{
		outfile << "Category:" << spending.GetCategory() << "\n"
			<< "Total money:" << spending.GetMoney() << "\n"
			<< "Date:" << spending.GetDate() << "\n\n";
	}


	outfile.close();
	system("cls");
	return;
}
void MoneyStorage::Input() 
{
	cout << "Enter number: ";
	cin >> number;
	cout << "Enter total money: ";
	cin >> TotalMoney;
	cout << "Enter credit limit: ";
	cin >> CreditLimit;
}
void MoneyStorage::TopUp()
{
	int amount;
	cout << "Enter amount to top up: ";
	cin >> amount;
	TotalMoney += amount;
	cout << "Amount updated.\n"; Sleep(1000); system("cls");
	return;
}


void FinanceManagement::Output() 
{
	system("cls");
	if (storages.empty())
	{
		cout << "Storage does not exist."; Sleep(1000); system("cls");
		return;
	}
	else
	{
		for (auto storage : storages)
		{
			cout << "Storage: " << storage->GetNumber() << ", Balance: " << storage->GetTotalMoney() << ", Credit limit: " << storage->GetCreditLimit() << "\n";
		}
	}
	Sleep(5000); system("cls");
}
void FinanceManagement::DeleteStorage() 
{
	system("cls");
	int num;
	cout << "Enter number storage to delete:";
	cin >> num;
	for (auto i = storages.begin(); i != storages.end(); i++)
	{
		cout << "Storage delete.\n"; Sleep(1000); system("cls");
        storages.erase(i);
        break;
	}
}
void FinanceManagement::TopUpStorage() 
{
	system("cls");
	int number;
	cout << "Enter storage number to top up:";
	cin >> number;
	for (auto storage : storages) 
	{
		if (storage->GetNumber() == number) 
		{
			storage->TopUp();
		}
	}
	cout << "Storage not found.\n";
}
void FinanceManagement::AddSpendingToStorage()
{
	system("cls");
	int number;
	cout << "Enter storage number to add spending:";
	cin >> number;
	for (auto storage : storages)
	{
		if (storage->GetNumber() == number)
		{
			storage->AddSpending();
		}
	}
}

void FinanceManagement::WriteStoragesToFile()
{
	system("cls");
	ofstream outFile("storages.txt");
	if (!outFile.is_open())
	{
		cout << "Error!\n";
		return;
	}

	for (auto storage : storages)
	{
		outFile << "Storage Number: " << storage->GetNumber() << "\n";
		outFile << "Total Money: " << storage->GetTotalMoney() << "\n";
		outFile << "Credit Limit: " << storage->GetCreditLimit() << "\n\n";
	}

	cout << "Storages written to file successfully.\n"; Sleep(1000); system("cls");
	outFile.close();
}
void FinanceManagement::CreateStorage()
{
	system("cls");
	int storage, number, CreditLimit;
	cout << "Select storage:\n";
	cout << "1. Card\n";
	cout << "2. Wallet\n";
	cin >> storage;
	system("cls");
	cout << "Enter number (7 digits): ";
	cin >> number;
	system("cls");
	if (to_string(number).length() == 7)
	{
		cout << "Enter credit limit:";
		cin >> CreditLimit;

		if (storage == 1)
		{
			Card* newCard = new Card(number, CreditLimit, "");
			cout << "New card created.\n"; Sleep(1000);
			newCard->Input();
			storages.insert(newCard);
		}
		else if (storage == 2)
		{
			Wallet* newWallet = new Wallet(number, CreditLimit, "");
			newWallet->Input();
			cout << "New wallet created.\n"; Sleep(1000);
			storages.insert(newWallet);
		}
		else
		{
			cout << "Invalid storage type.\n";
		}
		system("cls");
	}
	return;
}
	
	



