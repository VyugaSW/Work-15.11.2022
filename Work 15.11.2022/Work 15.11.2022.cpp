
#include <Windows.h>
#include <iostream>
#include "Product.h"

using namespace std;

int total_revenues = 0;

struct Check {
	char* name = new char[125];
	double price;
	int count;
};

void FillList(Product* product);
void PrintList(Product* product, int size);
Check* UpdateCheck(Check* total, int& sizeTotal);
void CheckCopy(Product* product, int index, Check* total, int size_total);
void CustomerChoice(Product* product, int size, double& amount, Check* total, int& size_total);
Product* DeleteProduct(Product* oldProduct, int& size, int index);
void VerifyProduct(Product* product, int &size);
void CheckPrint(Check* total, int size_total);

//Заполнение списка продуктов
void FillList(Product* product) {
	//Массив статичен и вы позволили, значит я имею право так сделать!!!!!!!!!!!!!!!!!!!
	product[0].fillProduct("Potato",1.5,100);
	product[1].fillProduct("Carrot", 2.0, 50);
	product[2].fillProduct("Beans", 3, 20);
	product[3].fillProduct("Water", 1.0, 150);
	product[4].fillProduct("Black bread", 2.5, 70);
	product[5].fillProduct("White bread", 3.0, 65);
	product[6].fillProduct("Beer", 5.0, 25);
	product[7].fillProduct("Wine", 20.0, 15);
	product[8].fillProduct("Banana", 1.2, 50);
	product[9].fillProduct("Cognac", 35.0, 10);
	product[10].fillProduct("Milk 3.2 liters", 4.5, 95);
	product[11].fillProduct("Milk 1 liters", 1.5, 125);
	product[12].fillProduct("Cheese", 5.0, 75);
	product[13].fillProduct("Chocolate 100g", 7.5, 30);
	product[14].fillProduct("Whale tears", 50.0, 5);
}
//Вывод списка товаров
void PrintList(Product* product, int size) {
	system("cls");
	cout <<  setw(17) << "\t|Name|\t\t\t" << "  |Price|\t\t " << " |Count|\n";
	for (int i = 0; i < size; i++) {
		product[i].PrintProduct();
	}
}
//Увеличение размера чека
Check* UpdateCheck(Check* total, int &sizeTotal) {
	sizeTotal++;
	Check* newCheck = new Check[sizeTotal];
	for (int i = 0; i < sizeTotal-1; i++) {
		strcpy_s(newCheck[i].name, 126, total[i].name);
		newCheck[i].count = total[i].count;
		newCheck[i].price = total[i].price;
	}
	//delete[] total;
	return newCheck;
}
//Копирование покупки (одной) в объект структуры Check
void CheckCopy(Product* product, int index, Check* total, int size_total) {
	Check p;
	strcpy_s(p.name, 126, product[index].getName());
	p.count = product[index].getCount();
	p.price = product[index].getPrice();

	strcpy_s(total[size_total - 1].name, 126, p.name);
	total[size_total - 1].count = p.count;
	total[size_total - 1].price = p.price;
}
//Выбор и покупка покупателя
void CustomerChoice(Product* product, int size, double &amount, Check* total, int &size_total) {
	int count;
	char* buff = new char[125];
	cout << "Enter a name of product and it count:\n";
	gets_s(buff, 200);
	cin >> count;
	cin.ignore();
	for (int i = 0; i < size; i++) {
		if (strcmp(buff, product[i].getName()) == 0) {

			if (count > product[i].getCount()) {
				cout << "\n\tWRONG!\n";
				Sleep(1000);
				break;
			}

			total = UpdateCheck(total, size_total); //Добавляем в чек единицу для продукта
			CheckCopy(product, i, total, size_total); //Копируем в чек продукт
			amount += product[i].getPrice()*count; //Сумма единичной покупки
			//Меняем количество товара
			product[i].fillProduct(product[i].getName(),product[i].getPrice(), product[i].getCount() - count);
			break;
		}
	}
}
//Удаление элемента из массива
Product* DeleteProduct(Product* oldProduct, int& size, int index) {
	size--;
	Product* newProduct = new Product[size];
	for (int i = 0, k = 0; i < size + 1; i++) {
		if (i != index) {
			newProduct[k].fillProduct(oldProduct[i].getName(), oldProduct[i].getPrice(), oldProduct[i].getCount());
			k++;
		}
	}
	//delete[] oldProduct;
	return newProduct;
}
//Проверка на закончившийся товар
void VerifyProduct(Product* product, int &size)
{
	for (int i = 0; i < size; i++) {
		if (product[i].getCount() == 0)
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


int main()
{
	int size = 15;
	Product* product = new Product[size];
	FillList(product);
	double total_amount = 0;
	bool flag = true;
	bool choice = true;
	while (flag) {
		int size_total = 0;
		Check* total = new Check[size_total];
		system("cls");
		PrintList(product, size);
		while (choice) {
			cout << "\n\n";
			CustomerChoice(product, size,total_amount,total,size_total);

			cout << "\nEnd or continue(1 - continue,0 - end)?\n";
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

