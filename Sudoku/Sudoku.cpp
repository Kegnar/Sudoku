#include <iostream>
#include <vector>
#include <Windows.h>
using namespace std;
class Sudoku {
    vector<vector<int>> grid;
    // проверяет возможность воткнуть число в клетку
    bool isValid(int row, int col, int num) {
        // Проверка строки и столбца
        for (int i = 0; i < 9; ++i) {
            if (grid[row][i] == num || grid[i][col] == num) {
                return false;
            }
        }

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

    // рекурсия для решения судоку
    bool solve() {
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                if (grid[row][col] == 0) { 
                    for (int num = 1; num <= 9; ++num) {
                        if (isValid(row, col, num)) {
                            grid[row][col] = num;

                            if (solve()) { 
                                return true;
                            }
                        	grid[row][col] = 0; 
                        }
                    }
                    return false; 
                }
            }
        }
        return true; 
    }

public:
    Sudoku() : grid(9, std::vector<int>(9, 0)) {}

    // Ввод начального состояния пользователем TODO: переделать, чтобы парсила строку, а не по символу
    void inputGrid() {
        cout << "Введите начальную сетку судоку (9 строк по 9 чисел). Используйте 0 для пустых ячеек:\n" ;
        for (int row = 0; row < 9; ++row) {
            for (int col = 0; col < 9; ++col) {
                cout << "Строка " << row + 1 << " : ";
                cin >> grid[row][col];
            }
        }
    }
    void setGrid(const vector<vector<int>>& grid)
    {
        this->grid = grid;
    }

    // Рисуем судоку
    void printGrid() const {
   
        for(int i = 0;i < 9;i++)
        {
	        for (int j = 0;j<9;j++)
	        {
                cout << grid[i][j];
                if (j>0 && (j + 1) < 9 && (j+1) % 3 == 0) {
                    cout << '|';
                }
                else
                {
                    cout << ' ';
                }
	        }
            cout << '\n';
            if (i > 0 && (i + 1) < 9 && (i+1) % 3 == 0) cout << "-----------------\n";
        }
    }

    // Запуск решалки судоку
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
# ifdef _DEBUG  // профиль Debug
    vector<vector<int>> test{
    {5, 3, 0, 0, 7, 0, 0, 0, 0},
    {6, 0, 0, 1, 9, 5, 0, 0, 0},
    {0, 9, 8, 0, 0, 0, 0, 6, 0},
    {8, 0, 0, 0, 6, 0, 0, 0, 3},
    {4, 0, 0, 8, 0, 3, 0, 0, 1},
    {7, 0, 0, 0, 2, 0, 0, 0, 6},
    {0, 6, 0, 0, 0, 0, 2, 8, 0},
    {0, 0, 0, 4, 1, 9, 0, 0, 5},
    {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };
    sudoku.setGrid(test);
#endif

#ifdef NDEBUG   //профиль Release
    cout << "Введите начальные условия:\n";
    sudoku.inputGrid();
    system("cls");
#endif



  
	cout << "\nНачальная сетка:\n";
    sudoku.printGrid();

    if (sudoku.solveSudoku()) {
        std::cout << "\nРешенная сетка:\n";
        sudoku.printGrid();
    }

}
