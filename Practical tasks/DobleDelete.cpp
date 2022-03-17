#include <iostream>
#include <vector>
#include <string>

using namespace std;

void prefix_func(const string& str, vector<int>& z) { // Создаём массив префиксов
    z.resize(str.size()); // Подгоняем под размер нужного слова
    z[0] = 0; // Обнумяем 0 элемент исходя из алгоритма
    for (int i = 1; i < z.size(); i++) {
        int pos = z[i - 1]; // Длинна предыдущего префикс-суффикса (п-ф)
        while (pos > 0 && str[pos] != str[i]) // Нельзя расширить
            pos = z[pos - 1]; // берём длинну меньшего п-ф
        z[i] = pos + (str[pos] == str[i] ? 1 : 0); // Расширяем
    }
}
int kmp(const string& text, const string& str) { // Поиск методом Кнута-Мориса-Пратта (kmp)
    vector<int> z; // Массив префиксов
    prefix_func(str, z); // Создаём таблицу префиксов
    int pos = 0; // Позиция в слове
    for (int i = 0; i < text.size(); i++) { // В строке сравниваемый символ - индекс i
        while (pos > 0 && str[pos] != text[i]) // Очередной символ строки не совпал с символом в образе 
            pos = z[pos - 1]; // Сдвигаем образ
        if (text[i] == str[pos]) pos++; // Еси искомое равняется искомому
        if (pos == str.size())
            return i - pos + 1; // Возврат индекса начала искомого слова
    }
    return -1; // Возврат неудачного поиска
}

void findDobleDel(int start, string& t, const string& s) { // Поиск записей для удаления и их удаление
    int kont = 0; // Значение возврата функции поиска, при невозврате -1
    string sech = t.substr(start); // Ряд без зафиксированных значений, вторая часть новой строки
    t = t.substr(0, start); // Задаём новуму ряду все значения, включая искомое
    while (kont != -1) {
        kont = kmp(sech, s); // Поиск вхождения
        if (kont != -1) {
            // УДАЛЕНИЕ
            int leightw = s.length(); // Длинна искомого слова
            string firsth; // Первая часть новой строки
            if (kont != 0) { // Если слово стоит в начале
                if (sech[kont - 1] == ' ' and (sech[kont + leightw] == ' ' or kont + leightw == sech.length())) { // Если это именно слово, а не часть другого слова
                    firsth = sech.substr(0, kont - 1);
                    sech = sech.substr(kont + leightw);
                }
                else { // Если это часть другого слова переходим через искомое вхождение слово
                       // Пример: ищем слово "мир", слово "перемирие" содержит "мир", поэтому мы "мир" в этом слове перекидываем в "несканируемую" или "зафиксированную" часть
                    firsth = sech.substr(0, kont + leightw);
                    sech = sech.substr(kont + leightw);
                }
            }
            else {
                if (sech[kont + leightw] == ' ') // Если это именно слово, а не часть другого слова
                    sech = sech.substr(kont + leightw + 1);
                else if (kont + leightw == sech.length()) // Если искомое слово единственное
                    sech = sech.substr(kont + leightw);
                else { // Если это часть другого слова
                    firsth = sech.substr(0, kont + leightw);
                    sech = sech.substr(kont + leightw);
                }
            }
            t = t + firsth; // Добавляем "зафиксированную часть в вывод"
        }
    }
    t = t + sech; // Добавляем оставшуюся часть
}

int main()
{
    setlocale(LC_ALL, "rus");
    system("chcp 1251>0"); // Установка языка
    string s;
    cout << "Введите предложение: ";
    string t; 
    getline(cin, t); // Ввод целой строки с пробелами
    int pos = 0; // Настоящая позиция в массиве бекв предложения
    int posstart = 0; // Позиция начала слова для поиска (предыдущие состояние pos)
    int kont = 0; // Контрольное значение окончания предложения
    int len = t.length(); // Длинна предложения
    // Алгоритм считывания делается в 2 этапа т.к. требуется создать динамический массив char
    while (pos <= len) { // Пока позиция в пределах предложения
        int k = 0; // Счётчик букв в слове
        for (int i = pos; i <= len; i++) { // Считываем кол-во букв до нового пробелла или конца предложения
            k++;
            if (t[i] == ' ' or i == len) {
                posstart = pos;
                pos = i + 1;
                if (i >= len)
                    kont = -1;
                break;
            }
        }
        if (kont != -1) { // Преобразуем динамический массив char в string
            char* word = new char[k - 1]; // Создание массива char для слова
            kont = 0;
            for (int i = posstart; i < posstart + k - 1; i++) { // Считываем буквы
                word[kont] = t[i];
                kont++;
            }
            word[kont] = '\0'; // Терминантный 0, символ завершения массива char
            s = word; // Преобразуем массив char в string
            findDobleDel(pos, t, s); // Удаляем дубликаты считанного слова
            len = t.length(); // Изменяем длинну предложения
        }
    }
    cout << "\nПредложение после удаления всех слов-дублёров: " << t << "\n";
    return 0;
}