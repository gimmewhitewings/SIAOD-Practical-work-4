//Киноафиша города.Структура записи о сеансе : название кинотеатра, название фильма, дата, время начала, стоимость билета.
//Операции
//1)	Заполнение записи по сеансу с клавиатуры.
//2)	Вставить запись по сеансу в таблицу, упорядочивая по названию кинотеатра перед первой записью по этому кинотеатру(сортировку не использовать).Если записи по вставляемому кинотеатру не было, то добавить запись в конец таблицы.
//3)	Удалить записи по заданной дате.
//4)	Вывести список кинотеатров, в которых можно посмотреть заданный фильм(по названию).

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
void createCinemaList(Table& table, string filmName, int* cinemaCounter);
void printArray(string* array, int size);

void main()
{
	setlocale(LC_ALL, "Russian");

	Table table{};
	Movie tempInfo{};
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
			cout << "Занесение информации о сеансе в таблицу" << endl;
			insertInfo(createInfo(maxLen), table);
			cout << "Запись занесена в таблицу." << endl;
			system("pause");
			break;
		case 2:
			cout << "Удаление записей по заданной дате" << endl;
			deletedInfo = deleteInfo(table);
			if (deletedInfo != 0)
			{
				cout << "Удалено " << deletedInfo << " записей" << endl;
			}
			system("pause");
			break;
		case 3:
			cout << "Список кинотетаров, в которых можно посмотреть заданный фильм." << endl;
			cout << "Какой фильм вы хотите посмотреть? : ";
			getline(cin, filmName);
			createCinemaList(table, filmName, &cinemaCounter);
			system("pause");
			break;
		case 0:
			cout << "Спасибо, до свидания!" << endl;
			break;
		default:
			cout << "Извините, я не понимаю вас. Пожалуйста, повторите ввод" << endl;
			cin.clear();
			system("pause");
			break;
		}
	}
}

void printMenu(Table& table, MaxStrLen& maxLen)
{
	cout << "Практическая работа №4 ИКБО-03-21 Поведенок С.С. Вариант 22\n\n"
		"Задание 4 - Структуры. ОДномерный массив.\n"
		"================Меню================\n"
		"Таблица:";
	printTable(table, maxLen);
	cout << endl;
	cout << "Введите 1, чтобы внести информацию о сеансе.\n"
		"Введите 2, чтобы удалить записи по заданной дате.\n"
		"Введите 3, чтобы вывести список кинотеатров, в которых можно посмотреть заданный фильм.\n"
		"Введите 0, чтобы закончить проверку.\n";
	cout << "Выш выбор: ";
}

void printTable(Table& table, MaxStrLen& maxLen)
{
	string cinemaStr = "Кинотеатр", movieStr = "Фильм", priceStr = "Цена";
	maxLen.cinema = max(maxLen.cinema, cinemaStr.length());
	maxLen.movie = max(maxLen.movie, movieStr.length());
	maxLen.price = max(maxLen.price, priceStr.length());

	unsigned headerLen = 58 + maxLen.cinema + maxLen.movie + maxLen.price;
	
	if (table.tableSize != 0)
	{
		string sep = "| ";

		cout << endl;
		cout << setfill('-') << setw(headerLen) << ' ' << endl;
		cout << setfill(' ');
		cout << sep << setw(maxLen.cinema) << cinemaStr;
		cout << sep << setw(maxLen.movie) << movieStr;
		cout << sep << setw(10) << "Дата ";
		cout << sep << setw(5) << "Время";
		cout << sep << setw(maxLen.price) << priceStr;
		cout << sep << endl;
		cout << setfill('-') << setw(headerLen) << ' ' << endl;
		cout << setfill(' ');

		for (size_t i = 0; i < table.tableSize; i++)
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
		cout << "Таблица пуста\n";
	}
}

Movie createInfo(MaxStrLen& maxLen)
{
	Movie newMovie;
	cout << "Введите название кинотеатра: ";
	getline(cin, newMovie.cinemaName);
	cout << "Введите название фильма: ";
	getline(cin, newMovie.movieName);
	cout << "Введите день сеанса: ";
	cin >> newMovie.date.day;
	cout << "Введите месяц сеанса: ";
	cin >> newMovie.date.month;
	cout << "Введите год сеанса: ";
	cin >> newMovie.date.year;
	cout << "Введите час начала сеанса: ";
	cin >> newMovie.time.hour;
	cout << "Введите минуту начала сеанса: ";
	cin >> newMovie.time.minute;
	cout << "Введите стоимость билета: ";
	cin >> newMovie.price;

	maxLen.cinema = max(newMovie.cinemaName.length(), maxLen.cinema);
	maxLen.movie = max(newMovie.movieName.length(), maxLen.cinema);
	maxLen.price = max(size_t(log10(newMovie.price)) + 1, maxLen.price);

	return newMovie;
}

void insertInfo(Movie info, Table& table)
{
	if (table.tableSize != 0)
	{
		for (size_t i = 0; i < table.tableSize; i++)
		{
			if (info.cinemaName == table.infoList[i].cinemaName)
			{
				for (size_t j = table.tableSize; j > i; j--)
				{
					table.infoList[j] = table.infoList[j - 1];
				}
				table.infoList[i] = info;
				return;
			}
		}
	}
	table.infoList[table.tableSize] = info;
	table.tableSize++;
}

int deleteInfo(Table& table)
{
	int day, month, year;
	int deletedInfo = 0;

	cout << "Введите день: ";
	cin >> day;
	cout << "Введите месяц: ";
	cin >> month;
	cout << "Введите год: ";
	cin >> year;

	for (size_t i = 0; i < table.tableSize; i++)
	{
		Date comparableDate = table.infoList[i].date;

		if (comparableDate.year == year &&
			comparableDate.month == month &&
			comparableDate.day == day)
		{
			for (size_t j = i; j < table.tableSize - 1; j++)
			{
				table.infoList[j] = table.infoList[j + 1];
			}
			table.tableSize--;
			i--;
			deletedInfo++;
		}
	}

	return deletedInfo;
}

void createCinemaList(Table& table, string filmName, int* cinemaCounter)
{
	string cinemaList[100];
	bool flag = true;

	for (size_t i = 0; i < table.tableSize; i++)
	{
		if (table.infoList[i].movieName == filmName)
		{
			flag = true;

			for (size_t j = 0; j < *cinemaCounter; j++)
			{
				if (table.infoList[i].cinemaName == cinemaList[j])
				{
					flag = false;
				}
			}

			if (flag)
			{
				cinemaList[*cinemaCounter] = table.infoList[i].cinemaName;
				*cinemaCounter += 1;
			}
		}
	}

	if (*cinemaCounter != 0)
	{
		cout << "Посмотреть данный фильм вы можете в следующих кинотеатрах: " << endl;
		printArray(cinemaList, *cinemaCounter);
	}
	else
	{
		cout << "К сожалению, не нашлось кинотетатров, в которых можно посмотреть данный фильм." << endl;
	}
}

void printArray(string* array, int size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << array[i] << endl;
	}
}
