#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
struct Thing
{
	int weight;
	int price;
};
int branchBound(vector <Thing> _spisok, int _maxWeight, int& bestWeight)
{
	int maxPrice = 0;
	int k = 0;//Будем отмечать предмет как выбранный
	bool* used = new bool[_spisok.size()];
	for (int i = 0; i < _spisok.size(); i++)
		used[i] = false;
	//Обход комбинаций. Если в рюкзаке n предметов, то будет 2^n комбинаций
	for (int i = 0; i < pow(2, _spisok.size()); i++)
	{
		int tempWeight = 0;
		int tempPrice = 0;
		int stopPoint = i;
		int j = 0;
		while (stopPoint)
		{
			used[j] = bool(stopPoint % 2);
			stopPoint /= 2;
			if (used[j])
			{
				tempWeight += _spisok[j].weight;
				tempPrice += _spisok[j].price;
				if (tempWeight >= _maxWeight)
					break;
			}
			j++;
		}
		if (tempPrice > maxPrice && tempWeight <= _maxWeight) {
			bestWeight = tempWeight;
			maxPrice = tempPrice;
		}
	}
	return maxPrice;
}
int main()
{
	setlocale(LC_ALL, "rus");
	int maxWeight = 0;
	int bestWeight = 0;
	int count;
	cout << "Введите максимальный вес: ";
	cin >> maxWeight;
	cout << "Введите количество вещей: ";
	cin >> count;
	vector<Thing> spisok(count);
	for (int i = 0; i < count; i++)
	{
		cout << "Введите вес и ценность вещи " << i + 1 << ": ";
		cin >> spisok[i].weight >> spisok[i].price;
	}
	cout << "\nМаксимальная стоимость - " << branchBound(spisok, maxWeight, bestWeight)
		<< endl;
	cout << "Итоговый вес - " << bestWeight << endl;
	return 0;
}