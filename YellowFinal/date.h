#pragma once

#include <iostream>

using namespace std;

class Date {
public:
	// конструктор выбрасывает исключение, если его аргументы некорректны
	Date(int new_year, int new_month, int new_day);

	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;
	string str() const;

private:
	int year;
	int month;
	int day;
};

Date ParseDate(istream& date_stream);

bool operator<(const Date& lhs, const Date& rhs);

bool operator>(const Date& lhs, const Date& rhs);

bool operator==(const Date& lhs, const Date& rhs);

bool operator!=(const Date& lhs, const Date& rhs);

bool operator>=(const Date& lhs, const Date& rhs);

bool operator<=(const Date& lhs, const Date& rhs);

ostream& operator<<(ostream& stream, const Date& date);