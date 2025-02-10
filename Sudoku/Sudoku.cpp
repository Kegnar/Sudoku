#include <iostream>
#include <string>
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
	Sudoku() : grid(9, vector<int>(9, 0)) {}

	void inputGrid() {
		std::cout << "Введите начальную положение судоку построчно (9 строк по 9 цифр). Используйте 0 для пустых ячеек:\n";
		for (int row = 0; row < 9; ++row) {
			std::string line;
			std::cout << "Введите " << row + 1 << "-ю строку: ";
			std::cin >> line;

			// Проверяем длину строки
			if (line.length() != 9) {
				cerr << "Ошибка: строка должна содержать ровно 9 цифр!\n";
				exit(1);
			}

			// Преобразуем строку в числа
			for (int col = 0; col < 9; ++col) {
				if (line[col] >= '0' && line[col] <= '9') {
					grid[row][col] = line[col] - '0'; // Преобразуем символ в число
				}
				else {
					cerr << "Ошибка: введены недопустимые символы!\n";
					exit(1);
				}
			}
		}
	}
	void setGrid(const vector<vector<int>>& grid)
	{
		this->grid = grid;
	}

	// Рисуем судоку
	void printGrid() const {

		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				cout << grid[i][j];
				if (j > 0 && (j + 1) < 9 && (j + 1) % 3 == 0) {
					cout << '|';
				}
				else
				{
					cout << ' ';
				}
			}
			cout << '\n';
			if (i > 0 && (i + 1) < 9 && (i + 1) % 3 == 0) cout << "-----------------\n";
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
