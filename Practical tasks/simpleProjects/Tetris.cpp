//Тетрис 1.0
#include <iostream>
#include <Windows.h>
#include <ctime>
using namespace std;

///------------------------///
///---ОСНОВНЫЕ НАСТРОЙКИ---///
///------------------------///
int const N1 = 20;//размер игрового поля (высота)
int const N2 = 9;//размер игрового поля (ширина)
int debug = 0;//debug режим (1 - вкл | 0 - выкл)
int chsp = 1;//Изменение скорости подения с увеличением очков (1 - вкл | 0 - выкл)
///------------------------///
///------------------------///
///------------------------///
int game[N1 + 1][N2 + 1];
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

int main()
{
    setlocale(LC_ALL, "rus");
    if (N1 < 20 or N2 < 9 or debug > 1 or debug < 0 or chsp > 1 or chsp < 0) {
        cout << "   *   *  * * * *  * * *  |      *\n";
        cout << "    * *   *     *  *      |  *  * \n";
        cout << "     *    *     *  *      |     * \n";
        cout << "    *     *     *  *      |  *  * \n";
        cout << "   *      *     *  * * *  |      *\n";
        cout << "----------------------------------\n";
        if (N1 < 20 or N2 < 9) {
            cout << "N1 должно быть >= 20 и N2 должно быть >= 9\n";
            cout << "Пожалуйста, эти параметры в настройках файла!\n";
        }
        if (debug > 1 or debug < 0) {
            cout << "Значение debug может принимать только 1 или 0\n";
            cout << "Пожалуйста, этот параметр в настройках файла!\n";
        }
        if (chsp > 1 or chsp < 0) {
            cout << "Значение chsp (изменение скорости) может принимать только 1 или 0\n";
            cout << "Пожалуйста, этот параметр в настройках файла!\n";
        }
        return 0;
    }
    int menu = 0;
    int start = 0;
    int end = 0;
    int vr = 0;
    long int exp = 0;
    while (end != 1) {
        system("cls");
        if (menu == 0) {
            vr = 0;
            while (vr != 1) {
                system("cls");
                cout << "-----------------------------------\n";
                cout << "|||||ДОБРО ПОЖАЛОВАТЬ В ТЕТРИС|||||\n";
                cout << "|---------версия 1.0 DEBUG--------|\n";
                cout << "|---------------------------------|\n";
                cout << "Что вы хотите сделать? \n";
                cout << "Прочитать про управление и правила (нажмите i) \n";
                cout << "Войти в настройки (нажмите s) \n";
                cout << "Начать игру (нажмите пробел) \n";
                cout << "Выйти из игры (нажмите Esc) \n";
                GetKEY();
                if (KEY[32]) {//пробел
                    start = 1;
                    vr = 1;
                }
                if (KEY[83]) {//s
                    menu = 2;
                    vr = 1;
                }
                if (KEY[27]) {//esc
                    end = 1;
                    vr = 1;
                }
                if (KEY[73]) {//i
                    menu = 1;
                    vr = 1;
                }
                Sleep(1000);
            }
        }
        if (menu == 1) {
            vr = 0;
            while (vr != 1) {
                system("cls");
                cout << "\n";
                cout << "|----------Управление и правила----------|\n";
                cout << "------------------------------------------\n";
                cout << "ВНИМАНИЕ: если у вас скачет экран, расширьте окно игры!\n";
                cout << "------------------------------------------\n";
                cout << "------------------Правила-----------------\n";
                cout << "Тетрис - игра на выживание. Вам нужно продержатся как можно долльше\n";
                cout << "Вы можете вращать фигуры по часовой стреле, перемещать их вправо и в лево и ускорять падение\n";
                cout << "В игре представлено 7 видов фигур:\n";
                cout << "_________________________________________________________\n";
                cout << "|1    |2      |3      |4      |5      |6      |7        |\n";
                cout << "|  *  |       |       |       |       |       |         |\n";
                cout << "|  *  |  *    |    *  |  * *  |  *    |    *  |    *    |\n";
                cout << "|  *  |  *    |    *  |  * *  |  * *  |  * *  |  * * *  |\n";
                cout << "|  *  |  * *  |  * *  |       |    *  |  *    |         |\n";
                cout << "|     |       |       |       |       |       |         |\n";
                cout << "---------------------------------------------------------\n";
                cout << "За каждую установленную фигуру даётся некоторое кол-во очков, зависимое от скорости падения фигур \n";
                cout << "Так же очки даются за одновременное уничтожение линий: \n";
                cout << "За 1 линию: 100 \n";
                cout << "За 2 линии: 300 \n";
                cout << "За 3 линии: 700 \n";
                cout << "За 4 линии: 1500 \n";
                cout << "------------------------------------------\n";
                cout << "\n";
                cout << "----------------Обозначения---------------\n";
                cout << "(*) - Управляемая фигура\n";
                cout << "(X) - Следующая фигура\n";
                cout << "(#) - Зафиксированные фигуры\n";
                cout << "(.) - Тень управляемой фигуры\n";
                cout << "------------------------------------------\n";
                cout << "\n";
                cout << "----------------Управление----------------\n";
                cout << "(w) - Поворот фигуры\n";
                cout << "(a) - Движение влево\n";
                cout << "(d) - Движение вправо\n";
                cout << "(s) - Ускорение падения\n";
                cout << "(esc) - Выход из текущей игры\n";
                cout << "------------------------------------------\n";
                cout << "Создатель: Сорокин Андрей\n";
                cout << "------------------------------------------\n";
                cout << "Для выхода нажмите Esc";
                GetKEY();
                if (KEY[27]) {//esc
                    menu = 0;
                    vr = 1;
                }
                Sleep(1000);
            }
        }
        if (menu == 2) {
            vr = 0;
            while (vr != 1) {
                system("cls");
                cout << "|-----------Настройки!-----------|\n";
                cout << "----------------------------------\n";
                if (debug == 0) {
                    cout << "Для включения дебаг режима нажмите d \n";
                }
                else {
                    cout << "Для выключения дебаг режима нажмите d \n";
                }
                if (chsp == 0) {
                    cout << "Для включения режима изменения скорости подения с увеличением очков нажмите s \n";
                }
                else {
                    cout << "Для выключения режима изменения скорости подения с увеличением очков нажмите s \n";
                }
                cout << "Для выхода нажмите Esc";
                GetKEY();
                if (KEY[68]) {//d
                    menu = 2;
                    if (debug == 0) {
                        debug = 1;
                    }
                    else {
                        debug = 0;
                    }
                    vr = 1;
                }
                if (KEY[83]) {//s
                    menu = 2;
                    if (chsp == 0) {
                        chsp = 1;
                    }
                    else {
                        chsp = 0;
                    }
                    vr = 1;
                }
                if (KEY[27]) {//esc
                    menu = 0;
                    vr = 1;
                }
                Sleep(1000);
            }
        }








        if (start == 1) {
            system("cls");
            for (int i = 0; i <= N1; i++) {
                for (int j = 0; j <= N2; j++) {
                    game[i][j] = 0;
                }
            }

            //игра
            int spown = 0;
            int gameend = 0;
            int n = 0;
            int k = 0;
            int k2 = 0;
            int k3 = 0;
            int k4 = 0;
            int next = 0;
            time_t now = time(0);
            next = (rand() + now) % 10;
            while (next > 7 or next < 1) {
                next = (rand() + now) % 10;
            }
            int k5 = 0;
            int speed = 0;
            int rspeed = 0;

            int top = 0;
            int bottom = 0;
            int left = 0;
            int right = 0;
            int rotate = 0;
            exp = 0;
            vr = 0;
            while (gameend == 0) {
                speed = 200;
                if (chsp == 1) {
                    speed = 200 - (exp / 1000) * 20;//формура рассчёта скорости падения (если включено)
                    if (speed < 20) {
                        speed = 20;
                    }
                }
                rspeed = speed;
                k = 0;
                k2 = 0;
                k3 = 0;
                if (spown == 0) {
                    for (int i = N1; i >= 0; i--) {
                        for (int j = 0; j <= N2; j++) {
                            if (game[i][j] == 8) {
                                game[i][j] = 0;
                            }
                        }
                    }
                    n = next;
                    time_t now = time(0);
                    next = (rand() + now) % 10;
                    while (next > 7 or next < 1) {
                        next = (rand() + now) % 10;
                    }
                    //генерация новой фигуры
                    //n = 2;///////////////////////////////////
                    if (n == 1 or next == 1) {
                        if (n == 1) {
                            game[0][N2 / 2] = 2;
                            game[1][N2 / 2] = 2;
                            game[2][N2 / 2] = 2;
                            game[2][N2 / 2 - 1] = 2;
                            top = 0;
                            bottom = 2;
                            left = N2 / 2 - 1;
                            right = N2 / 2;
                        }
                        if (next == 1) {
                            game[0][1] = 8;
                            game[1][1] = 8;
                            game[2][1] = 8;
                            game[2][0] = 8;
                        }
                    }
                    if (n == 2 or next == 2) {
                        if (n == 2) {
                            game[0][N2 / 2] = 2;
                            game[1][N2 / 2] = 2;
                            game[2][N2 / 2] = 2;
                            game[3][N2 / 2] = 2;
                            top = 0;
                            bottom = 3;
                            left = N2 / 2;
                            right = N2 / 2;
                        }
                        if (next == 2) {
                            game[0][1] = 8;
                            game[1][1] = 8;
                            game[2][1] = 8;
                            game[3][1] = 8;
                        }
                    }
                    if (n == 3 or next == 3) {
                        if (n == 3) {
                            game[0][N2 / 2] = 2;
                            game[0][N2 / 2 - 1] = 2;
                            game[1][N2 / 2] = 2;
                            game[1][N2 / 2 - 1] = 2;
                            top = 0;
                            bottom = 1;
                            left = N2 / 2 - 1;
                            right = N2 / 2;
                        }
                        if (next == 3) {
                            game[0][0] = 8;
                            game[0][1] = 8;
                            game[1][0] = 8;
                            game[1][1] = 8;
                        }
                    }
                    if (n == 4 or next == 4) {
                        if (n == 4) {
                            game[0][N2 / 2] = 2;
                            game[1][N2 / 2] = 2;
                            game[2][N2 / 2] = 2;
                            game[2][N2 / 2 + 1] = 2;
                            top = 0;
                            bottom = 2;
                            left = N2 / 2;
                            right = N2 / 2 + 1;
                        }
                        if (next == 4) {
                            game[0][1] = 8;
                            game[1][1] = 8;
                            game[2][1] = 8;
                            game[2][2] = 8;
                        }
                    }
                    if (n == 5 or next == 5) {
                        if (n == 5) {
                            game[0][N2 / 2 - 1] = 2;
                            game[0][N2 / 2] = 2;
                            game[1][N2 / 2] = 2;
                            game[1][N2 / 2 + 1] = 2;
                            top = 0;
                            bottom = 1;
                            left = N2 / 2 - 1;
                            right = N2 / 2 + 1;
                        }
                        if (next == 5) {
                            game[0][0] = 8;
                            game[0][1] = 8;
                            game[1][1] = 8;
                            game[1][2] = 8;
                        }
                    }
                    if (n == 6 or next == 6) {
                        if (n == 6) {
                            game[0][N2 / 2 + 1] = 2;
                            game[0][N2 / 2] = 2;
                            game[1][N2 / 2] = 2;
                            game[1][N2 / 2 - 1] = 2;
                            top = 0;
                            bottom = 1;
                            left = N2 / 2 - 1;
                            right = N2 / 2 + 1;
                        }
                        if (next == 6) {
                            game[0][1] = 8;
                            game[0][2] = 8;
                            game[1][1] = 8;
                            game[1][0] = 8;
                        }
                    }
                    if (n == 7 or next == 7) {
                        if (n == 7) {
                            game[0][N2 / 2] = 2;
                            game[1][N2 / 2] = 2;
                            game[1][N2 / 2 + 1] = 2;
                            game[1][N2 / 2 - 1] = 2;
                            top = 0;
                            bottom = 1;
                            left = N2 / 2 - 1;
                            right = N2 / 2 + 1;
                        }
                        if (next == 7) {
                            game[0][1] = 8;
                            game[1][1] = 8;
                            game[1][2] = 8;
                            game[1][0] = 8;
                        }
                    }
                    spown = 1;
                    //система гарантированного спавна
                    /*if (bottom == 0) {
                        spown = 0;
                    }*/
                    rotate = 0;
                }
                k4 = 0;

                if (spown == 1) {
                    //спуск фигуры и её управление и закрепление
                    GetKEY();
                    if (KEY[65]) //нажат (влево)
                    {
                        for (int i = bottom; i >= top; i--) {
                            for (int j = 0; j <= N2; j++) {
                                if (j != 0 and game[i][j - 1] == 1 and game[i][j] == 2) {
                                    k = 1;
                                }
                                if (j == 0 and game[i][j] == 2) {
                                    k2 = 1;
                                }
                            }
                        }
                        if (k != 1 and k2 != 1) {
                            for (int i = bottom; i >= top; i--) {
                                for (int j = 0; j <= N2; j++) {
                                    if (j != 0 and game[i][j - 1] != 2) {
                                        if (game[i][j - 1] == 1 and game[i][j] == 2) {
                                            k = 1;
                                        }
                                        else {
                                            if (game[i][j] == 2) {
                                                game[i][j - 1] = 2;
                                                game[i][j] = 0;
                                            }
                                        }
                                        k3 = 0;
                                    }
                                }
                            }
                        }
                        if (k != 1 and left != 0) {
                            left--;
                            right--;
                        }
                    }
                    if (KEY[68]) //нажат (вправо)
                    {
                        for (int i = bottom; i >= top; i--) {
                            for (int j = 0; j <= N2; j++) {
                                if (j != N2 and game[i][j + 1] == 1 and game[i][j] == 2) {
                                    k = 1;
                                }
                                if (j == N2 and game[i][j] == 2) {
                                    k3 = 1;
                                }
                            }
                        }
                        if (k != 1 and k3 != 1) {
                            for (int i = bottom; i >= top; i--) {
                                for (int j = N2; j >= 0; j--) {
                                    if (j != N2 and game[i][j + 1] != 2) {
                                        if (game[i][j + 1] == 1 and game[i][j] == 2) {
                                            k = 1;
                                        }
                                        else {
                                            if (game[i][j] == 2) {
                                                game[i][j + 1] = 2;
                                                game[i][j] = 0;
                                            }
                                        }
                                        k2 = 0;
                                    }
                                }
                            }
                        }
                        if (k != 1 and right != N2) {
                            left++;
                            right++;
                        }
                    }
                    if (KEY[83]) {//нажат s (ускорение)
                        speed = 20;
                    }
                    if (KEY[27]) {//нажат s (ускорение)
                        gameend = 1;
                    }
                    if (KEY[87] and n != 3) {//нажат w (поворот)
                        k5 = 0;
                        if (n == 1) {
                            if (rotate == 0 and right != N2 and game[top][left] != 1 and game[top + 1][left] != 1 and game[top + 1][left + 1] != 1 and game[top + 1][left + 2] != 1) {
                                game[top][left] = 3;
                                game[top + 1][left] = 3;
                                game[top + 1][left + 1] = 3;
                                game[top + 1][left + 2] = 3;
                                rotate = 1;
                            }
                            else {
                                if (rotate == 1 and bottom != N1 and game[top][left + 1] != 1 and game[top][left + 2] != 1 and game[top + 1][left + 1] != 1 and game[top + 2][left + 1] != 1) {
                                    game[top][left + 1] = 3;
                                    game[top][left + 2] = 3;
                                    game[top + 1][left + 1] = 3;
                                    game[top + 2][left + 1] = 3;
                                    rotate = 2;
                                }
                                else {
                                    if (rotate == 2 and left != 0 and game[top + 1][left] != 1 and game[top + 1][left + 1] != 1 and game[top + 1][left + 2] != 1 and game[top + 2][left + 2] != 1) {
                                        game[top + 1][left] = 3;
                                        game[top + 1][left + 1] = 3;
                                        game[top + 1][left + 2] = 3;
                                        game[top + 2][left + 2] = 3;
                                        rotate = 3;
                                    }
                                    else {
                                        if (rotate == 3 and game[top][left + 1] != 1 and game[top + 1][left + 1] != 1 and game[top + 2][left + 1] != 1 and game[top + 2][left] != 1) {
                                            game[top][left + 1] = 3;
                                            game[top + 1][left + 1] = 3;
                                            game[top + 2][left + 1] = 3;
                                            game[top + 2][left] = 3;
                                            rotate = 0;
                                        }
                                        else {
                                            k5 = 1;
                                        }
                                    }
                                }
                            }
                        }
                        if (n == 2) {
                            if (rotate == 0 and right != N2 and right != N2 - 1 and left != 0 and game[top + 2][left - 1] != 1 and game[top + 2][left + 1] != 1 and game[top + 2][left + 2] != 1 and game[top + 2][left] != 1) {
                                game[top + 2][left - 1] = 3;
                                game[top + 2][left + 1] = 3;
                                game[top + 2][left + 2] = 3;
                                game[top + 2][left] = 3;
                                rotate = 1;
                            }
                            else {
                                if (rotate == 1 and bottom != N1 and bottom != N1 - 1 and bottom != N1 - 2 and game[top][left + 1] != 1 and game[top + 1][left + 1] != 1 and game[top + 2][left + 1] != 1 and game[top + 3][left + 1] != 1) {
                                    game[top][left + 1] = 3;
                                    game[top + 1][left + 1] = 3;
                                    game[top + 2][left + 1] = 3;
                                    game[top + 3][left + 1] = 3;
                                    rotate = 0;
                                }
                                else {
                                    k5 = 1;
                                }
                            }
                        }
                        if (n == 4) {
                            if (rotate == 0 and left != 0 and game[top + 1][left] != 1 and game[top + 1][left + 1] != 1 and game[top + 1][left + 2] != 1 and game[top + 2][left] != 1) {
                                game[top + 1][left] = 3;
                                game[top + 1][left + 1] = 3;
                                game[top + 1][left + 2] = 3;
                                game[top + 2][left] = 3;
                                rotate = 1;
                            }
                            else {
                                if (rotate == 1 and game[top][left] != 1 and game[top][left + 1] != 1 and game[top + 1][left + 1] != 1 and game[top + 2][left + 1] != 1) {
                                    game[top][left] = 3;
                                    game[top][left + 1] = 3;
                                    game[top + 1][left + 1] = 3;
                                    game[top + 2][left + 1] = 3;
                                    rotate = 2;
                                }
                                else {
                                    if (rotate == 2 and right != N2 and game[top + 1][left] != 1 and game[top + 1][left + 1] != 1 and game[top + 1][left + 2] != 1 and game[top][left + 2] != 1) {
                                        game[top + 1][left] = 3;
                                        game[top + 1][left + 1] = 3;
                                        game[top + 1][left + 2] = 3;
                                        game[top][left + 2] = 3;
                                        rotate = 3;
                                    }
                                    else {
                                        if (rotate == 3 and bottom != N1 and game[top][left + 1] != 1 and game[top + 1][left + 1] != 1 and game[top + 2][left + 1] != 1 and game[top + 1][left + 2] != 1) {
                                            game[top][left + 1] = 3;
                                            game[top + 1][left + 1] = 3;
                                            game[top + 2][left + 1] = 3;
                                            game[top + 2][left + 2] = 3;
                                            rotate = 0;
                                        }
                                        else {
                                            k5 = 1;
                                        }
                                    }
                                }
                            }
                        }
                        if (n == 5) {
                            if (rotate == 0 and bottom != N1 and game[top][left + 1] != 1 and game[top + 1][left] != 1 and game[top + 1][left + 1] != 1 and game[top + 2][left] != 1) {
                                game[top][left + 1] = 3;
                                game[top + 1][left] = 3;
                                game[top + 1][left + 1] = 3;
                                game[top + 2][left] = 3;
                                rotate = 1;
                            }
                            else {
                                if (rotate == 1 and right != N2 and game[top][left] != 1 and game[top][left + 1] != 1 and game[top + 1][left + 1] != 1 and game[top + 1][left + 2] != 1) {
                                    game[top][left] = 3;
                                    game[top][left + 1] = 3;
                                    game[top + 1][left + 1] = 3;
                                    game[top + 1][left + 2] = 3;
                                    rotate = 0;
                                }
                                else {
                                    k5 = 1;
                                }
                            }
                        }
                        if (n == 7) {
                            if (rotate == 0 and bottom != N1 and game[top][left] != 1 and game[top + 1][left] != 1 and game[top + 1][left + 1] != 1 and game[top + 2][left] != 1) {
                                game[top][left] = 3;
                                game[top + 1][left] = 3;
                                game[top + 1][left + 1] = 3;
                                game[top + 2][left] = 3;
                                rotate = 1;
                            }
                            else {
                                if (rotate == 1 and right != N2 and game[top][left] != 1 and game[top][left + 1] != 1 and game[top][left + 2] != 1 and game[top + 1][left + 1] != 1) {
                                    game[top][left] = 3;
                                    game[top][left + 1] = 3;
                                    game[top][left + 2] = 3;
                                    game[top + 1][left + 1] = 3;
                                    rotate = 2;
                                }
                                else {
                                    if (rotate == 2 and bottom != N1 and game[top][left + 1] != 1 and game[top + 1][left] != 1 and game[top + 1][left + 1] != 1 and game[top + 2][left + 1] != 1) {
                                        game[top][left + 1] = 3;
                                        game[top + 1][left] = 3;
                                        game[top + 1][left + 1] = 3;
                                        game[top + 2][left + 1] = 3;
                                        rotate = 3;
                                    }
                                    else {
                                        if (rotate == 3 and right != N2 and game[top][left + 1] != 1 and game[top + 1][left] != 1 and game[top + 1][left + 1] != 1 and game[top + 1][left + 2] != 1) {
                                            game[top][left + 1] = 3;
                                            game[top + 1][left] = 3;
                                            game[top + 1][left + 1] = 3;
                                            game[top + 1][left + 2] = 3;
                                            rotate = 0;
                                        }
                                        else {
                                            k5 = 1;
                                        }
                                    }
                                }
                            }
                        }
                        if (n == 6) {
                            if (rotate == 0 and bottom != N1 and game[top][left] != 1 and game[top + 1][left] != 1 and game[top + 1][left + 1] != 1 and game[top + 2][left + 1] != 1) {
                                game[top][left] = 3;
                                game[top + 1][left] = 3;
                                game[top + 1][left + 1] = 3;
                                game[top + 2][left + 1] = 3;
                                rotate = 1;
                            }
                            else {
                                if (rotate == 1 and right != N2 and game[top][left + 1] != 1 and game[top][left + 2] != 1 and game[top + 1][left] != 1 and game[top + 1][left + 1] != 1) {
                                    game[top][left + 1] = 3;
                                    game[top][left + 2] = 3;
                                    game[top + 1][left] = 3;
                                    game[top + 1][left + 1] = 3;
                                    rotate = 0;
                                }
                                else {
                                    k5 = 1;
                                }

                            }
                        }
                        if (k5 != 1) {
                            for (int i = top; i <= bottom; i++) {
                                for (int j = left; j <= right; j++) {
                                    if (game[i][j] == 2) { game[i][j] = 0; }
                                }
                            }
                            left = N2;
                            right = 0;
                            top = N1;
                            bottom = 0;
                            for (int i = 0; i <= N1; i++) {
                                for (int j = 0; j <= N2; j++) {
                                    if (game[i][j] == 3) { game[i][j] = 2; }
                                    if (game[i][j] == 2 and j < left) { left = j; }
                                    if (game[i][j] == 2 and j > right) { right = j; }
                                    if (game[i][j] == 2 and i < top) { top = i; }
                                    if (game[i][j] == 2 and i > bottom) { bottom = i; }
                                }
                            }
                        }
                    }
                    for (int i = bottom; i >= top; i--) {
                        for (int j = 0; j <= N2; j++) {
                            if (game[i][j] == 2 and (i == N1 or game[i + 1][j] == 1)) {
                                k = 1;
                            }
                        }
                    }
                    if (k != 1) {
                        for (int i = bottom; i >= top; i--) {
                            for (int j = 0; j <= N2; j++) {
                                if (game[i][j] == 2) {
                                    game[i + 1][j] = 2;
                                    game[i][j] = 0;
                                }
                            }
                        }
                        top++;
                        bottom++;
                    }
                    else {
                        for (int i = bottom; i >= top; i--) {
                            for (int j = 0; j <= N2; j++) {
                                if (game[i][j] == 2) {
                                    game[i][j] = 1;
                                    spown = 0;
                                    top = 0;
                                    bottom = 0;
                                    k = 0;
                                }
                            }
                        }
                        exp += (210 - rspeed);//формула рассчёта счёта за 1 фигуру
                    }



                    //отрисовка поля
                    system("cls");
                    for (int i = 0; i <= N2; i++) {
                        cout << "--";
                    }
                    cout << "\n";
                    for (int i = 0; i <= N1; i++) {
                        cout << "|";
                        for (int j = 0; j <= N2; j++) {
                            if (i == 4 and game[i][j] == 0) {
                                cout << "--";
                            }
                            else {
                                if (game[i][j] == 2) {
                                    cout << "* ";
                                    //cout << game[i][j] << " ";
                                }
                                else {
                                    if (game[i][j] == 1) {
                                        cout << "# ";
                                        //cout << game[i][j] << " ";
                                    }
                                    else {
                                        if (j <= right and j >= left and i > top and game[i][j] == 0 and spown == 1) {
                                            cout << ". ";
                                        }
                                        else {
                                            if (game[i][j] == 0) {
                                                cout << "  ";
                                            }
                                            else {
                                                if (game[i][j] == 8) {
                                                    cout << "X ";
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        cout << "|\n";
                    }
                    for (int i = 0; i <= N2; i++) {
                        cout << "--";
                    }
                    cout << "\n";
                    cout << "Ваш счёт: " << exp << "\n";
                    cout << "\n";
                    if (debug == 1) {
                        cout << "spown: " << spown << " |\n";
                        cout << "top: " << top << " |\n";
                        cout << "bottom: " << bottom << " |\n";
                        cout << "left: " << left << " |\n";
                        cout << "right: " << right << " |\n";
                        cout << "n: " << n << " |\n";
                        cout << "k5: " << k5 << " |\n";
                        cout << "next: " << next << " |\n";
                        cout << "vr: " << vr << " |\n";
                        cout << "Cкорость: " << speed << " |\n";
                    }

                    k4 = 0;
                        int kkk = 0;//конфедерация красных карликов
                    for (int i = N1; i >= 0; i--) {
                        for (int j = 0; j <= N2; j++) {
                            if (game[i][j] == 1) {
                                k4++;
                            }
                        }
                        if (k4 == N2 + 1) {
                            for (int j = 0; j <= N2; j++) {
                                game[i][j] = 0;
                            }
                            for (int l = i - 1; l >= 4; l--) {
                                for (int j = 0; j <= N2; j++) {
                                    game[l + 1][j] = game[l][j];
                                    game[l][j] = 0;
                                }
                            }
                            i = i + 1;
                            kkk++;
                        }
                        k4 = 0;
                    }
                        if (kkk == 1) {
                            exp += 100;
                        }
                        if (kkk == 2) {
                            exp += 300;
                        }
                        if (kkk == 3) {
                            exp += 700;
                        }
                        if (kkk >= 4) {
                            exp += 1500;
                            cout << "ТЕТРИС\n";
                        }
                    if (spown == 0) {
                        for (int i = 0; i <= 4; i++) {
                            for (int j = 0; j <= N2; j++) {
                                if (game[i][j] == 1) {
                                    gameend = 1;
                                }
                            }
                        }
                    }
                }
                Sleep(speed);
            }
            start = 0;
            vr = -99;
        }
        if (vr == -99) {
            vr = 0;
            while (vr != 1) {
                system("cls");
                cout << "Игра окончена\n";
                cout << "Ваш счёт: " << exp << "\n";
                cout << "Что будем делать дальше? \n";
                cout << "Выйти в главное меню (нажмите Пробел)\n";
                cout << "Выйти из игры (нажмите Esc)\n";
                GetKEY();
                if (KEY[32]) {//пробел
                    start = 0;
                    menu = 0;
                    vr = 1;
                    exp = 0;
                }
                if (KEY[27]) {//esc
                    end = 1;
                    vr = 1;
                }
                Sleep(1000);
            }
        }
        
    }
    system("cls");
    cout << "Ждём твоего возвращения, самурай!\n";
    return 0;
}