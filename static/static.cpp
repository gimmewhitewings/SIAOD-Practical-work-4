//��������� ������.��������� ������ � ������ : �������� ����������, �������� ������, ����, ����� ������, ��������� ������.
//��������
//1)	���������� ������ �� ������ � ����������.
//2)	�������� ������ �� ������ � �������, ������������ �� �������� ���������� ����� ������ ������� �� ����� ����������(���������� �� ������������).���� ������ �� ������������ ���������� �� ����, �� �������� ������ � ����� �������.
//3)	������� ������ �� �������� ����.
//4)	������� ������ �����������, � ������� ����� ���������� �������� �����(�� ��������).

#include <iostream>
#include <locale>
#include <iomanip>
#include <string>
#include "Structures.h"

using namespace std;

void printMenu(Table& table, MaxStrLen& maxLen);
void printTable(Table& table, MaxStrLen& maxLen);
Movie createInfo(MaxStrLen& maxLen);
void insertInfo(Movie info, Table& table);
int deleteInfo(Table& table);
void createCinemaList(Table& table);

void main()
{
	setlocale(LC_ALL, "Russian");

	Table table{};
	Movie tempInfo{};
	MaxStrLen maxLen;

	int userChoice = -1;
	int deletedInfo = 0;

	while (userChoice != 0)
	{
		system("cls");
		printMenu(table, maxLen);
		cin >> userChoice;
		cin.ignore();
		switch (userChoice)
		{
		case 1:
			cout << "��������� ���������� � ������ � �������" << endl;
			insertInfo(createInfo(maxLen), table);
			cout << "������ �������� � �������." << endl;
			system("pause");
			break;
		case 2:
			cout << "�������� ������� �� �������� ����" << endl;
			deletedInfo = deleteInfo(table);
			if (deletedInfo != 0)
			{
				cout << "������� " << deletedInfo << " �������";
			}
			system("pause");
			break;
		case 0:
			cout << "�������, �� ��������!" << endl;
			break;
		default:
			cout << "��������, � �� ������� ���. ����������, ��������� ����" << endl;
			cin.clear();
			system("pause");
			break;
		}
	}
}

void printMenu(Table& table, MaxStrLen& maxLen)
{
	cout << "������������ ������ �4 ����-03-21 ��������� �.�. ������� 22\n\n"
		"������� 4 - ���������. ���������� ������.\n"
		"================����================\n"
		"�������:";
	printTable(table, maxLen);
	cout << endl;
	cout << "������� 1, ����� ������ ���������� � ������.\n"
		"������� 2, ����� ������� ������ �� �������� ����.\n"
		"������� 3, ����� ������� ������ �����������, � ������� ����� ���������� �������� �����\n";
	cout << "��� �����: ";
}

void printTable(Table& table, MaxStrLen& maxLen)
{
	string cinemaStr = "��������� ", movieStr = "����� ", priceStr = "���� ";
	maxLen.cinema = max(maxLen.cinema, cinemaStr.length());
	maxLen.movie = max(maxLen.movie, movieStr.length());
	maxLen.price = max(maxLen.price, priceStr.length());

	unsigned headerLen = 58 + maxLen.cinema + maxLen.movie + maxLen.price;
	
	if (table.tableSize != 0)
	{
		string sep = "| ";

		cout << endl;
		cout << setfill('-') << setw(headerLen) << endl;
		cout << sep << setw(maxLen.cinema) << cinemaStr;
		cout << sep << setw(maxLen.movie) << movieStr;
		cout << sep << setw(10) << "���� ";
		cout << sep << setw(8) << "����� ";
		cout << sep << setw(maxLen.price) << priceStr;
		cout << sep << endl;
		cout << setfill('-') << setw(headerLen) << endl;

		for (size_t i = 0; i < table.tableSize; i++)
		{
			cout << sep << setw(maxLen.cinema) << table.infoList[i].cinemaName;
			cout << sep << setw(maxLen.movie) << table.infoList[i].movieName;
			cout << sep << setw(10) << table.infoList[i].date.day / 10 
				<< table.infoList[i].date.day % 10 << '.' 
				<< table.infoList[i].date.month / 10 
				<< table.infoList[i].date.month % 10 << '.'
				<< table.infoList[i].date.year;
			cout << sep << setw(5) << table.infoList[i].time.minute / 10  
				<< table.infoList[i].time.minute % 10 << ':' 
				<< table.infoList[i].time.hour;
			cout << sep << setw(maxLen.price) << table.infoList[i].price;
			cout << sep << endl;
			cout << setfill('-') << setw(headerLen) << endl;
		}
	}
	else
	{
		cout << "������� �����\n";
	}
}

Movie createInfo(MaxStrLen& maxLen)
{
	Movie newMovie;
	cout << "������� �������� ����������: ";
	getline(cin, newMovie.cinemaName);
	cout << "������� �������� ������: ";
	getline(cin, newMovie.movieName);
	cout << "������� ���� ������: ";
	cin >> newMovie.date.day;
	cout << "������� ����� ������: ";
	cin >> newMovie.date.month;
	cout << "������� ��� ������: ";
	cin >> newMovie.date.year;
	cout << "������� ��� ������ ������: ";
	cin >> newMovie.time.hour;
	cout << "������� ������ ������ ������: ";
	cin >> newMovie.time.minute;

	maxLen.cinema = max(newMovie.cinemaName.length(), maxLen.cinema);
	maxLen.movie = max(newMovie.movieName.length(), maxLen.cinema);
	maxLen.price = max(size_t(log10(newMovie.price)) + 1, maxLen.price);

	return newMovie;
}

void insertInfo(Movie info, Table& table)
{
	bool flag = false;
	if (table.tableSize != 0)
	{
		for (size_t i = 0; i < table.tableSize; i++)
		{
			if (info.cinemaName == table.infoList[i].cinemaName)
			{
				flag = true;
				for (size_t j = table.tableSize - 1; j < 0; j--)
				{
					table.infoList[i + 1] = table.infoList[i];
				}
				table.infoList[i] = info;
				break;
			}
		}
	}
	else if (table.tableSize == 0 || !flag)
	{
		table.infoList[table.tableSize] = info;
	}
	table.tableSize++;
}

int deleteInfo(Table& table)
{
	int day, month, year;
	int deletedInfo = 0;

	cout << "������� ���: ";
	cin >> year;
	cout << "������� �����: ";
	cin >> month;
	cout << "������� ����: ";
	cin >> day;

	for (size_t i = 0; i < table.tableSize; i++)
	{
		Date comparableDate = table.infoList[i].date;

		if (comparableDate.year == year &&
			comparableDate.month == month &&
			comparableDate.day == day)
		{
			for (size_t j = i; j < table.tableSize - 1; j--)
			{
				table.infoList[j] = table.infoList[j + 1];
			}
			table.tableSize--;
			deletedInfo++;
		}
	}

	return deletedInfo;
}

void createCinemaList(Table& table)
{
	string cinemaList[100];
	int cinemaCounter = 0;

	for (size_t i = 0; i < length; i++)
	{

	}
}
