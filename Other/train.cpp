#include <iostream>
#include <vector>
#include <algorithm>
#include <list>



/*
* 
* Если глобал переменную пометить как static, то её будет видно только в данном cpp файле
* ссылка под капотом - константный указатель, ссылка всего инициирована, не может быть nullptr
* 
* вектор - динам массив О(const/1) - т.к. массив
* лист - двусвязный список О(n) - т.к. нужно пройти по всем элементам
* 
Полиморф
стат - на этапе комппиляции
Пример: 
Перегрузка операторов, шаблоны

динам - на этапе исполнения
Наслед от род класса и переопределение метода

Решение ромбовид наслед - виртуальное наследование или расширение (прим d.C::h (объект.класс через который::поле/метод), но это дублирует h из род класса)

*/

enum FFF { // перечисляемый тип данных
    ON, //0
    OFF //1
};

//защита от копирования и перемещения
class GGG {
    GGG(const GGG&) = delete; // копир
    GGG(GGG&&) noexcept = delete; // перемещь
    GGG& operator=(const GGG&) = delete;
    GGG& operator=(GGG&&) noexcept = delete;

};


class A {
    unsigned int a;
    static int b; // Одинаковая для всех объектов! Иницилизаци должна быть вне класса
    static int count;
public:
    FFF d;
    A() {
        a = 10;
        count++;
    }
    ~A() {
        //std::cout << "End";
    }
    void setA(int a) {
        if (a > -1) this->a = a;
    }
    unsigned int getA() {
        return a;
    }
    void operator == (const A& other) {
        std::cout << "AaA == aAa" << std::endl;
        std::cout << this->getA() << "?=?" << other.a << std::endl;
        std::cout << "AaA == aAa" << std::endl;
    }
    int getCount() {
        return count;
    }

    friend void faf(int* a);// функция может работать с закрытыми полями класса
};

int A::count = 0;

void fff(int i = 5) {
    std::cout << i;
}

void faf(int *a) {
    *a = 1021;
}

void faff(int& a) {
    a = 8899;
}

void fafff() {
    
}

void mass(int arr0[], int &s);

// Шаблон
template<typename T>
void some(T t) {
    std::cout << t << std::endl;
}


class AA {
public:
    virtual void BANG() {
        std::cout << "BANG" << std::endl;
    }
    AA() {
        std::cout << "AA" << std::endl;
    }
    virtual ~AA() {
        std::cout << "~AA" << std::endl;
    }
};

class BB : public AA {
public:
    void BANG() override { // override - контроль за не переопределением virtual функции, что б не был создан новый метод, а переопределён предыдущий (полиморфизм)
        std::cout << "BANG - BANG - BANG" << std::endl;
    }
    BB():AA() { // Выбор конструктора базового класса
        std::cout << "BB" << std::endl;
    }
    ~BB() override {
        std::cout << "~BB" << std::endl;
    }
};



// Чисто вирт класс (хотя бы 1 чисто вирт функция)
class VV {
    virtual void hhh() = 0;
};



int main()
{
    A x;
    x.setA(5);
    std::cout << x.getA() << std::endl;
    fff();
    fff(10);

    std::cout << std::endl << std::endl;
    int a = 5;

    int* px = &a;
    std::cout << a << std::endl << &a << std::endl << px << std::endl << *px << std::endl << &px;

    *px = 2;

    std::cout << std::endl << a;

    int arr[3]{ 1, 2, 3 };

    std::cout << std::endl << arr[2];

    std::cout << std::endl << *(arr + 2);
    //std::cout << std::endl << *(arr + 20);
    std::cout << std::endl << (arr + 2);
    std::cout << std::endl << &arr[2];
    
    faf(&a);
    std::cout << std::endl << a;

    int& aRe = a;
    faff(aRe);
    std::cout << std::endl << a << std::endl << &a << std::endl << aRe << std::endl << &aRe << std::endl;

    char arr2[4]{ 'a', 'b', 'c', '\0'};
    std::cout << std::endl << arr2;
    int* pb = new int;
    *pb = 10;
    std::cout << std::endl << *pb << std::endl << pb;
    delete pb;
    pb = nullptr;
    //std::cout << std::endl << *pb << std::endl << pb;

    int size = 10;
    int* arr3 = new int[size];
    arr3[6] = 10;
    std::cout << std::endl << arr3[6] << std::endl << (arr3 + 6) << std::endl << &arr3[6];
    delete[] arr3;

    int r = 3;
    int c = 3;
    int **arr4 = new int* [r]; // ** хранит указатель на указатель | * означает новый динам массив из ссылок
    for (int i = 0; i < r; ++i)
        arr4[i] = new int[c];

    arr4[2][2] = 5;
    std::cout << std::endl << arr4[2][2];

    for (int i = 0; i < r; ++i)
        delete[] arr4[i];
    delete[] arr4;

    //указатель на функцию
    void (*fPointer)();
    fPointer = fafff;

    std::cout << std::endl;
    std::cout << std::endl;

    int ppp = 10;
    (ppp < 10) ? (std::cout << std::endl << 'abc' << std::endl) : (std::cout << std::endl << 'acb' << std::endl);

    int arr0[]{1, 2, 3, 4};

    std::cout << sizeof(arr0) << std::endl;
    std::cout << arr0[1] << std::endl;
    int s = sizeof(arr0) / sizeof(int);
    mass(arr0, s);
    std::cout << arr0[1] << std::endl;

    size = 5;
    s = 50;
    int* arr10 = new int[size];
    std::cout << arr10[1] << ' ' << s << std::endl;
    mass(arr10, s);
    std::cout << arr10[1] << ' ' << s << std::endl;

    A y;
    y == x;

    std::cout << y.getCount() << std::endl; // Вывод кол-во объектов класса

    BB p;
    p.BANG();
    AA o;
    o.BANG();

    AA* ptrAA = &o;

    //VV jj; // - нельзя, так как VV чисто вируальная - абстрактный класс

    AA* dinamAA = new AA;
    delete dinamAA;

    std::vector<int> sss;
    sss.push_back(2);
    std::cout << sss[0] << ' ' << sss.size() << std::endl;
    std::cout << std::endl << std::endl;

    // enum
    A j;
    j.d = FFF::ON;
    std::cout << j.d << std::endl;

    if(j.d == ON) std::cout << "OOOOOONN" << std::endl;

    std::cout << std::endl << std::endl;

    std::shared_ptr<int> ptr;


    //проблема без диструкторов
    /*
    Дистр A
    Дистр B завис от A
    A* a = new B; - создание нового класса B через род класс A
    delete a; - это вызовет диструктор только класса A, т.к. мы объявляем его, B не удалится - это утечка памяти
    Для этого ставится виртуальный диструктор в род классе
    */

    std::vector<int> vvv{5,4,3,2,1};
    std::sort(vvv.begin(), vvv.end());
    for (int i = 0; i < 5; ++i) {
        std::cout << vvv[i] << std::endl;
    }

    int mass[5]{1, 2, 3, 4, 5};
    for (int i = 0; i < 5; i++) {
        bool flag = false;
        for (int j = 0; j < 4; j++) {
            if (mass[j] > mass[j + 1]) {
                int b = mass[j]; // создали дополнительную переменную
                mass[j] = mass[j + 1]; // меняем местами
                mass[j + 1] = b; // значения элементов
                flag = true;
            }
        }
        if (!flag) break;
    }

    for (int i = 0; i < 5; ++i) {
        std::cout << mass[i] << std::endl;
    }

    //list<int> this_list = { 4, 6, 3, 2 };
}

void mass(int arr0[], int &s) {
    arr0[1] = 10;
    ++s;
}