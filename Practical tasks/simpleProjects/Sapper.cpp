#include <iostream>
#include <Windows.h>
#include <ctime>
using namespace std;


///------------------------///
///---ОСНОВНЫЕ НАСТРОЙКИ---///
///------------------------///
int const N = 9;//размер игрового поля (min 6 | max 30)
int debug = 0;//режим тестера (0 - выкл | 1 -вкл) (допилить в версии 1, искл в версии 2)//////////////////////////////////////////////////////////////
int gamecontroll = 1;//изначальный контроль (0 - ввод | 1 - клавиатура)
int m = 10;//кол-во мин по формуле(m <= N * N - 16 or m >= 1)
///------------------------///
///------------------------///
///------------------------///



int first[N][N];
int open[N][N];
int openc[N][N];
bool KEY[256];
void GetKEY()
{
    int i = 0;
    while (i < 256)
    {
        if (GetAsyncKeyState(i)) KEY[i] = 1; else KEY[i] = 0;
        i++;
    }
}
void firstopen(int pstr, int pstl, int first[][N], int N) {
    first[pstr + 1][pstl + 1] = 10;
    first[pstr + 1][pstl] = 10;
    first[pstr + 1][pstl - 1] = 10;
    first[pstr][pstl + 1] = 10;
    first[pstr][pstl - 1] = 10;
    first[pstr - 1][pstl + 1] = 10;
    first[pstr - 1][pstl] = 10;
    first[pstr - 1][pstl - 1] = 10;
    first[pstr][pstl] = 10;
}
void openz(int r, int l, int first[][N], int open[][N], int N) {

    if (r != N - 1 and l != N - 1) { open[r + 1][l + 1] = 1; }
    if (r != N - 1) { open[r + 1][l] = 1; }
    if (r != N - 1 and l != 0) { open[r + 1][l - 1] = 1; }
    if (l != N - 1) { open[r][l + 1] = 1; }
    if (l != 0) { open[r][l - 1] = 1; }
    if (r != 0 and l != N - 1) { open[r - 1][l + 1] = 1; }
    if (r != 0) { open[r - 1][l] = 1; }
    if (r != 0 and l != 0) { open[r - 1][l - 1] = 1; }
}
void opennumber(int r, int l, int first[][N], int open[][N], int openc[][N], int N) {
    int vrr, vrl, on = 0;
    for (int i = 1; i < 9; i++) {
        if (i == 1 and r != N - 1 and l != N - 1 and open[r + 1][l + 1] == 0) { vrr = r + 1; vrl = l + 1; on = 1; }
        if (i == 2 and r != N - 1 and open[r + 1][l] == 0) { vrr = r + 1; vrl = l; on = 1; }
        if (i == 3 and r != N - 1 and l != 0 and open[r + 1][l - 1] == 0) { vrr = r + 1; vrl = l - 1; on = 1; }
        if (i == 4 and l != N - 1 and open[r][l + 1] == 0) { vrr = r; vrl = l + 1; on = 1; }
        if (i == 5 and l != 0 and open[r][l - 1] == 0) { vrr = r; vrl = l - 1; on = 1; }
        if (i == 6 and r != 0 and l != N - 1 and open[r - 1][l + 1] == 0) { vrr = r - 1; vrl = l + 1; on = 1; }
        if (i == 7 and r != 0 and open[r - 1][l] == 0) { vrr = r - 1; vrl = l; on = 1; }
        if (i == 8 and r != 0 and l != 0 and open[r - 1][l - 1] == 0) { vrr = r - 1; vrl = l - 1; on = 1; }
        if (on == 1) {
            open[vrr][l + 1] = 1;
            if (first[vrr][l + 1] == 9) {
                open[vrr][l + 1] = 4;
            }
            if (first[vrr][l + 1] == 0) {
                int k = 0;
                int kkk = 0;
                openz(vrr, l + 1, first, open, N);
                while (k < (N - 1) * (N - 1)) {
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < N; j++) {
                            if (open[i][j] == 1 and openc[i][j] == 0 and first[i][j] == 0) {
                                openc[i][j] = 1;
                                openz(i, j, first, open, N);
                                kkk = 1;
                            }
                            else {
                                k++;
                            }
                        }
                    }
                    if (kkk == 1) {
                        k = 0;
                        kkk = 0;
                    }
                }
            }
        }
        on = 0;
    }
}
int endgame(int debug) {//////////////////////////////////////////////////////////////
    if (debug == 0) {//////////////////////////////////////////////////////////////
        system("cls");
    }
    cout << "|---------------------------------|\n";
    cout << "-_- -_- -_- -_- -_- -_- -_- -_- -_-\n";
    cout << "|---------------------------------|\n";
    cout << "|--------------Пока!--------------|\n";
    cout << "|---------------------------------|\n";
    return 0;
}
void showmap(int stat, int debug, int gamecontroll, int pstr, int pstl, int first[][N], int open[][N], int openc[][N], int N) {//////////////////////////////////////////////////////////////
    cout << "  | ";
    for (int i = 0; i < N; i++) {
        if (i < 10) {
            cout << i << " ";
        }
        else {
            cout << i << "";
        }
    }
    cout << "| \n";
    cout << "  | ";
    for (int i = 0; i < N; i++) {
        cout << "--";
    }
    cout << "| \n";
    for (int i = 0; i < N; i++) {
        if (i < 10) {
            cout << i << " | ";
        }
        else {
            cout << i << "| ";
        }
        for (int j = 0; j < N; j++) {
            if (stat != 2) {
                if (i == pstr and j == pstl) {
                    if (gamecontroll == 1) {
                        cout << "+ ";
                    }
                    else {
                        if (stat != 1) {
                            if (open[i][j] == 3) {
                                cout << "b ";//бомба стоит
                            }
                            else {
                                if (first[i][j] == 0 and open[i][j] == 1) {
                                    if (debug == 1) {//////////////////////////////////////////////////////////////
                                        cout << "0 ";//пустота
                                    }
                                    else {
                                        cout << "  ";
                                    }
                                }
                                else {
                                    if (first[i][j] != 0 and first[i][j] != 9 and open[i][j] == 1) {
                                        cout << first[i][j] << " ";//показываем число
                                    }
                                    else {
                                        cout << ". ";//показываем закрытую клетку
                                    }
                                }
                            }
                        }
                        else {
                            cout << ". ";
                        }
                    }
                }
                else {
                    if (stat != 1) {
                        if (open[i][j] == 3) {
                            cout << "b ";
                        }
                        else {
                            if (first[i][j] == 9) {//дебаг
                                if (debug == 1) {//////////////////////////////////////////////////////////////
                                    cout << "X ";
                                }
                                else {
                                    cout << ". ";
                                }
                            }
                            else {
                                if (open[i][j] != 1) {
                                    cout << ". ";
                                }
                                else {
                                    if (first[i][j] == 0) {
                                        if (debug == 1) {//////////////////////////////////////////////////////////////
                                            cout << "0 ";
                                        }
                                        else {
                                            cout << "  ";
                                        }
                                    }
                                    else {
                                        cout << first[i][j] << " ";
                                    }
                                }
                            }
                        }
                    }
                    else {
                        cout << ". ";
                    }
                }
            }
            else {
                if (open[i][j] == 3) {
                    if (first[i][j] == 9) {
                        cout << "B ";
                    }
                    else {
                        cout << "b ";
                    }
                }
                else {
                    if (first[i][j] == 9) {
                        cout << "X ";
                    }
                    else {
                        if (open[i][j] != 1) {
                            cout << ". ";
                        }
                        else {
                            if (first[i][j] == 0) {
                                if (debug == 1) {//////////////////////////////////////////////////////////////
                                    cout << "0 ";
                                }
                                else {
                                    cout << "  ";
                                }
                            }
                            else {
                                cout << first[i][j] << " ";
                            }
                        }
                    }
                }
            }
        }
        cout << "|\n";
    }
    cout << "  | ";
    for (int i = 0; i < N; i++) {
        cout << "--";
    }
    cout << "| \n";
}
int main()
{
    setlocale(LC_ALL, "rus");
    if ((N < 6 or N > 30) or (m > N * N - 16 or m < 1) or (debug > 1 or debug < 0) or (gamecontroll > 1 or gamecontroll < 0)) {//////////////////////////////////////////////////////////////
        cout << "   *   *  * * * *  * * *  |      *\n";
        cout << "    * *   *     *  *      |  *  * \n";
        cout << "     *    *     *  *      |     * \n";
        cout << "    *     *     *  *      |  *  * \n";
        cout << "   *      *     *  * * *  |      *\n";
        cout << "----------------------------------\n";
        if (N < 6 or N > 30) {
            cout << "Размер поля должен быть больше 6 * 6 и меньше 30 * 30!\n";
            cout << "Пожалуйста, имените размер поля в настройках файла!\n";
        }
        else {
            if (debug > 1 or debug < 0) {//////////////////////////////////////////////////////////////
                cout << "Дебаг функция должна иметь только значения 0 или 1!\n";
                cout << "Пожалуйста, имените значение функции дебаг в настройках файла!\n";
            }
            else {
                if (gamecontroll > 1 or gamecontroll < 0) {
                    cout << "Функция контроля управления должна иметь только значения 0 или 1!\n";
                    cout << "Пожалуйста, имените значение функции контроля управления в настройках файла!\n";
                }
                else {
                    cout << "Кол-во мин слишком большое или отрицательное или равное 0\n";
                    cout << "Пожалуйста, имените кол-во мин в настройках файла по формуле(m <= N * N - 16 or m >= 1)!\n";
                }
            }
        }
        cout << "----------------------------------\n";
        return 0;
    }
    //стартовый экран

    int start = 0;
    int session = 1;
    int menu = 0;
    while (session == 1) {
        while (start != 1) {
            if (menu == 0) {
                while (menu == 0) {
                    if (gamecontroll == 1) {
                        GetKEY();
                    }
                    system("cls");
                    cout << "|||||ДОБРО ПОЖАЛОВАТЬ В САПЁР|||||\n";
                    cout << "|--------версия 1.0 DEBUG--------|\n";
                    cout << "|--------------------------------|\n";
                    cout << "|////////////////////////////////|\n";
                    cout << "|--------------------------------|\n";
                    cout << "Генерируемый мир: " << N << " x " << N << " с числом мин = " << m << "!\n";
                    cout << "----------------------------------\n";
                    if (gamecontroll == 1) {
                        cout << "Для изменения управления и не только в настройках нажмите s\n";
                        cout << "Для информации об управлении, правилах и не только введите i\n";
                        cout << "Если вы хотите изменить кол-во миннажмите m\n";
                        //cout << "Для входа в таблицу очков нажмите r\n";
                        cout << "Если вы готовы начать, нажмите пробел\n";
                        cout << "Если вы хотите выйти, нажмите Ecs\n";
                        if (KEY[27]) //нажат Esc
                        {
                            menu = -10;
                        }
                        if (KEY[83]) //нажат s
                        {
                            menu = 1;
                        }
                        if (KEY[73]) //нажат i
                        {
                            menu = 2;
                        }
                        if (KEY[77]) //нажат m
                        {
                            menu = 3;
                        }
                        if (KEY[82]) //нажат r
                        {
                            menu = 4;
                        }
                        if (KEY[32]) //нажат пробел
                        {
                            start = 1;
                            menu = -9999;
                        }
                        Sleep(1000);
                    }
                    else {
                        cout << "Для изменения управления и не только в настройках введите 1\n";
                        cout << "Для информации об управлении и не только введите 2\n";
                        cout << "Если вы хотите изменить кол-во мин, введите 3\n";
                        cout << "Если вы готовы начать, введите 10\n";
                        cout << "Если вы хотите выйти, введите 0\n";
                        cout << "Выбор: ";
                        cin >> menu;
                        if (menu == 10) {
                            start = 1;
                        }
                        if (menu == 0) {
                            menu = -10;
                        }
                    }
                }
            }
            if (menu == 1) {
                while (menu != 0) {
                    system("cls");
                    cout << "|-----------Настройки!-----------|\n";
                    cout << "----------------------------------\n";
                    if (gamecontroll == 1) {
                        GetKEY();
                        cout << "У вас стоит управление клавиатурой, для изменения на управление вводом нажмите k\n";
                        cout << "Для возврата на главный экран введите Esc\n";
                        if (KEY[27]) //нажат esc
                        {
                            menu = 0;
                        }
                        if (KEY[75]) //нажат k
                        {
                            if (gamecontroll == 1) {
                                gamecontroll = 0;
                            }
                            else {
                                gamecontroll = 1;
                            }
                            menu = 0;
                            system("cls");
                            cout << "Настройка изменена, сейчас вы будите переброшены на главный экран";
                            Sleep(2000);
                        }
                        Sleep(1000);
                    }
                    else {
                        cout << "У вас стоит управление вводом, для изменения на управление клавиатурой введите 1\n";
                        if (debug == 1) {//////////////////////////////////////////////////////////////
                            cout << "Для деактивации дебаг функций введите 42\n";
                        }
                        else {
                            cout << "Для активации дебаг функций введите 42\n";
                        }
                        cout << "Для возврата на главный экран введите 0\n";
                        cout << "Выбор: ";
                        cin >> menu;
                        if (menu == 1) {
                            if (gamecontroll == 1) {
                                gamecontroll = 0;
                            }
                            else {
                                gamecontroll = 1;
                            }
                            menu = 0;
                            system("cls");
                            cout << "Настройка изменена, сейчас вы будите переброшены на главный экран";
                            Sleep(2000);
                        }
                        if (menu == 42) {
                            if (debug == 1) {//////////////////////////////////////////////////////////////
                                debug = 0;//////////////////////////////////////////////////////////////
                            }
                            else {
                                debug = 1;//////////////////////////////////////////////////////////////
                            }
                            menu = 1;
                        }
                    }
                }

            }
            if (menu == 2) {
                while (menu != 0) {
                    system("cls");
                    cout << "|----------Управление и правила----------|\n";
                    cout << "------------------------------------------\n";
                    cout << "------------------ВНИМАНИЕ----------------\n";
                    cout << "- Если у вас наблюдается мерцание экрана, то советуем использовать управление вводом\n";
                    cout << "- В игре есть вероятность получить нерешаемые задачи. Эта вероятность зависит от\n";
                    cout << "  размера поля и кол-во бомб на нём. Выбирайте эти параметры с умом!\n";
                    cout << "- Очки рассчитываются по формуле: длинна поля * высоту поля * кол-во найденных бомб\n";
                    cout << "------------------------------------------\n";
                    cout << "------------------Правила-----------------\n";
                    cout << "- Цель игры заключается в разминировании поля игроком. Для этого игроку на поле пишутся числа: сколько вокруг этой точки бомб\n";
                    cout << "- Вы можете помечать бомбы, если вы пометите все бомбы, а остальные клетки откроете, то вы победитель!\n";
                    cout << "- Если вы нажмёте на пустую клетку, то откроются все пустые и граничащие с ними клетки!\n";
                    cout << "- Игра всегда начинается с пустой клетки!\n";
                    cout << "- Если вы отметили рядом с клеткой указанное кол-во бомб, то можете нажать на неё, для открытия оставшихся вокруг неё.\n";
                    cout << "  Если вы ошиблись в постановке бомб, то откроется бомба и вы проиграли!\n";
                    cout << "- Если вы нажмёте на закрытую клетку, а там окажется бомба, то вы проиграли.\n";
                    cout << "------------------------------------------\n";
                    cout << "----------------Обозначения---------------\n";
                    cout << "(  ) - пустая клетка\n";
                    cout << "(1 ) - клетка с обозначением кол-во бомб вокруг неё\n";
                    cout << "(. ) - закрытая клетка\n";
                    cout << "(b ) - помечаная бомбой клетка\n";
                    cout << "(+ ) - положение курсора (при управлении клавиатурой)\n";
                    cout << "------------------------------------------\n";
                    cout << "----------------Управление----------------\n";
                    cout << "Управление вводом: следуйте инструкциям на экране\n";
                    cout << "Управление клавиатурой в игре:\n";
                    cout << "кнопки w, a, s, d для управлением \n";
                    cout << "Esc - выход\n";
                    cout << "b - поставить/убрать бомбу\n";
                    cout << "------------------------------------------\n";
                    cout << "Для возврата на главный экран введите 0\n";
                    cout << "Введите 0: ";
                    cin >> menu;
                }
            }
            if (menu == 3) {
                m = -1;
                while (m > N * N - 16 or m < 1) {
                    system("cls");
                    cout << "|-----------Изменение числа мин-----------|\n";
                    cout << "-------------------------------------------\n";
                    cout << "Введите новое число мин, меньшее, чем " << N * N - 16 << ": ";
                    cin >> m;
                    if (m > N * N - 16 or m < 1) {
                        cout << "Настройка не изменена: неверное значение мин\n";
                    }
                    else {
                        cout << "Настройка изменена, сейчас вы будите переброшены на главный экран\n";
                        menu = 0;
                    }
                    Sleep(2000);
                }
            }
            if (menu == 4) {
                system("cls");
                cout << "|-----------Таблица очков-----------|\n";
            }
            if (menu == -10) {
                endgame(debug);//////////////////////////////////////////////////////////////
                return 0;
            }
            if (menu != -10 and menu != 0 and menu != 1 and menu != 2 and menu != 3 and menu != 4 and menu != 10 and menu != -9999) {
                system("cls");
                menu = 0;
                cout << "Вы ввели что-то странное, сейчас вы будите переброшены на главный экран";
                Sleep(2000);
            }
        }


        //создание мира
        system("cls");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                first[j][i] = 0;
                open[i][j] = 0;
                openc[i][j] = 0;
            }
        }
        int pstr = 0;
        int pstl = 0;
        int n = 0;
        //показываем экран, для выбора стартовай точки
        while (n != 1) {
            if (gamecontroll == 1) {
                GetKEY();
            }
            system("cls");
            showmap(1, debug, gamecontroll, pstr, pstl, first, open, openc, N);//////////////////////////////////////////////////////////////
            if (debug == 1) { cout << "pstr = " << pstr << " | pstl = " << pstl << "\n"; }//////////////////////////////////////////////////////////////
            if (gamecontroll == 1) {
                if (KEY[87]) //нажат ↑
                {
                    if (pstr != 0) {
                        pstr = pstr - 1;
                    }
                }
                if (KEY[83]) //нажат ↓
                {
                    if (pstr != N - 1) {
                        pstr = pstr + 1;
                    }
                }
                if (KEY[65]) //нажат ←
                {
                    if (pstl != 0) {
                        pstl = pstl - 1;
                    }
                }
                if (KEY[68]) //нажат →
                {
                    if (pstl != N - 1) {
                        pstl = pstl + 1;
                    }
                }
                if (KEY[32]) //нажат пробел
                {
                    firstopen(pstr, pstl, first, N);
                    n = 1;
                }
                if (KEY[27]) //нажат esc
                {
                    endgame(debug);//////////////////////////////////////////////////////////////
                    return 0;
                    n = 1;
                }
                Sleep(200);
            }
            else {
                pstl = -1;
                pstr = -1;
                while (pstl < 0 or pstl > N - 1 or pstr < 0 or pstr > N - 1) {
                    cout << "Введите координату для открытия через пробел (x y): ";
                    cin >> pstl >> pstr;
                }
                firstopen(pstr, pstl, first, N);
                n = 1;
            }
        }


        int x;
        int y;
        time_t now = time(0);
        system("cls");
        int kk = 0;
        //генерируем бомбы
        for (int i = 1; i <= m; i++) {
            x = (rand() % N + now % N) / 2;
            y = (rand() % N + now % N) / 2;
            //x = rand() % N;
            //y = rand() % N;
            while (kk != 1) {
                if (first[x][y] != 9 and first[x][y] != 10) {
                    first[x][y] = 9;
                    kk = 1;
                }
                else {
                    x = rand() % N;
                    y = rand() % N;
                }
            }
            kk = 0;
        }


        //расстановка цифр
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (first[i][j] == 10) {
                    first[i][j] = 0;
                }
                if (first[i][j] == 0) {
                    if (i == 0) {
                        if (j == 0) {
                            if (first[0][0 + 1] == 9) { first[0][0]++; }
                            if (first[0 + 1][0 + 1] == 9) { first[0][0]++; }
                            if (first[0 + 1][0] == 9) { first[0][0]++; }
                        }
                        if (j == N - 1) {
                            if (first[0][N - 1 - 1] == 9) { first[0][N - 1]++; }
                            if (first[0 + 1][N - 1 - 1] == 9) { first[0][N - 1]++; }
                            if (first[0 + 1][N - 1] == 9) { first[0][N - 1]++; }
                        }
                        if (j != N - 1 and j != 0) {
                            if (first[0][j - 1] == 9) { first[0][j]++; }
                            if (first[0 + 1][j - 1] == 9) { first[0][j]++; }
                            if (first[0 + 1][j] == 9) { first[0][j]++; }
                            if (first[0 + 1][j + 1] == 9) { first[0][j]++; }
                            if (first[0][j + 1] == 9) { first[0][j]++; }
                        }
                    }
                    else {
                        if (i == N - 1) {
                            if (j == 0) {
                                if (first[N - 1][0 + 1] == 9) { first[N - 1][0]++; }
                                if (first[N - 1 - 1][0] == 9) { first[N - 1][0]++; }
                                if (first[N - 1 - 1][0 + 1] == 9) { first[N - 1][0]++; }
                            }
                            if (j == N - 1) {
                                if (first[N - 1][N - 1 - 1] == 9) { first[N - 1][N - 1]++; }
                                if (first[N - 1 - 1][N - 1] == 9) { first[N - 1][N - 1]++; }
                                if (first[N - 1 - 1][N - 1 - 1] == 9) { first[N - 1][N - 1]++; }
                            }
                            if (j != N - 1 and j != 0) {
                                if (first[N - 1][j + 1] == 9) { first[N - 1][j]++; }
                                if (first[N - 1][j - 1] == 9) { first[N - 1][j]++; }
                                if (first[N - 1 - 1][j + 1] == 9) { first[N - 1][j]++; }
                                if (first[N - 1 - 1][j] == 9) { first[N - 1][j]++; }
                                if (first[N - 1 - 1][j - 1] == 9) { first[N - 1][j]++; }
                            }
                        }
                        else {

                            if (j == 0) {
                                if (first[i - 1][j + 1] == 9) { first[i][j]++; }
                                if (first[i - 1][j] == 9) { first[i][j]++; }
                                if (first[i][j + 1] == 9) { first[i][j]++; }
                                if (first[i + 1][j] == 9) { first[i][j]++; }
                                if (first[i + 1][j + 1] == 9) { first[i][j]++; }
                            }
                            if (j == N - 1) {
                                if (first[i - 1][j - 1] == 9) { first[i][j]++; }
                                if (first[i - 1][j] == 9) { first[i][j]++; }
                                if (first[i][j - 1] == 9) { first[i][j]++; }
                                if (first[i + 1][j] == 9) { first[i][j]++; }
                                if (first[i + 1][j - 1] == 9) { first[i][j]++; }
                            }
                            if (j != N - 1 and j != 0) {
                                if (first[i + 1][j + 1] == 9) { first[i][j]++; }
                                if (first[i + 1][j] == 9) { first[i][j]++; }
                                if (first[i + 1][j - 1] == 9) { first[i][j]++; }
                                if (first[i][j + 1] == 9) { first[i][j]++; }
                                if (first[i][j - 1] == 9) { first[i][j]++; }
                                if (first[i - 1][j + 1] == 9) { first[i][j]++; }
                                if (first[i - 1][j] == 9) { first[i][j]++; }
                                if (first[i - 1][j - 1] == 9) { first[i][j]++; }
                            }

                        }
                    }
                }
            }
        }


        //открытие всех нулевых точек и первыых после нулевых, рядом со стартовай
        open[pstr][pstl] = 1;
        openc[pstr][pstl] = 1;
        openz(pstr, pstl, first, open, N);
        int k = 0;
        int kkk = 0;
        while (k < (N - 1) * (N - 1)) {
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (open[i][j] == 1 and openc[i][j] == 0 and first[i][j] == 0) {
                        openc[i][j] = 1;
                        openz(i, j, first, open, N);
                        kkk = 1;
                    }
                    else {
                        k++;
                    }
                }
            }
            if (kkk == 1) {
                k = 0;
                kkk = 0;
            }
        }


        //ТЕСТИРОВАТЬ И ДЕБАЖИТЬ
        //ИГРА / показ карты открытых значений
        string fincontroll = "";//дебаг
        int end = 0;
        int bombput = 0;
        int explore = 0;
        int exp = 0;
        n = -1;
        while (end != 1 and explore != 1) {
            if (gamecontroll == 1) {
                GetKEY();
            }
            system("cls");
            showmap(0, debug, gamecontroll, pstr, pstl, first, open, openc, N);//////////////////////////////////////////////////////////////
            if (debug == 1) { cout << "pstr = " << pstr << " | pstl = " << pstl << " | bombput = " << bombput << " из " << m << " | exp = " << exp << "\n"; }//////////////////////////////////////////////////////////////
            cout << "Поставлено " << bombput << " бомб из " << m << "!\n";
            if (gamecontroll != 1) {
                n = 0;
                cout << "Действия\n";
                cout << "0 0 0: выйти\n";
                cout << "1 x y: пометить бомбу\n";
                cout << "2 x y: открыть клетку\n";
                cout << "Введите действие и координату (действие x y): ";
                cin >> n >> pstl >> pstr;
            }
            if (gamecontroll == 1) {
                // управление на карте
                if (KEY[87]) //нажат ↑
                {
                    if (pstr != 0) {
                        pstr = pstr - 1;
                    }
                }
                if (KEY[83]) //нажат ↓
                {
                    if (pstr != N - 1) {
                        pstr = pstr + 1;
                    }
                }
                if (KEY[65]) //нажат ←
                {
                    if (pstl != 0) {
                        pstl = pstl - 1;
                    }
                }
                if (KEY[68]) //нажат →
                {
                    if (pstl != N - 1) {
                        pstl = pstl + 1;
                    }
                }
            }
            if ((gamecontroll == 1 and KEY[32]) or (gamecontroll == 0 and n == 2)) //нажат пробел
            {
                if (open[pstr][pstl] == 0 and first[pstr][pstl] == 0) {
                    k = 0;
                    kkk = 0;
                    openz(pstr, pstl, first, open, N);
                    while (k < (N - 1) * (N - 1)) {
                        for (int i = 0; i < N; i++) {
                            for (int j = 0; j < N; j++) {
                                if (open[i][j] == 1 and openc[i][j] == 0 and first[i][j] == 0) {
                                    openc[i][j] = 1;
                                    openz(i, j, first, open, N);
                                    kkk = 1;
                                }
                                else {
                                    k++;
                                }
                            }
                        }
                        if (kkk == 1) {
                            k = 0;
                            kkk = 0;
                        }
                    }
                }
                if (open[pstr][pstl] == 1) {
                    if (first[pstr][pstl] == 1 or first[pstr][pstl] == 2 or first[pstr][pstl] == 3 or first[pstr][pstl] == 4 or first[pstr][pstl] == 5 or first[pstr][pstl] == 6 or first[pstr][pstl] == 7 or first[pstr][pstl] == 8) {
                        int k = 0;
                        if (pstr != N - 1 and pstl != N - 1 and open[pstr + 1][pstl + 1] == 3) { k++; }
                        if (pstr != N - 1 and open[pstr + 1][pstl] == 3) { k++; }
                        if (pstr != N - 1 and pstl != 0 and open[pstr + 1][pstl - 1] == 3) { k++; }
                        if (pstr != N - 1 and open[pstr][pstl + 1] == 3) { k++; }
                        if (pstl != 0 and open[pstr][pstl - 1] == 3) { k++; }
                        if (pstr != 0 and pstl != N - 1 and open[pstr - 1][pstl + 1] == 3) { k++; }
                        if (pstr != 0 and open[pstr - 1][pstl] == 3) { k++; }
                        if (pstr != 0 and pstl != 0 and open[pstr - 1][pstl - 1] == 3) { k++; }
                        if (first[pstr][pstl] == k) {
                            opennumber(pstr, pstl, first, open, openc, N);
                            for (int i = 0; i < N; i++) {
                                for (int j = 0; j < N; j++) {
                                    if (open[i][j] == 4) {
                                        explore = 1;
                                        fincontroll = "Вы, поставив неверную бомбу, нажали на цифру и взорвали соседнюю бомбу!";
                                    }
                                }
                            }
                        }
                    }
                }
                if (first[pstr][pstl] == 9 and open[pstr][pstl] != 3) {
                    explore = 1;
                    fincontroll = "Вы нажали на бомбу!";
                }
                if (open[pstr][pstl] == 0) {
                    if (first[pstr][pstl] == 1 or first[pstr][pstl] == 2 or first[pstr][pstl] == 3 or first[pstr][pstl] == 4 or first[pstr][pstl] == 5 or first[pstr][pstl] == 6 or first[pstr][pstl] == 7 or first[pstr][pstl] == 8) {
                        open[pstr][pstl] = 1;
                    }
                }
            }
            if ((gamecontroll == 1 and KEY[66]) or (gamecontroll == 0 and n == 1)) //нажата b
            {
                if (open[pstr][pstl] == 0 or open[pstr][pstl] == 3) {
                    if (open[pstr][pstl] == 3) {
                        open[pstr][pstl] = 0;
                        bombput--;
                        if (first[pstr][pstl] == 9) {
                            exp--;
                        }
                    }
                    else {
                        open[pstr][pstl] = 3;
                        bombput++;
                        if (first[pstr][pstl] == 9) {
                            exp++;
                        }
                    }
                }
            }
            if ((gamecontroll == 1 and KEY[27]) or (gamecontroll == 0 and n == 0)) //нажат Esc
            {
                if (debug == 1) {//////////////////////////////////////////////////////////////
                    //показ карты статуса контроля открытия
                    cout << "  | ";
                    for (int i = 0; i < N; i++) {
                        if (i < 10) {
                            cout << i << " ";
                        }
                        else {
                            cout << i << "";
                        }
                    }
                    cout << "| \n";
                    cout << "  | ";
                    for (int i = 0; i < N; i++) {
                        cout << "--";
                    }
                    cout << "| \n";
                    for (int i = 0; i < N; i++) {
                        if (i < 10) {
                            cout << i << " | ";
                        }
                        else {
                            cout << i << "| ";
                        }
                        for (int j = 0; j < N; j++) {
                            if (openc[i][j] == 1) {
                                cout << "1 ";
                            }
                            else {
                                cout << "0 ";
                            }
                        }
                        cout << "|\n";
                    }
                    cout << "  | ";
                    for (int i = 0; i < N; i++) {
                        cout << "--";
                    }
                    cout << "| \n";
                    //показ статуса открытых клеток
                    cout << "  | ";
                    for (int i = 0; i < N; i++) {
                        if (i < 10) {
                            cout << i << " ";
                        }
                        else {
                            cout << i << "";
                        }
                    }
                    cout << "| \n";
                    cout << "  | ";
                    for (int i = 0; i < N; i++) {
                        cout << "--";
                    }
                    cout << "| \n";
                    for (int i = 0; i < N; i++) {
                        if (i < 10) {
                            cout << i << " | ";
                        }
                        else {
                            cout << i << "| ";
                        }
                        for (int j = 0; j < N; j++) {
                            cout << open[i][j] << " ";
                        }
                        cout << "|\n";
                    }
                }
                endgame(debug);//////////////////////////////////////////////////////////////
                return 0;
            }
            if (bombput == m) {
                k = 0;
                for (int i = 0; i < N; i++) {
                    for (int j = 0; j < N; j++) {
                        if (open[i][j] == 1) {
                            k++;
                        }
                        else {
                            if (open[i][j] == 3 and first[i][j] == 9) {
                                k++;
                            }
                        }
                    }
                }
                if (k == N * N) {
                    end = 1;
                    fincontroll = "ВЫ ПОБЕДИЛИ!";
                }
                if (debug == 1) { cout << "k = " << k << " из " << N * N << " | exp = " << exp << "\n"; }//////////////////////////////////////////////////////////////
            }
            if (gamecontroll == 1) {
                Sleep(200);
            }
        }


        //конец игры
        n = -1;
        while (n != 0) {
            system("cls");
            showmap(2, debug, gamecontroll, pstr, pstl, first, open, openc, N);//////////////////////////////////////////////////////////////
            int exp1 = exp * N * N;
            cout << "---Конец игры!---\n";
            cout << "Причина: " << fincontroll << " \n";
            cout << "-----------------\n";
            cout << "B - правильные бомбы | b - ошибочные бомбы\n";
            cout << "-----------------\n";
            cout << "Вы правильно поставили " << exp << " бомб(ы) из " << m << " \n";
            cout << "Ваш счёт за игру: " << exp1 << " \n";
            if (gamecontroll == 1) {
                GetKEY();
                cout << "Для перехода на главный экран нажмите пробел \n";
                cout << "Для начала новой игры нажмите enter \n";
                cout << "Для выхлда из игры нажмите esc \n";
                if (KEY[27]) //нажат Esc
                {
                    session = 0;
                    n = 0;
                }
                if (KEY[13]) //нажат enter
                {
                    start = 1;
                    n = 0;
                }
                if (KEY[32]) //нажат пробел
                {
                    menu = 0;
                    start = 0;
                    n = 0;
                }
            }
            else {
                cout << "Для перехода на главный экран введите 1 \n";
                cout << "Для начала новой игры введите 2 \n";
                cout << "Для выхода из игры введите 0 \n";
                cout << "Выбор: ";
                cin >> k;
                if (k == 1) {
                    menu = 0;
                    start = 0;
                    n = 0;
                }
                if (k == 2) {
                    n = 0;
                    start = 1;
                }
                if (k == 0) {
                    session = 0;
                    n = 0;
                }
            }

            if (debug == 1) {//////////////////////////////////////////////////////////////
                //показ карты статуса контроля открытия
                cout << "  | ";
                for (int i = 0; i < N; i++) {
                    if (i < 10) {
                        cout << i << " ";
                    }
                    else {
                        cout << i << "";
                    }
                }
                cout << "| \n";
                cout << "  | ";
                for (int i = 0; i < N; i++) {
                    cout << "--";
                }
                cout << "| \n";
                for (int i = 0; i < N; i++) {
                    if (i < 10) {
                        cout << i << " | ";
                    }
                    else {
                        cout << i << "| ";
                    }
                    for (int j = 0; j < N; j++) {
                        if (openc[i][j] == 1) {
                            cout << "1 ";
                        }
                        else {
                            cout << "0 ";
                        }
                    }
                    cout << "|\n";
                }
                cout << "  | ";
                for (int i = 0; i < N; i++) {
                    cout << "--";
                }
                cout << "| \n";
                //показ статуса открытых клеток
                cout << "  | ";
                for (int i = 0; i < N; i++) {
                    if (i < 10) {
                        cout << i << " ";
                    }
                    else {
                        cout << i << "";
                    }
                }
                cout << "| \n";
                cout << "  | ";
                for (int i = 0; i < N; i++) {
                    cout << "--";
                }
                cout << "| \n";
                for (int i = 0; i < N; i++) {
                    if (i < 10) {
                        cout << i << " | ";
                    }
                    else {
                        cout << i << "| ";
                    }
                    for (int j = 0; j < N; j++) {
                        cout << open[i][j] << " ";
                    }
                    cout << "|\n";
                }
            }
            if (gamecontroll == 1) {
                Sleep(2000);
            }
        }
    }
    endgame(debug);//////////////////////////////////////////////////////////////
    return 0;
}