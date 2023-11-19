#pragma once
#include "String.h"
#include "Date.h"


class Product
{
public:
	Product();
	Product(String name, size_t weight, Date iDate, size_t eDate, double price);
	String getName() const;
	void setName(String str);
	size_t getWeight() const;
	void setWeight(size_t w);
	Date getIssueDate() const;
	void setIssueDate(Date date);
	size_t getExpirationDate() const;
	void setExpirationDate(size_t date);
	void setPrice(size_t price);
	double getPrice() const;
	bool promotionalProduct() const;
	bool expiredProduct() const;
private:
	String name;
	size_t weight;
	Date issueDate;
	size_t expirationDate;
	double price;
friend ostream& operator<<(ostream& out, const Product& product);
friend istream& operator>>(istream& in, Product& product);
};

