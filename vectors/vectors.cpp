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
#include <vector>
#include "Structures.h"

using namespace std;

void printMenu(Table& table, MaxStrLen& maxLen);
void printTable(Table& table, MaxStrLen& maxLen);
Movie createInfo(MaxStrLen& maxLen);
void insertInfo(Movie info, Table& table);
int deleteInfo(Table& table);
void createCinemaList(Table& table, string filmName);
void printVector(vector<string> vec);


void main()
{
	setlocale(LC_ALL, "Russian");

	Table table;
	Movie tempInfo;
	MaxStrLen maxLen;

	int userChoice = -1;
	int deletedInfo = 0;
	int cinemaCounter = 0;
	string filmName;

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
				cout << "������� " << deletedInfo << " �������" << endl;
			}
			system("pause");
			break;
		case 3:
			cout << "������ �����������, � ������� ����� ���������� �������� �����." << endl;
			cout << "����� ����� �� ������ ����������? : ";
			getline(cin, filmName);
			createCinemaList(table, filmName);
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
		"������� 3, ����� ������� ������ �����������, � ������� ����� ���������� �������� �����.\n"
		"������� 0, ����� ��������� ��������.\n";
	cout << "��� �����: ";
}

void printTable(Table& table, MaxStrLen& maxLen)
{
	string cinemaStr = "���������", movieStr = "�����", priceStr = "����";
	maxLen.cinema = max(maxLen.cinema, cinemaStr.length());
	maxLen.movie = max(maxLen.movie, movieStr.length());
	maxLen.price = max(maxLen.price, priceStr.length());

	unsigned headerLen = 58 + maxLen.cinema + maxLen.movie + maxLen.price;

	if (!table.infoList.empty())
	{
		string sep = "| ";

		cout << endl;
		cout << setfill('-') << setw(headerLen) << ' ' << endl;
		cout << setfill(' ');
		cout << sep << setw(maxLen.cinema) << cinemaStr;
		cout << sep << setw(maxLen.movie) << movieStr;
		cout << sep << setw(10) << "���� ";
		cout << sep << setw(5) << "�����";
		cout << sep << setw(maxLen.price) << priceStr;
		cout << sep << endl;
		cout << setfill('-') << setw(headerLen) << ' ' << endl;
		cout << setfill(' ');

		for (size_t i = 0; i < table.infoList.size(); i++)
		{
			cout << sep << setw(maxLen.cinema) << table.infoList[i].cinemaName;
			cout << sep << setw(maxLen.movie) << table.infoList[i].movieName;
			cout << sep << table.infoList[i].date.day / 10
				<< table.infoList[i].date.day % 10 << '.'
				<< table.infoList[i].date.month / 10
				<< table.infoList[i].date.month % 10 << '.'
				<< table.infoList[i].date.year;
			cout << sep << table.infoList[i].time.hour / 10
				<< table.infoList[i].time.hour % 10 << ':'
				<< table.infoList[i].time.minute / 10
				<< table.infoList[i].time.minute % 10;
			cout << sep << setw(maxLen.price) << table.infoList[i].price;
			cout << sep << endl;
			cout << setfill('-') << setw(headerLen) << ' ' << endl;
			cout << setfill(' ');
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
	cout << "������� ��������� ������: ";
	cin >> newMovie.price;

	maxLen.cinema = max(newMovie.cinemaName.length(), maxLen.cinema);
	maxLen.movie = max(newMovie.movieName.length(), maxLen.cinema);
	maxLen.price = max(size_t(log10(newMovie.price)) + 1, maxLen.price);

	return newMovie;
}

void insertInfo(Movie info, Table& table)
{
	for (size_t i = 0; i < table.infoList.size(); i++)
	{
		if (info.cinemaName == table.infoList[i].cinemaName)
		{
			table.infoList.insert(table.infoList.begin() + i, info);
			return;
		}
	}
	table.infoList.push_back(info);

}

int deleteInfo(Table& table)
{
	int day, month, year;
	int deletedInfo = 0;

	cout << "������� ����: ";
	cin >> day;
	cout << "������� �����: ";
	cin >> month;
	cout << "������� ���: ";
	cin >> year;

	for (size_t i = 0; i < table.infoList.size(); i++)
	{
		Date comparableDate = table.infoList[i].date;

		if (comparableDate.year == year &&
			comparableDate.month == month &&
			comparableDate.day == day)
		{
			table.infoList.erase(table.infoList.begin() + i);
			i--;
			deletedInfo++;
		}
	}

	return deletedInfo;
}

void createCinemaList(Table& table, string filmName)
{
	vector<string> cinemaList;
	bool flag = true;

	for (size_t i = 0; i < table.infoList.size(); i++)
	{
		if (table.infoList[i].movieName == filmName)
		{
			flag = true;

			for (size_t j = 0; j < cinemaList.size(); j++)
			{
				if (table.infoList[i].cinemaName == cinemaList[j])
				{
					flag = false;
				}
			}

			if (flag)
			{
				cinemaList.push_back(table.infoList[i].cinemaName);
			}
		}
	}

	if (!cinemaList.empty())
	{
		cout << "���������� ������ ����� �� ������ � ��������� �����������: " << endl;
		printVector(cinemaList);
	}
	else
	{
		cout << "� ���������, �� ������� ������������, � ������� ����� ���������� ������ �����." << endl;
	}
}

void printVector(vector<string> vec)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << endl;
	}
}
