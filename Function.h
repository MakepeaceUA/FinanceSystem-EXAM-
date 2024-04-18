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
		cout << "Выберите операцию:\n";
		cout << "1 - Создать новое хранилище\n";
		cout << "2 - Пополнить счёт\n";  
		cout << "3 - Снять со счёта(расходы)\n";
		cout << "4 - Добавить хранилище в файл\n";
		cout << "5 - Удалить хранилище\n";
		cout << "6 - Список всех хранилищ\n";
		cout << "7 - Выход\n";
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
			cout << "Пока!";
			break;
		default:
			system("cls");
		}
	} while (choose != 7);
}

void Spending::Output() const
{
	cout << "Деньги:" << money << "\n" << "Категория:" << category << "\n";
}
void Spending::Input()
{
	cout << "Введите сумму денег:";
	cin >> money;
	cout << "Введите категорию:";
	cin >> category;
    system("cls");
}

void Card::Output() 
{
	cout << "Название банка:" << BankName << "\n";
}
void Card::Input() 
{
	system("cls");
	cout << "Введите название банка:";
	cin >> BankName;
	system("cls");
}
void Wallet::Output()
{
	system("cls");
	cout << "Тип кошелька:" << WalletType << "\n"; Sleep(1000);
	system("cls");
}
void Wallet::Input() 
{
	system("cls");
	cout << "Введите тип кошелька:";
	cin >> WalletType;
	system("cls");
}

void MoneyStorage::AddSpending()
{
	int amount;
	string category, date;
	cout << "Введите категорию расходов: ";
	cin >> category;
	cout << "Введите сумму расходов: ";
	cin >> amount;
	cout << "Введите дату(dd/mm/yyyy): ";
	cin >> date;


	Spending newSpending(amount,category, date);

	spend.insert(newSpending);

	ofstream outfile("spending.txt"); 

	if (!outfile) 
	{
		cout << "Ошибка!\n";
		return; 
	}
	TotalMoney -= amount;

	for (const auto& spending : spend) 
	{
		outfile << "Категория:" << spending.GetCategory() << "\n"
			<< "Сумма денег:" << spending.GetMoney() << "\n"
			<< "Дата:" << spending.GetDate() << "\n\n";
	}


	outfile.close();
	system("cls");
	return;
}
void MoneyStorage::Input() 
{
	cout << "Введите номер хранилиша: ";
	cin >> number;
	cout << "Введите сумму денег: ";
	cin >> TotalMoney;
	cout << "Введите кредитный лимит: ";
	cin >> CreditLimit;
}
void MoneyStorage::TopUp()
{
	system("cls");
	int amount;
	do
	{
		cout << "Введите сумму для пополнения: ";
		cin >> amount;
		if (TotalMoney + amount > CreditLimit)
		{
		    system("cls");
		}
		else if(amount == 0) 
		{
			system("cls");
			break;
		}
		else 
		{
			TotalMoney += amount;
			cout << "Счёт хранилища обновлён.\n"; Sleep(1000); system("cls");
			break;
		}
	} while (true);
	return;
}


void FinanceManagement::Output() 
{
	system("cls");
	if (storages.empty())
	{
		cout << "Хранилище не найдено."; Sleep(1000); system("cls");
		return;
	}
	else
	{
		for (auto storage : storages)
		{
			cout << "Хранилище: " << storage->GetNumber() << ", Баланс: " << storage->GetTotalMoney() << ", Кредитный лимит: " << storage->GetCreditLimit() << "\n";
		}
	}
	Sleep(5000); system("cls");
}
void FinanceManagement::DeleteStorage() 
{
	system("cls");
	int num;
	cout << "Введите номер хранилища:";
	cin >> num;
	for (auto i = storages.begin(); i != storages.end(); i++)
	{
		cout << "Хранилище удалено.\n"; Sleep(1000); system("cls");
        storages.erase(i);
        break;
	}
}
void FinanceManagement::TopUpStorage() 
{
	system("cls");
	int number;
	cout << "Введите номер хранилища:";
	cin >> number;
	for (auto storage : storages) 
	{
		if (storage->GetNumber() == number)
		{
			storage->TopUp();
		}
		else
			system("cls");
	}
}
void FinanceManagement::AddSpendingToStorage()
{
	system("cls");
	int number;
	cout << "Введите номер хранилища:";
	cin >> number;
	for (auto storage : storages)
	{
		if (storage->GetNumber() == number)
		{
			storage->AddSpending();
		}
		else
			system("cls");
	}
}

void FinanceManagement::WriteStoragesToFile()
{
	system("cls");
	ofstream outFile("storages.txt");
	if (!outFile.is_open())
	{
		cout << "Ошибка!\n";
		return;
	}

	for (auto storage : storages)
	{
		outFile << "Номер хранилища: " << storage->GetNumber() << "\n";
		outFile << "Сумма денег: " << storage->GetTotalMoney() << "\n";
		outFile << "Кредитный лимит: " << storage->GetCreditLimit() << "\n\n";
	}

	cout << "Хранилища добавлены в файл.\n"; Sleep(1000); system("cls");
	outFile.close();
}
void FinanceManagement::CreateStorage()
{
	system("cls");
	int storage, number, CreditLimit;
	cout << "Выберите хранилище:\n";
	cout << "1. Карта\n";
	cout << "2. Кошелёк\n";
	cin >> storage;
	system("cls");
	cout << "Введите номер хранилища (7 цифр): ";
	cin >> number;
	system("cls");
	if (to_string(number).length() == 7)
	{
		cout << "Введите кредитный лимит:";
		cin >> CreditLimit;

		if (storage == 1)
		{
			Card* newCard = new Card(number, CreditLimit, "");
			cout << "Новая карта создана.\n"; Sleep(1000);
			newCard->Input();
			storages.insert(newCard);
		}
		else if (storage == 2)
		{
			Wallet* newWallet = new Wallet(number, CreditLimit, "");
			newWallet->Input();
			cout << "Новый кошелёк создан.\n"; Sleep(1000);
			storages.insert(newWallet);
		}
		else
		{
			cout << "Неверный тип хранилища.\n";
		}
		system("cls");
	}
	return;
}
	
	



