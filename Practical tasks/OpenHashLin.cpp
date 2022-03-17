#include <iostream>
#include <string>
using namespace std;

class Hash
{
private:
    struct VuzSpec {  // Элемент хеш массива: Специализация вуза: код специальности, название вуза
        string code; // Код специальности
        string name; // Название вуза
        int state; // Состояние записи
    };

    VuzSpec* a; // Хеш-массив
    int size = 10; // Размер кеша стартовый
    int c = 1; // Константа хеширования 
    int sizeMss; // Размер массива
    int CleanLine; // Чистые существующие значения (не удалённые)
    int AllLine; // Все значения (чистые + удалённые)

    int HashCode(int key, int i) { // Хеширование
        return key % 10 + c * i;
    }

    int CodeDivision(string code) { // Берём 3 число кода (xx.xx.XX)
        string s = code;
        string delimiter = ".";// Разделитель
        size_t pos = 0;
        int i = 0;
        while ((pos = s.find(delimiter)) != std::string::npos) { // Разделяем на части
            s.erase(0, pos + delimiter.length()); // Удаляем первые 2 числа
            i++;
        }
        if (i == 2) {
            return stoi(s); // Преобразуем 3 число из string в int
        }
        else {
            cout << "В коде вы ввели что-то не так! Формат кода: XX.XX.XX";
            return 0;
        }
    }

    void ReHashSize(bool action) { // Рехеширование и расширение
        AllLine = 0;
        CleanLine = 0;
        int sizeOld = sizeMss;
        if (action == false)
            sizeMss = sizeMss + size; // Добавляем несколько пустых записей
        else
            sizeMss = sizeMss; // Оставляем всё как есть
        VuzSpec* avr = new VuzSpec[sizeMss]; // Временный хеш массив
        for (int i = 0; i < sizeMss; ++i)
            avr[i].state = 0;
        swap(a, avr); // Меняем местами старый и временный массивы
        for (int i = 0; i < sizeOld; ++i) { // Рехешируем
            if (action == true) {
                if (avr[i].state == 1) {
                    Insert(avr[i].name, avr[i].code);
                }
            }
            else
                a[i] = avr[i];
        }
        delete[] avr; // Удаление старой таблицы
        //cout << "Выполнен resize и rehash!\n";
    }

public:
    Hash() {
        sizeMss = size; // Первоначальный массив
        CleanLine = 0;
        AllLine = 0;
        a = new VuzSpec[sizeMss]; // Создание нового массива
        for (int i = 0; i < sizeMss; i++)
            a[i].state = 0; // Заполнение массива пустыми записями
    }

    void Insert(string name, string code) // Ввод новых данных
    {
        int codeh = 0;
        codeh = CodeDivision(code);
        if (AllLine > 2 * CleanLine) // Перехеш при множестве удалённых записей
            ReHashSize(true); // Рехеш при большом кол-ве удалённых записей
        int с = HashCode(codeh, 0); // Хеширование кода
        int free = -1; // Первая свободная ячейка
        int i = 1; // Ступень хеширования
        for (с; a[с].state == 0 or a[с].state == -1 or a[с].state == 1;) {
            if (a[с].code == code and a[с].state == 1) { // Ячейка с этим номером уже существует
                cout << "Запись с кодом " << code << " уже существует!\n";
                return;
            }
            if (a[с].state == -1 or a[с].state == 0) { // Найдена первая свободная ячейка
                a[с].code = code;
                a[с].name = name;
                a[с].state = 1;
                free = 1;
                break;
            }

            с = HashCode(codeh, i); // Место занято
            i++;
        }
        if (free == -1) { // Если нет места, то задаем новые значения
            ReHashSize(false); // Расширение при отсутствии свободных ячейки
            a[с].code = code;
            a[с].name = name;
            a[с].state = 1;
        }
        CleanLine++;
        AllLine++;
    }

    void PrintAll() { // Вывод хеш-таблицы
        cout << "Хеш-таблица:\n";
        for (int i = 0; i < sizeMss; i++) {
            cout << "Номер хеша: " << i;
            if (a[i].state == 0 or a[i].state == -1)
                cout << "\tНет записи\n";
            else
                cout << "\tНомер: " << a[i].code << "\tИнститут: " << a[i].name << "\n";
        }
        cout << "\n";
    }

    void Search(string code) { // Вывод института по коду
        int codeh = CodeDivision(code);
        int с = HashCode(codeh, 0);
        int i = 1;
        for (с; a[с].state != 0 and с < sizeMss;) { // Скачем по записям
            if (a[с].code == code and a[с].state == 1) { // Код найден
                cout << "У кода " << code << " институт - " << a[с].name << "\n";
                return;
            }
            с = HashCode(codeh, i); // Место занято
            i++;
        }
        cout << "Код " << code << " не найден!\n";
    }

    void Delete(string code) { // Удаляем (меняем состояния ячейки на -1 "удалено")      
        int codeh = CodeDivision(code);
        int с = HashCode(codeh, 0);
        int i = 1;
        for (с; a[с].state != 0 and i < sizeMss;) {
            if (a[с].code == code and a[с].state == 1) {
                a[с].state = -1;
                CleanLine--;
                return;
            }
            с = HashCode(codeh, i); // Место занято
            i++;
        }
        cout << "Номер " << code << " для удаления не найден!";
    }
};

int main()
{
    setlocale(LC_ALL, "rus");

    Hash a1;
    int act = -1;
    while (act != 0) {
        cout << "\n";
        cout << "Выберете действие:\n";
        cout << "1 - Вставить запись\n";
        cout << "2 - Найти запись\n";
        cout << "3 - Удалить запись\n";
        cout << "4 - Вывести всё\n";
        cout << "0 - Выйти\n";
        cout << "Введите действие: \n";
        cin >> act;
        if (act == 1) {
            system("cls");
            cout << "Введите код: \n";
            string code;
            cin >> code;
            cout << "Введите вуз: \n";
            string name;
            cin >> name;
            a1.Insert(name, code);
        }
        if (act == 2) {
            system("cls");
            a1.PrintAll();
            cout << "Введите код: \n";
            string code;
            cin >> code;
            a1.Search(code);
        }
        if (act == 3) {
            system("cls");
            a1.PrintAll();
            cout << "Введите код: \n";
            string code;
            cin >> code;
            a1.Delete(code);
        }
        if (act == 4) {
            system("cls");
            a1.PrintAll();
        }

    }
    return 0;
}