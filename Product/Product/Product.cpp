#include "Product.h"
#include "Consts.h"
Product::Product() :name(nullptr), weight(0), issueDate(0),
expirationDate(0), price(0) {}

Product::Product(String name, size_t weight, Date iDate, size_t eDate, double price) : name(name), weight(weight), issueDate(iDate),
expirationDate(eDate), price(price) {}

String Product::getName() const
{
    return name;
}

void Product::setName(String str)
{
	name = str;
}

size_t Product::getWeight() const
{
    return weight;
}

void Product::setWeight(size_t w)
{
	weight = w;
}

Date Product::getIssueDate() const
{
    return issueDate;
}

void Product::setIssueDate(Date date)
{
	issueDate = date;
}

size_t Product::getExpirationDate() const
{
    return expirationDate;
}

void Product::setExpirationDate(size_t date)
{
	expirationDate = date;
}

void Product::setPrice(size_t price)
{
    this->price = price;
}

double Product::getPrice() const
{
    return price;
}

bool Product::promotionalProduct() const
{
	Date LocalDate(getLocalTime()->tm_mday, getLocalTime()->tm_mon + 1, getLocalTime()->tm_year + 1900);
	return ((LocalDate.getDays() - (this->getIssueDate().getDays() + this->expirationDate)) <= 2) ;
}

bool Product::expiredProduct() const
{
	Date LocalDate(getLocalTime()->tm_mday, getLocalTime()->tm_mon + 1, getLocalTime()->tm_year + 1900);
	return (this->getIssueDate().getDays() + this->expirationDate) < LocalDate.getDays();
}

ostream& operator<<(ostream& out, const Product& product) {
	out << "Name: " << product.name;
	out << "Weight: " << product.weight << endl;
	out << "Date: " << product.issueDate;
	out << "Expiration Date: " << product.expirationDate << endl;
	out << "Price = " << product.price << endl;
	return out;
}

istream& operator>>(istream& in, Product& product) {
	in >> product.name;
	in >> product.weight ;
	in >> product.issueDate;
	in >> product.expirationDate;
	in >> product.price;
	return in;
}
