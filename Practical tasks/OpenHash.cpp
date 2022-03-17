#include <iostream>
#include <string>
using namespace std;

class Hash
{
private:
    struct VuzSpec {  //Элемент хеш массива: Специализация вуза: код специальности, название вуза
        string code; //код специальности
        string name; // название вуза
        int state; //состояние записи
    };

    VuzSpec* a; // Хеш-массив
    int size = 10; // Размер кеша стартовый
    int sizeMss; // Размер массива
    int CleanLine; // Чистые существующие значения (не удалённые)
    int AllLine; // Все значения (чистые + удалённые)

    int MainHash(int key) { // Главное хеширование
        return key % size;
    }
    int DoubleHash(int key, int step) { // Двойное хеширование, при колизиях
        return key % size + size * step;
    }

    int CodeDivision(string code) { //берём 3 число кода (xx.xx.XX)
        string s = code;
        string delimiter = ".";//разделитель
        size_t pos = 0;
        int i = 0;
        while ((pos = s.find(delimiter)) != std::string::npos) { //Разделяем на части
            s.erase(0, pos + delimiter.length()); // удаляем первые 2 числа
            i++;
        }
        if (i == 2) {
            return stoi(s); //преобразуем 3 число из string в int
        }
        else {
            cout << "В коде вы ввели что-то не так! Формат кода: XX.XX.XX";
            return 0;
        }
    }

    void ReHash() { // Рехеширование
        AllLine = 0;
        CleanLine = 0;
        int sizeOld = sizeMss;
        sizeMss = sizeMss + size; //добавляем несколько пустых записей
        VuzSpec* avr = new VuzSpec[sizeMss]; //временный хеш массив
        for (int i = 0; i < sizeMss; ++i)
            avr[i].state = 0;
        swap(a, avr); // меняем местами старый и временный массивы
        for (int i = 0; i < sizeOld; ++i) { // Рехешируем
            if (avr[i].state == 1)
                Insert(avr[i].name, avr[i].code);

        }
        delete[] avr; // Удаление старой таблицы
        //cout << "Выполнен resize и rehash!\n";
    }

public:
    Hash() {
        sizeMss = size; //первоначальный массив
        CleanLine = 0;
        AllLine = 0;
        a = new VuzSpec[sizeMss]; //создание нового массива
        for (int i = 0; i < sizeMss; i++)
            a[i].state = 0; // Заполнение массива пустыми записями
    }

    void Insert(string name, string code) //ввод новых данных
    {
        int codeh = 0;
        codeh = CodeDivision(code);
        if (AllLine > 2 * CleanLine) // Перехеш при множестве удалённых записей
            ReHash();
        int с = MainHash(codeh); //главное хеширование кода
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

            с = DoubleHash(codeh, i); //дополнительное хеширование кода
            i++;
        }
        if (free == -1) { // Если нет места, то задаем новые значения
            ReHash(); //Рехеш при отсутствии ячейки
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
        int с = MainHash(CodeDivision(code));
        int i = 1;
        for (с; a[с].state != 0 and с < sizeMss;) { // скачем по записям
            if (a[с].code == code and a[с].state == 1) { // Код найден
                cout << "У кода " << code << " институт - " << a[с].name << "\n";
                return;
            }
            с = DoubleHash(codeh, i);
            i++;
        }
        cout << "Код " << code << "не найден!\n";
    }

    void Delete(string code) { // Удаляем (меняем состояния ячейки на -1 "удалено")      
        int codeh = CodeDivision(code);
        int с = MainHash(CodeDivision(code));
        int i = 1;
        for (с; a[с].state != 0 and i < sizeMss;) {
            if (a[с].code == code and a[с].state == 1) {
                a[с].state = -1;
                CleanLine--;
                return;
            }
            с = DoubleHash(codeh, i);
            i++;
        }
        cout << "Номер " << code << " для удаления не найден!";
    }
};

int main()
{
    setlocale(LC_ALL, "rus");

    Hash a1;
    a1.Insert("aaa", "02.12.51");
    a1.Insert("aaa", "02.13.51");
    a1.Insert("aaa", "02.12.52");
    a1.Insert("aaa", "02.13.52");
    a1.Insert("aaa", "02.12.53");
    a1.Insert("aaa", "02.13.53");
    a1.Insert("aaa", "02.12.54");
    a1.Insert("aaa", "02.13.54");
    a1.Insert("aaa", "02.12.55");
    a1.Insert("aaa", "02.13.55");
    a1.Insert("aaa", "02.12.56");
    a1.Insert("aaa", "02.13.56");
    a1.Insert("aaa", "02.12.57");
    a1.Insert("aaa", "02.13.57");
    a1.Insert("aaa", "02.12.58");
    a1.Insert("aaa", "02.13.58");
    a1.Insert("aaa", "02.12.59");
    a1.Insert("aaa", "02.13.59");
    a1.Insert("aaa", "02.12.60");
    a1.Insert("aaa", "02.13.60");
    a1.Insert("aaa", "02.13.70");
    a1.PrintAll();
    a1.Delete("02.13.60");
    a1.Delete("02.12.59");
    a1.Delete("02.13.59");
    a1.Delete("02.12.58");
    a1.Delete("02.13.58");
    a1.Delete("02.13.57");
    a1.Delete("02.13.56");
    a1.Delete("02.13.55");
    a1.Delete("02.13.54");
    a1.Delete("02.13.53");
    a1.Delete("02.13.52");
    a1.Delete("02.13.51");
    a1.PrintAll();
    a1.Insert("aaa", "02.13.60");
    a1.PrintAll();
    return 0;
}