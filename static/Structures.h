#pragma once
#include <string>

using namespace std;

const int maxTableSize = 100;

struct Date
{
	unsigned day;
	unsigned month;
	unsigned year;
};

struct Time
{
	unsigned minute;
	unsigned hour;
};

struct Movie
{
	string cinemaName;
	string movieName;
	Date date;
	Time time;
	float price;
};

struct Table
{
	Movie infoList[maxTableSize] = {};
	int tableSize = 0;
};

struct MaxStrLen
{
	size_t cinema = 0;
	size_t movie = 0;
	size_t price = 0;
};