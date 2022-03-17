#include "iostream"

using namespace std;

int board[8][8]; // Шахматная доска

int Check(int c, int r){ // Проверка, что можно ставить в клетку [c][r]
    for (int i = 0; i < c; ++i){ // Проверка только сверху т.к. снизу точно ничего нет
        if (board[i][r]) 
           return 0; // Проверка горизонтали
        // Проверка диагоналей (тоже только сверху от точки)
        if ((r - c + i >= 0) and (board[i][r - c + i])) 
           return 0;
        if ((r + c - i < 8) and (board[i][r + c - i]))
           return 0;
    }
    return 1; // Если ферзь не находится под ударом, ставим его
}

// Рекурсивная функция
int Horizontal(int i){ // Горизонтальная линия
    if (i == 8) // Если расставили все фигуры
        return 1;
    for (int j = 0; j < 8; ++j)  // Ищем место по вертикали
        if (Check(i, j)){ // Если не под ударом - ставим
            board[i][j] = 1;
            if (Horizontal(i + 1) == 1)
                return 1; // Ооставляем ферзя на позиции
            board[i][j] = 0; // Если не получилось создать выйгрышную комбинацию - убираем ферзя
        }
    return 0; // Неудачный возврат
}

int main(){
    Horizontal(0); // Начало с 0 линии
    // Вывод
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j] == 1)
                cout << "+ ";
            else
                cout << ". ";
        }
        cout << endl;
    }
}