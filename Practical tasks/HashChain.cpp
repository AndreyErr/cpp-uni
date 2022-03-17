#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Hash
{
private:
    struct Scet {  
        int code; // Код
        string addr; // Адрес
        string fio; // Фио
        Scet* next; // Указатель на следующую структуру
    };

    Scet* a; // Хеш-массив типа структуры
    int size = 10; // Размер кеша стартовый 
    float index = 3; // Индек рехеширования (кол-во записей / размер массива)(n/m)
    int sizeMss; // Размер массива
    int stepReHash = 0; // Ступень рехеширования (сколько раз произошло рехеширование)
    int Keys = 0; // Кол-во записей

    int HashCode(int key, int step) { // Хеширование
        int vr = pow(10, step); // возведение в степень
        return key % (10 * vr); //вычисление значения хеша
    }


    /*
    
    Почему происходит рехеширование в хешировании цепочкой:

    Если сразу создать хеш-таблицу большого размера, то многие элементы могут не использоваться
    Если создать небольшую таблицу, то длина цепочек будет расти (с увеличением времени поиска)


    */
    void ReHash() { // Рехеширование
        int sizeOld = sizeMss;
        stepReHash++;
        sizeMss = sizeMss * 10; // увеличиваем кол-во записей в 10 раз
        Scet* avr = new Scet[sizeMss]; // Временный хеш массив
        for (int i = 0; i < sizeMss; ++i) {
            avr[i].code = -1; // Ставим статусы -1
            avr[i].next = nullptr;
        }
        swap(a, avr); // Меняем местами старый и временный массивы
        for (int i = 0; i < sizeOld; i++) {
            if (avr[i].code != -1)
            {
                Scet* href = avr[i].next;
                while (href != nullptr)
                {
                    Insert(href->code, href->fio, href->addr);//Вносим данные из временного в новый массив
                    href = href->next;
                }
            }
        }
    }

public:
    Hash() {
        sizeMss = size; // Первоначальный массив
        a = new Scet[sizeMss]; // Создание нового массива
        for (int i = 0; i < sizeMss; i++) {
            a[i].next = nullptr; // Заполнение массива пустыми записями
            a[i].code = -1; // Код ссылки (-1 не ссылается, 1 ссылается)
        }
    }

    void Insert(int code, string fio, string name) // Ввод новых данных
    {
        if ((float)Keys / sizeMss > index) { // Производим рехеш при условии
            //cout << "REHESH";
            ReHash();
        }
        int c = HashCode(code, stepReHash); // Хеширование кода
        if (a[c].next == nullptr and a[c].code == -1) { // Добавляем структуру, если она 1 в цепочке
            Scet* str = new Scet; // Создаём новую структуру
            str->code = code; //Заносим в неё данные
            str->addr = name;
            str->fio = fio;
            str->next = nullptr; //Обнуляем указатель
            a[c].next = str;//Указываем структуру в ячейке массива на новую структуру
            a[c].code = 0;//Указываем, что ячейка ссылается на структуру
        }
        else {// Добавляем структуру, если она не 1 в цепочке

            Scet* href = &a[c];
            Scet* hrefBef = &a[c];
            while (href != nullptr)
            {
                if (href->code == code) // Проверка на существование кода
                {
                    cout << "Запись с кодом " << code << " уже существует!\n";
                    return;
                }
                hrefBef = href;
                href = href->next;
            }
            Scet* str = new Scet;
            str->code = code;
            str->addr = name;
            str->fio = fio;
            str->next = nullptr;// Обнуляем указатель
            hrefBef->next = str;//Указываем предыдущию структуру на новую

        }
        Keys++;
    }

    void PrintAll() { // Вывод хеш-таблицы
        cout << "Хеш-таблица:\n";
        for (int i = 0; i < sizeMss; i++) {
            cout << "Номер хеша: " << i;
            if (a[i].next == nullptr and a[i].code == -1)
                cout << "\tНет записи\n";
            else
            {
                Scet* href = &a[i]; // & - взятие адреса, берём адрес ячейки массива
                int strel = 0;// Для вывода стрелки
                cout << "\t";
                while (href != nullptr) // Пока запись существует
                {
                    if (strel > 0) {
                        if (strel > 1) {
                            cout << "  <-  ";
                        }
                        cout << "Номер: " << href->code << " | Адрес: " << href->fio << " | ФИО: " << href->fio;
                    }
                    href = href->next; // Переход к новой записи
                    strel++;
                }
                cout << "\n";
            }
        }
        cout << "\n";
    }

    void Search(int code) //Поиск по коду
    { 
        int c = HashCode(code, stepReHash); // Хеширование кода
        if (a[c].code != -1) {
            Scet* href = &a[c];
            while (href != nullptr)
            {
                if (href->code == code) {
                    cout << "У кода " << code << " ФИО - " << href->fio << " и адрес - " << href->addr << "\n";
                    return;
                }
                href = href->next;
            }
        }
        cout << "Код " << code << " не найден!\n";
        return;
    }

    void Delete(int code) { // Удаляем запись 
        int c = HashCode(code, stepReHash); // Хеширование кода
        if (a[c].code != -1) {
            Scet* href = &a[c];
            Scet* hrefbef = nullptr;
            while (href != nullptr)
            {
                if (href->code == code) {
                    Scet* hrefnext = href->next;
                    delete href; // Удаляем запись
                    hrefbef->next = hrefnext; // Меняем ссылку предыдущего удалённой структуре на следующей
                    cout << "Код " << code << " удалён!\n";
                    Keys--;
                    if (a[c].next == nullptr) { //Если запись была единственной в цепочке, то ставим статус ячейки массива -1
                        a[c].code = -1;
                    }
                    return;
                }
                hrefbef = href;
                href = href->next;
            }
        }
        cout << "Код " << code << " для удаления не найден!\n";
        return;
    }
};

int main()
{
    setlocale(LC_ALL, "rus");

    Hash a1;
    a1.Insert(1234581, "ФИО1", "ххх,ххх,,qwer");
    a1.Insert(2234581, "ФИО3", "ххх,ххх,,qwer");
    a1.PrintAll();
    a1.Delete(1234581);
    a1.Delete(2234581);
    a1.PrintAll();
    a1.Insert(1234581, "ФИО7", "ххх,ххх,,qwer");
    a1.Insert(2234581, "ФИО9", "ххх,ххх,,qwer");
    a1.Delete(1234581);
    a1.PrintAll();
    a1.Search(2234581);

    /*a1.Insert(1234567, "ФИО1", "ххх,ххх,,хххх");
    a1.Insert(1234577, "ФИО2", "ххх,ххх,,qwer");
    a1.Insert(1234578, "ФИО3", "ххх,ххх,,qwer");
    a1.Insert(1234577, "ФИО4", "ххх,ххх,,qwer");
    a1.Insert(1234567, "ФИО5", "ххх,ххх,,хххх");
    a1.Insert(1234588, "ФИО6", "ххх,ххх,,qwer");
    a1.Insert(1234580, "ФИО7", "ххх,ххх,,qwer");
    a1.Insert(1234581, "ФИО7", "ххх,ххх,,qwer");
    a1.Insert(1234582, "ФИО7", "ххх,ххх,,qwer");
    a1.Insert(1234583, "ФИО7", "ххх,ххх,,qwer");
    a1.Insert(1234584, "ФИО7", "ххх,ххх,,qwer");
    a1.Insert(1234585, "ФИО7", "ххх,ххх,,qwer");
    a1.PrintAll();
    a1.Search(1234567);
    a1.Delete(1234567);
    a1.Insert(1234567, "ФИО1", "ххх,ххх,,хххх");
    a1.Insert(2234567, "ФИО1", "ххх,ххх,,хххх");
    a1.PrintAll();
    a1.Search(1234567);*/


    /*a1.Insert("aaa", "02.12.51");
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
    a1.PrintAll();*/
    return 0;
}