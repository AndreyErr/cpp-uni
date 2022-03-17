#include <iostream>
using namespace std;
bool cycle = false; // Проверка на ацикличность

void fillGraf(int** arr, int s) { // Создание графа
	cout << "Ввод однонаправленных связей\n";
	cout << "Если связь двунаправленная, то введите направления с обоих сторон!\n";
	for (int i = 1; i <= s; i++) {
		cout << "\nВведите точки к которым пойдёт однонаправленная связь от точки " << i << " (0 для конца): ";
		int num = 1;
		while (num > 0 and num <= s) { // Ввод, пока не будет числа за пределами кол-ва точек
			cin >> num;
			arr[i][num] = 1;
		}
	}
}

void printGraf(int** arr, int s) { // Вывод матрицы смежности
	cout << "\nВывод мотрицы связей\n";
	cout << "X ";
	for (int i = 1; i <= s; i++)
		cout << i << " ";
	cout << endl;
	for (int i = 1; i <= s; i++) {
		cout << i << " ";
		for (int j = 1; j <= s; j++)
			cout << arr[i][j] << " ";
		cout << endl;
	}
}

void Connect(int** arr, int* check, int s, int n, int& fins) { // Проверка графа на связанность
	fins++; // Подсчёт узлов
	check[n] = 1; // Вершина посещена
	for (int i = 1; i <= s; i++) { // Идём по соединённым вершинам по направлению
		if (arr[n][i] == 1) { // Если обнаруженно соединение
			if (check[i] == 0) // Если точка не проверена, проверяем её
				Connect(arr, check, s, i, fins);
		}
	}
}

void acycl(int** arr, int* check, int s, int n) { // Проверка графа на ацикличность
	check[n] = 1; // Вершина посещена
	for (int i = 1; i <= s; i++) { // Идём по соединённым вершинам по направлению
		if (arr[n][i] == 1) { // Если обнаруженно соединение
			if (check[i] == 0) // Если точка не проверена, проверяем её
				acycl(arr, check, s, i);
			else if (check[i] == 1) { // Если точка проверена, значит это цикл
				cycle = true;
				return;
			}
		}
	}
	check[n] = 2; // Вершина проверена
}

int main() {
	setlocale(LC_ALL, "RUS");
	int size; // Кол-во вершин
	cout << "Введите кол-во вершин: "; 
	cin >> size;
	int* check = new int [size + 1]; // Массив просмотра точек
	for (int i = 1; i <= size; i++) { // Обнуление массива
		check[i] = 0;
	}
	int** arr = new int* [size+1]; // Двумерный массив, где каждая строка - точка из которой идёт связь, столбец - в которую
	for (int i = 1; i <= size; i++) { // Обнуление двумерного массива
		arr[i] = new int[size+1];
		for (int j = 0; j <= size; j++)
			arr[i][j] = 0;
	}
	fillGraf(arr, size); // Создание графа
	printGraf(arr, size); // Вывод графа
	int fins = 0;
	int contrl = 0;
	for (int k = 1; k <= size; k++) {
		fins = 0;
		for (int i = 1; i <= size; i++) { // Обнуление массива
			check[i] = 0;
		}
		Connect(arr, check, size, k, fins); // Подсчёт кол-ва связанных узлов
		if (fins != size) {
			cout << "Граф не связанный\n";
			contrl = 1;
			break;
		}
	}
	if(contrl != 1)
		cout << "Граф связанный\n";
	
	for (int i = 1; i <= size; i++) { // Обниление массива
		check[i] = 0;
	}
	for (int i = 1; i < size and !cycle; i++) { // Идём по всем точкам (на случай, если граф не связанный)
		if (check[i] == 0)
			acycl(arr, check, size, i);
	}
	if (cycle == false)
		cout << "Граф ацикличный\n";
	else
		cout << "Граф не ацикличный\n";
}