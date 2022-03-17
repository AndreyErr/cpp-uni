#include <iostream>
#include <bitset>
#include <cstdlib>
#include <fstream>
#include <string>
#include <chrono>
#include <vector>
#include <cstdio>
#include <stdio.h>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    ofstream mainf;
    string p = "file.txt";
    int num = 10;                   //Сколько char -ов в 1 файле
    unsigned char a[10] = { 0 };    //Сколько char -ов в 1 файле
    mainf.open(p);
    
    //Автоввод
    for (int i = 200; i >= 0; i--) { //9999999
        mainf << i << " ";
    };
    
    //ручной ввод
    /*
    for (int i = 0; i < 5; i++) {
        int x;
        cin >> x;
        mainf << x << endl;
    }*/

    mainf.close();

    auto begin = chrono::high_resolution_clock::now();
    // Старт таймера


    ///////////////////
    int maxf = 0;
    ifstream mainfop;
    mainfop.open(p);
    int ch;
    while (mainfop >> ch) {
        for (int i = 0; i <= 9; i++)
            a[i] = 0;
        cout << "+" << ch;
        //ch = ch - 1000000;
        //cout << "+" << ch;
        int f = ch / (num * 8);
        ifstream filenum0;
        filenum0.open(to_string(f) + string(".txt"));
        if (!filenum0.is_open()) {
            ofstream filenumrr;
            filenumrr.open(to_string(f) + string(".txt"));
            for (int i = 0; i < num; i++) {
                filenumrr << 0 << " ";
            }
            filenumrr.close();
        }
        filenum0.close();
        ifstream filenum;
        filenum.open(to_string(f) + string(".txt"));

        int i = 0;
        unsigned char maska = 1;
        const int n = sizeof(char) * 8;
        int ch1;
        while (filenum >> ch1) {
            a[i] = ch1;
            i++;
        }
        filenum.close();
        ofstream filenumr;
        filenumr.open(to_string(f) + string(".txt"));
        a[(ch - num * 8 * f) / 8] = a[(ch - num * 8 * f) / 8] | (maska << ((ch - 8 * f) % 8));

        for (int j = 0; j < num; j++)
            cout << " | " << bitset<n>(a[j]) << " ";

        for (int i = 0; i < num; i++) {
            filenumr << (int)a[i] << " ";
            cout << (int)a[i] << " (" << i << ") ";
        }
        cout << "|||" << f;
        cout << endl;
        filenumr.close();
        if(f > maxf)
            maxf = f;
    }
    mainfop.close();
    
    ofstream mainffin;
    mainffin.open(p);

    for (int i = 0; i <= maxf; i++) {
        ifstream filenumr;
        filenumr.open(to_string(i) + string(".txt"));

        int ch1 = 0;
        int g = 0;
        while (filenumr >> ch1) {
            unsigned char maska = 1;
            for (int j = 0; j <= 7; j++) {
                if (ch1 != (ch1 & (~(maska)))) {
                    cout << j + 8 * g + i * 8 * num << " ";
                    mainffin << j + 8 * g + i * 8 * num << " ";
                }
                maska = maska << 1;
                cout << "+";
            }
            g++;
        }
        cout << "=";
        filenumr.close();
    }
    mainffin.close();
    for (int i = 0; i <= maxf; i++) {
        string d = to_string(i) + string(".txt");
        cout << d;
        remove(d.c_str());
    }


    // Остановка таймера
    auto end = chrono::steady_clock::now();
    cout << "Размер массива: " << sizeof(char) * num << " байт, или " << sizeof(char) * num / 8 / 1024 << "КБ";
    cout << endl;
    chrono::duration<double, std::milli> elapsed_ms = end - begin;
    cout << "Время: " << elapsed_ms.count() << " ms, или " << elapsed_ms.count() / 1000 << " секунд\n";
    cout << endl;


    cout << "Конец!!!" << endl;
    return 0;
}




#include <iostream>
#include <bitset>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    int num = 100;                   //Сколько char -ов в 1 файле
    unsigned char a[100] = { 0 };    //Сколько char -ов в 1 файле

    ofstream mainf;
    string p = "file.txt";
    mainf.open(p);
    //Автоввод
    for (int i = 1090000; i >= 1000000; i--) { //9999999
        mainf << i << " ";
    };
    //ручной ввод
    /*
    for (int i = 0; i < 5; i++) {
        int x;
        cin >> x;
        mainf << x << endl;
    }*/
    mainf.close();

    // Старт таймера
    auto begin = chrono::high_resolution_clock::now();

    int maxf = 0;
    ifstream mainfop;
    mainfop.open(p);
    int ch;
    //обнуление временного массива
    while (mainfop >> ch) {
        for (int i = 0; i <= 9; i++)
            a[i] = 0;
        ch = ch - 1000000;
        //Создание временных файлов
        int f = ch / (num * 8);
        ifstream filenum0;
        filenum0.open(to_string(f) + string(".txt"));
        if (!filenum0.is_open()) {
            ofstream filenumrr;
            filenumrr.open(to_string(f) + string(".txt"));
            for (int i = 0; i < num; i++) {
                filenumrr << 0 << " ";
            }
            filenumrr.close();
        }
        filenum0.close();
        ifstream filenum;
        filenum.open(to_string(f) + string(".txt"));

        int i = 0;
        unsigned char maska = 1;
        const int n = sizeof(char) * 8;
        int ch1;
        //запись во временный массив
        while (filenum >> ch1) {
            a[i] = ch1;
            i++;
        }
        filenum.close();
        //Запись во временные файлы
        ofstream filenumr;
        filenumr.open(to_string(f) + string(".txt"));
        a[(ch - num * 8 * f) / 8] = a[(ch - num * 8 * f) / 8] | (maska << ((ch - 8 * f) % 8));

        for (int i = 0; i < num; i++) {
            filenumr << (int)a[i] << " ";
        }
        filenumr.close();
        if (f > maxf)
            maxf = f;
    }
    mainfop.close();

    ofstream mainffin;
    mainffin.open("finout.txt");
    //перезапись из временных файлов в конечный
    for (int i = 0; i <= maxf; i++) {
        ifstream filenumr;
        filenumr.open(to_string(i) + string(".txt"));

        int ch1 = 0;
        int g = 0;
        while (filenumr >> ch1) {
            unsigned char maska = 1;
            for (int j = 0; j <= 7; j++) {
                if (ch1 != (ch1 & (~(maska)))) {
                    mainffin << j + 8 * g + i * 8 * num << " ";
                }
                maska = maska << 1;
            }
            g++;
        }
        filenumr.close();
    }
    mainffin.close();

    //Удаление временных файлов
    for (int i = 0; i <= maxf; i++) {
        string d = to_string(i) + string(".txt");
        remove(d.c_str());
    }


    // Остановка таймера
    auto end = chrono::steady_clock::now();
    cout << "Размер массива: " << sizeof(char) * num << " байт, или " << sizeof(char) * num / 1024 << "КБ";
    cout << endl;
    chrono::duration<double, std::milli> elapsed_ms = end - begin;
    cout << "Время: " << elapsed_ms.count() << " ms, или " << elapsed_ms.count() / 1000 << " секунд\n";
    cout << endl;
    cout << "Начальный массив можно посмотрель в файле file.txt, а отсортированный в файле finout.txt\n";
    return 0;
}