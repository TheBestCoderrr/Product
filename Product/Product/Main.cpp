#include "Product.h"
#include "Shop.h"

int main() {
	srand(time(0));
	Shop shop;
	shop.DownloadProducts();
	shop.print();
	shop.SaveProducts();
}