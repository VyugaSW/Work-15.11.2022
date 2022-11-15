#pragma once
#include <iostream>
#include <iomanip>
using namespace std;

class Product
{
private:
	char* name = new char[125]{NULL};
	double price = NULL;
	int count = NULL;
public:
	//Заполнение информации по продукту
	void fillProduct(const char* name, double price, int count) {
		strcpy_s(Product::name,126, name);
		Product::price = price;
		Product::count = count;
	}
	//Вывод одного продукта
	void PrintProduct() {
		cout << setw(15) << name << "\t\t" << setw(14) << price << "\t\t" << setw(14) << count << endl;
	}
	//Те крохотные функцие, о коих вы нам сказывали
	char* getName() {
		return name;
	}
	double getPrice() {
		return price;
	}
	int getCount() {
		return count;
	}
};

