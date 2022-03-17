#include <iostream>

using namespace std;

struct node // Создаём структуру узла
{
    char sb; // Буква
    node *l, *r; // Дочерние узлы
};

node* T = nullptr; // Главный указатель на дерево

void inp(char sb, node** t) { // Создание узла
    if (*t == nullptr) { // Если узла нет на позиции, создаём его
        (*t) = new node;
        (*t) -> sb = sb;
        (*t) -> l = (*t) -> r = nullptr;
        return;
    }
    if ((int)sb > (int)((*t) -> sb)) { // Если узел есть и ASCII код новой буквы больше буквы в узле
        inp(sb, &(*t)->r); // Идём в правое дерево
    }
    else {
        inp(sb, &(*t)->l); // Иначе идём в левое дерево
    }
}

void out(node* t, int u, int k) { // Вывод дерева методом симметричного обхода наоборот (u - глубина, k - направление ветви)
    if (t == nullptr) return; // Выход, если нет узла
    else {
        out(t->r, ++u, 1); // Идём по правой ветви
        cout << "  ";
        for (int i = 2; i < u; ++i) cout << "      ";
        if (u != 1) {
            if (k == 1) cout << "/";
            if (k == -1) cout << "\\";
            cout << "-----";
        }
        cout << t->sb << "(" << (int)(t->sb) << ")" << endl; // Вывод числа и ASCII кода
        u--;
    }
    out(t->l, ++u, -1); // Идём по левой ветви
}

int findWay(node* t, char b) { // Поиск длинны пути
    int w = 0; // Обнуляем длинну пути
    while (t) { // Пока есть узлы
        if (t->sb != b) { // Если искомая и буква в узле не совпадают
            w++; // Увеличиваем путь
            if ((int)b > (int)(t->sb)) { // Идём в нужную ветвь по правилу (справа числа всегда больше, чем в настоящем узле)
                t = t->r;
            }
            else {
                t = t->l;
            }
        }
        else
            return w; // При удачном поиске возвращаем длинну пути
    }
    return -1; // Возврат при неудачном поиске
}


void arithmeticMean(node* t, int &sum, int &k) { // Поиск суммы и кол-во узлов для среднего арифметического (прямой обход)
    if (t) {
        sum += (int)(t->sb);
        k++;
        arithmeticMean(t->l, sum, k);
        arithmeticMean(t->r, sum, k);
    }
}

void directBypass(node* t) { // Прямой обход (сверху вниз приорететно по левой ветви)
    if (t) {
        cout << t->sb;
        directBypass(t->l);
        directBypass(t->r);
    }
}

void symmetricBypass(node* t) { // Симметрический обход (снизу вверх приорететно по левой ветви)
    if (t) {
        symmetricBypass(t->l);
        cout << t->sb;
        symmetricBypass(t->r);
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Строим дерево из букв!\n";
    int n;
    char s;
    cout << "Введите кол-во узлов в дереве: "; cin >> n;
    for (int i = 0; i < n; ++i) {
        cout << "Введите букву: "; cin >> s;
        inp(s, &T);
    }
    cout << "Построенное дерево!\n";
    out(T, 0, 0);
    system("pause");
    int men = 0;
    while (men != 3) {
        system("cls");
        cout << "Дерево\n";
        out(T, 0, 0);
        cout << "\n\nВыберете действие!";
        cout << "\n1) Обход, среднее ариф. узлов";
        cout << "\n2) Поиск длинны пути";
        cout << "\n3) Выход";
        cout << "\nВведите выбор: "; cin >> men;
        if (men == 1) {
            system("cls");
            cout << "Дерево\n";
            out(T, 0, 0);
            cout << "\n\nПрямой обход: "; directBypass(T);
            cout << "\nСимметричный обход: "; symmetricBypass(T);
            int sum = 0;
            int k = 0;
            arithmeticMean(T, sum, k);
            cout << "\nСреднее ариф: "; cout << (float)sum / (float)k << " (" << sum << "/" << k << ")"; // Поиск ср. арифм.
            cout << endl;
            system("pause");
        }
        if (men == 2) {
            system("cls");
            cout << "Дерево\n";
            out(T, 0, 0);
            char j;
            cout << "Введите букву для поиска длинны пути: "; cin >> j;
            cout << "Длинна пути до буквы " << j << ": ";
            if (findWay(T, j) == -1)
                cout << "буква не найдена!";
            else
                cout << findWay(T, j);
            cout << endl;
            system("pause");
        }
    }
}