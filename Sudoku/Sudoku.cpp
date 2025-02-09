#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;
class Sudoku {
private:
    vector<vector<int>> grid;

    // Проверяет, можно ли поместить число num в позицию (row, col)
    bool isValid(int row, int col, int num) {
        // Проверка строки и столбца
        for (int i = 0; i < 9; ++i) {
            if (grid[row][i] == num || grid[i][col] == num) {
                return false;
            }
        }

        // Проверка квадрата 3x3
        int startRow = row - row % 3;
        int startCol = col - col % 3;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (grid[startRow + i][startCol + j] == num) {
                    return false;
                }
            }
        }
        return true;
    }

    // Рекурсивная функция для решения судоку
    bool solve() {
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (grid[row][col] == 0) { 
                    for (int num = 1; num <= 9; ++num) {
                        if (isValid(row, col, num)) {
                            grid[row][col] = num; // Помещаем число

                            if (solve()) { // Рекурсивно решаем дальше
                                return true;
                            }
                        	grid[row][col] = 0; 
                        }
                    }
                    return false; // Нет подходящего числа, возвращаемся назад
                }
            }
        }
        return true; // Все ячейки заполнены
    }

public:
    Sudoku() : grid(9, std::vector<int>(9, 0)) {}

    // Метод ввода начальной сетки пользователем
    void inputGrid() {
        cout << "Введите начальную сетку судоку (9 строк по 9 чисел). Используйте 0 для пустых ячеек:\n" ;
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                cin >> grid[row][col];
            }
        }
    }

    // Рисуем судоку
    void printGrid() const {
    /*    for (const auto& row : grid) {
            for (int cell : row) {
                cout << cell << " ";
            }
            cout << '\n';
        }*/
        for(int i = 0;i < 9;i++)
        {
	        for (int j = 0;j<9;j++)
	        {
                cout << grid[i][j];
                if (j > 0 && j % 3 == 0) {
                    cout << '|';
                }
               /* else
                {
                    cout << ' ';
                }*/
               
	        }
            cout << '\n';
            if (i > 0 && i % 3 == 0) cout << "-----------\n";
          
        }
    }

    // Метод для запуска решения судоку
    bool solveSudoku() {
        if (solve()) {
            return true;
        }
            cout << "Невозможно решить судоку.\n";
            return false;
        }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Sudoku sudoku;

    cout << "Введите начальные условия:\n";
    sudoku.inputGrid();
    system("cls");

	cout << "\nНачальная сетка:\n";
    sudoku.printGrid();

    if (sudoku.solveSudoku()) {
        std::cout << "\nРешенная сетка:\n";
        sudoku.printGrid();
    }

}