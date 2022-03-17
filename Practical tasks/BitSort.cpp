#include <iostream>
#include <bitset>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

int main()
{
	setlocale(LC_ALL, "rus");
	//Заполнение файла числами в обратном порядке
	ofstream mainf;
	mainf.open("mainf.txt");
	for (int i = 9999999; i >= 1000000; i--) {
		mainf << i << " ";
	};
	mainf.close();

	unsigned char maska = 1;
	// Запуск таймера
	auto begin = chrono::high_resolution_clock::now();
	ofstream output;
	ifstream file;
	file.open("mainf.txt");
	output.open("mainfsort.txt");

	//Создание и обнуление вектора
	vector<unsigned char> m;
	for (int i = 0; i < 9000000 / 8; i++) {
		m.push_back(0);
	}
	//Считывание и битовый воод чисел в вектор
	int ch;
	while (file >> ch) {
		ch = ch - 1000000;
		m[ch / 8] = m[ch / 8] | (maska << (ch % 8));
	}

	//Побитовый вывод из вектора в файл
	for (int i = 0; i < 9000000 / 8; i++) {
		maska = 1;
		for (int j = 0; j < 8; j++) {
			if (m[i] != (m[i] & (~(maska)))) {
				output << j + 1000000 + 8 * i << " ";
			}
			maska = maska << 1;
		}
	}

	// Остановка таймера
	auto end = chrono::steady_clock::now();
	cout << "Размер массива: " << m.capacity() << " байт, или " << sizeof(char) * m.capacity() / 1024 << "КБ \n";
	chrono::duration<double, std::milli> elapsed_ms = end - begin;
	cout << "Время: " << elapsed_ms.count() << " ms, или " << elapsed_ms.count() / 1000 << " секунд\n\n";
	cout << "Начальный массив можно посмотрель в файле mainf.txt, а отсортированный в файле mainfsort.txt\n";
	return 0;
}