
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include "Product.h"

using namespace std;

int total_revenues = 0;

struct Check {
	char* name = new char[125];
	double price;
	int count;
};

void FillList(Product** product); //Заполнение списка продуктов
void PrintList(Product** product, int size); //Вывод списка продуктов
Check* UpdateCheck(Check* total, int& sizeTotal); //Добавление продукта в чек
Check UpdateCheckOb(Check* total, int index); //Создание объекта для функции выше (как буфера)
void CheckCopyStart(Product* product, int index, Check* total, int size_total); //начала копирование чек
void CheckCopyEnd(Check p, Check* total, int size_total); //Конец копирование чек
void CustomerChoice(Product** product, int size, double& amount, Check* total, int& size_total); //Выбор покупателя
Product** DeleteProduct(Product** oldProduct, int& size, int index); //Удаление продукта из списка
void VerifyProduct(Product** product, int &size); //Проверка на наличие продукта
void CheckPrint(Check* total, int size_total); //Вывод чека
Check* NulledCheck(Check* total); //Обнуление чека

//Заполнение списка продуктов
void FillList(Product** product) {
	//Массив статичен и вы позволили, значит я имею право так сделать!!!!!!!!!!!!!!!!!!!
	product[0] = new Product("Potato",1.5,100);
	product[1] = new Product("Carrot", 2.0, 50);
	product[2] = new Product("Beans", 3, 20);
	product[3] = new Product("Water", 1.0, 150);
	product[4] = new Product("Black bread", 2.5, 70);
	product[5] = new Product("White bread", 3.0, 65);
	product[6] = new Product("Beer", 5.0, 25);
	product[7] = new Product("Wine", 20.0, 15);
	product[8] = new Product("Banana", 1.2, 50);
	product[9] = new Product("Cognac", 35.0, 10);
	product[10] = new Product("Milk 3.2 liters", 4.5, 95);
	product[11] = new Product("Milk 1 liters", 1.5, 125);
	product[12] = new Product("Cheese", 5.0, 75);
	product[13] = new Product("Chocolate 100g", 7.5, 30);
	product[14] = new Product("Whale tears", 50, 5);
}
//Вывод списка товаров
void PrintList(Product** product, int size) {
	system("cls");
	cout  << "\t|Name|\t\t\t" << "  |Price|\t\t " << " |Count|\n";
	for (int i = 0; i < size; i++) {
		product[i]->PrintProduct();
	}
}
//Увеличение размера чека
Check UpdateCheckOb(Check* total, int index) {
	Check p;
	strcpy_s(p.name, 126, total[index].name);
	p.count = total[index].count;
	p.price = total[index].price;
	return p;
}
Check* UpdateCheck(Check* total, int &sizeTotal) {
	sizeTotal++;
	Check p;
	Check* newCheck = new Check[sizeTotal];
	for (int i = 0; i < sizeTotal-1; i++) {
		p = UpdateCheckOb(total, i);
		strcpy_s(newCheck[i].name, 126, p.name);
		newCheck[i].count = p.count;
		newCheck[i].price = p.price;
	}
	return newCheck;
}
//Копирование покупки (одной) в объект структуры Check
void CheckCopyStart(Product** product, int index, Check* total, int size_total) {
	Check p;
	strcpy_s(p.name, 126, product[index]->getName());
	p.count = product[index]->getCount();
	p.price = product[index]->getPrice();
	CheckCopyEnd(p, total, size_total);
}
void CheckCopyEnd(Check p, Check* total, int size_total) {
	strcpy_s(total[size_total - 1].name, 126, p.name);
	total[size_total - 1].count = p.count;
	total[size_total - 1].price = p.price;
}
//Выбор и покупка покупателя
void CustomerChoice(Product** product, int size, double &amount, Check* total, int &size_total) {
	int count;
	char* buff = new char[125];
	cout << "Enter a name of product and it count:\n";
	gets_s(buff, 200);
	cin >> count;
	cin.ignore();
	for (int i = 0; i < size; i++) {
		if (strcmp(buff, product[i]->getName()) == 0) {

			if (count > product[i]->getCount()) {
				cout << "\n\tWRONG!\n";
				Sleep(1000);
				break;
			}

			total = UpdateCheck(total, size_total); //Добавляем в чек единицу для продукта
			CheckCopyStart(product, i, total, size_total); //Копируем в чек продукт
			amount += product[i]->getPrice()*count; //Сумма единичной покупки
			//Меняем количество товара
			product[i]->setCount(product[i]->getCount() - count);
			break;
		}
	}
}
//Удаление элемента из массива
Product** DeleteProduct(Product** oldProduct, int &size, int index) {
	size--;
	Product** newProduct = new Product*[size-1];
	for (int i = 0, k = 0; i < size + 1; i++) {
		if (i != index) {
			newProduct[k] = new Product(oldProduct[i]->getName(), oldProduct[i]->getPrice(), oldProduct[i]->getCount());
			k++;
		}
	}
	return newProduct;
}
//Проверка на закончившийся товар
void VerifyProduct(Product** product, int &size)
{
	for (int i = 0; i < size; i++) {
		if (product[i]->getCount() == 0)
			product = DeleteProduct(product, size, i);
	}
}
//Вывод чека
void CheckPrint(Check* total, int size_total) {
	system("cls");
	for (int i = 0; i < size_total; i++) {
		cout << total[i].name << "\t" << total[i].price << "\t" << total[i].count << "\n";
	}
	cout << endl << total_revenues;
}
//Обнуление чека
Check* NulledCheck(Check* total) {
	Check* newTotal = new Check[0];
	return newTotal;
}

int main()
{
	int size = 15;
	Product** product = new Product*[size];
	FillList(product);
	double total_amount = 0;
	bool flag = true;
	bool choice = true;
	int size_total = 0;
	Check* total = new Check[size_total];

	while (flag) {
		int size_total = 0;
		total = NulledCheck(total);
		system("cls");
		PrintList(product, size);
		while (choice) {
			cout << "\n\n";
			CustomerChoice(product, size,total_amount,total,size_total);

			cout << "\nEnd or continue shopping(1 - continue,0 - end)?\n";
			cin >> choice;
			cin.ignore();

			VerifyProduct(product, size);
			system("cls");
			PrintList(product, size);
		}
		CheckPrint(total, size_total);
		Sleep(10000);
	}

}

