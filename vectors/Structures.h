#pragma once
#include <string>
#include <vector>

using namespace std;

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
	vector<Movie> infoList;
};

struct MaxStrLen
{
	size_t cinema = 0;
	size_t movie = 0;
	size_t price = 0;
};