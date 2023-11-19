#pragma once
#include <iostream>
using namespace std;

class Date {
public:
	Date(const Date& date);
	Date(const int num);
	Date(const int d, const int m, const int y);
	size_t getDays();
	size_t days;
	size_t months;
	size_t years;
	
	Date& operator=(const Date& date);
	Date& operator=(const int num);
friend ostream& operator<<(ostream& out, const Date& date);
friend istream& operator>>(istream& in, Date& date);
};