#pragma once
#include <iostream>
#include "Vector.h"
#include <cmath>
using namespace std;
class Matrix
{
	size_t m_rows;
	size_t m_columns;
	Vector** m_matrix;
public:
	// констр. с парам.
	Matrix(size_t rows, size_t columns) : m_rows(rows), m_columns(columns) {
		if (rows > 0 && columns > 0) {
			m_matrix = { new Vector* [rows] {} };
			for (auto i = 0; i < rows; i++) {
				m_matrix[i] = new Vector(columns);
			}
		}
		else m_matrix = nullptr;
	}
	// констр. копир. ????
	Matrix(const Matrix& mx) : m_rows(mx.m_rows), m_columns(mx.m_columns) {
		m_matrix = new Vector* [mx.m_rows];
		for (auto i = 0; i < m_rows; i++) {
			// копируем векторы
			m_matrix[i] = new Vector(mx.m_columns);
			*m_matrix[i] = *mx.m_matrix[i];	// знач. первого элемента в массиве
		}
	}
	// констр. перемещ.
	Matrix(Matrix&& mx) noexcept : m_rows(mx.m_rows), m_columns(mx.m_columns), m_matrix(mx.m_matrix) {
		mx.m_matrix = nullptr;
		mx.m_rows = 0;
		mx.m_columns = 0;
	}
	// опер. присв. копир.
	Matrix& operator=(const Matrix& mx) {
		if (this == &mx) return *this;  // Защита от самоприсваивания
		// удаление старых данных
		for (auto i = 0; i < m_rows; i++) {
			delete m_matrix[i];
		}
		delete[] m_matrix;
		// копирование
		m_rows = mx.m_rows;
		m_columns = mx.m_columns;
		m_matrix = new Vector*[mx.m_rows];
		for (auto i = 0; i < m_rows; i++) {
			// копируем векторы
			m_matrix[i] = new Vector(mx.m_columns);
			*m_matrix[i] = *mx.m_matrix[i];
		}
		return *this;
	}
	// опер. присв. перемещ.
	Matrix& operator=(Matrix&& mx) noexcept {
		if (this == &mx) return *this;
		// удаление старых данных
		for (auto i = 0; i < m_rows; i++) {
			delete m_matrix[i];
		}
		delete[] m_matrix;
		// перемещение данных
		m_matrix = mx.m_matrix;  
		m_rows = mx.m_rows;
		m_columns = mx.m_columns;
		// очищаем исходный объект
		mx.m_matrix = nullptr;
		mx.m_rows = 0;
		mx.m_columns = 0;
		return *this;
	}
	// деструктор
	~Matrix() {
		// освобождение динамической памяти
		for (auto i = 0; i < m_rows; i++) {
			delete m_matrix[i];
		}
		delete[] m_matrix;
		m_matrix = nullptr;
		cout << "Матрица аннигилированна." << endl;
	}
	void transpose() {
		// создание временной матрицы
		Matrix temp_mtrx(0, 0);
		temp_mtrx.m_matrix = { new Vector * [m_columns] {} };
		for (auto i = 0; i < m_columns; i++) {
			temp_mtrx.m_matrix[i] = new Vector(0);
			for (auto j = 0; j < m_rows; j++) {
				temp_mtrx.m_matrix[i]->push_back(m_matrix[j]->getElement(i));
			}
		}
		cout << "++++++++++++++ TEMP-MX = CREATED +++++++++\n";
		temp_mtrx.getInfo();
		// освобождение динамической памяти
		for (auto i = 0; i < m_rows; i++) {
			delete m_matrix[i];
		}
		delete[] m_matrix;
		// перенос временной матрицы в основную
		m_matrix = temp_mtrx.m_matrix;	// перенос указателя на массивы
		m_rows += m_columns;			// меняем столбцы и строки местами в значениях
		m_columns = m_rows - m_columns;
		m_rows = m_rows - m_columns;
		temp_mtrx.m_matrix = nullptr;	// избавляемся от указателя временной матрицы, т.к основной указатель уже указывает на созданную матрицу.
	}
	void getInfo() {
		cout << "Matrix size: [" << m_rows << "]*[" << m_columns << "]" << endl;
		if (m_rows > 0 && m_columns > 0) {
			for (auto i = 0; i < m_rows; i++) {
				m_matrix[i]->getInfo();
			}
		}
		else cout << "empty;";
		cout << "\n\n";
	}
	void resize(size_t new_rows, size_t new_cols) {
		if (new_rows == m_rows && new_cols == m_columns) return;	// если повтор
		else if (new_rows == 0 || new_cols == 0) {
			// освобождение динамической памяти
			for (auto i = 0; i < m_rows; i++) {
				delete m_matrix[i];
			}
			delete[] m_matrix;
			m_matrix = nullptr;
		}
		else if (new_rows >= m_rows) {
			// освобождение динамической памяти
			for (auto i = 0; i < m_rows; i++) {
				delete m_matrix[i];
			}
			delete[] m_matrix;
			// создание матрицы заного
			m_matrix = { new Vector * [new_rows] {} };
			for (auto i = 0; i < m_rows; i++) {
				m_matrix[i] = new Vector(m_columns);	// создание вектора прошлого размера для 1 и его последующего масштабирования
				m_matrix[i]->resize(new_cols);			// уменьшение или расширение вектора (+ добавление 0, т.к размер больше)
			}
			for (auto i = m_rows; i < new_rows; i++) {
				m_matrix[i] = new Vector(0);			// создание пустого вектора, чтобы его заполнить нулями
				m_matrix[i]->resize(new_cols);			// заполнение нулями
			}	
		}
		else {	// (new_rows < m_rows)
			// изменение начальных векторов
			for (auto i = 0; i < new_rows; i++) {
				m_matrix[i]->resize(new_cols);				// изменение размеров векторов
			}
			// убираем те, которые выходят за новые границы
			for (auto i = new_rows; i < m_rows; i++) {
				delete m_matrix[i];
			}
		}
		m_rows = new_rows;
		m_columns = new_cols;
	}
	Matrix slice(size_t row_start, size_t row_end, size_t col_start, size_t col_end) {
		if (row_start >= m_rows || row_end >= m_rows) {
			cout << "Ошибка. Срез матрицы невозможно выполнить, т.к начало или конец СТРОКИ превосходят индекс последнего элемента." << endl;
			Matrix mtrx_return(0,0);
			return mtrx_return;
		}
		else if (col_start >= m_columns || col_end >= m_columns) {
			cout << "Ошибка. Срез матрицы невозможно выполнить, т.к начало или конец КОЛОНКИ превосходят индекс последнего элемента." << endl;
			Matrix mtrx_return(0, 0);
			return mtrx_return;
		}
		// если старт это конец, а конец - это начало	// СТРОКА
		if ((row_end - row_start) < 0) {
			row_start += row_end;
			row_end = row_start - row_end;
			row_start = row_start - row_end;
		}
		// если старт это конец, а конец - это начало	// КОЛОНКА
		if ((col_end - col_start) < 0) {
			col_start += col_end;
			col_end = col_start - col_end;
			col_start = col_start - col_end;
		}
		long cnt = 0;
		Matrix mtrx_return(0,0);
		delete[] mtrx_return.m_matrix;
		// заполнение возвращаемой матрицы данными из основной матрицы
		mtrx_return.m_rows = (row_end - row_start) + 1;
		mtrx_return.m_columns = (col_end - col_start) + 1;
		mtrx_return.m_matrix = { new Vector* [(row_end - row_start)+1] {} };
		for (auto i = row_start; i <= row_end; i++) {
			mtrx_return.m_matrix[cnt] = new Vector(m_matrix[i]->slice(col_start, col_end));
			cnt++;
		}
		// док-во что вектор создан
		//mtrx_return.getInfo();
		return mtrx_return;
	}
	long determinant() {	// рекурсивный детерминант
		if (m_rows != m_columns && (m_rows != 0 || m_columns != 0)) return 0; // только для квадратных матриц и не пустых
		else if (m_rows == 1) {
			return m_matrix[0]->getElement(0);
		}
		else if (m_rows == 2) {
			return ((m_matrix[0]->getElement(0)) * (m_matrix[1]->getElement(1))) - ((m_matrix[0]->getElement(1)) * (m_matrix[1]->getElement(0)));
		}
		else {
			long deter = 0;
			for (auto i = 0; i < m_columns; i++) {	// берем подопытный определитель - первую строчку матрицы
				// создаем новую матрицу с чуть меньшим размером (на -1)
				Matrix mx(0, 0);
				long IA = 0;	// счетчик
				mx.m_matrix = { new Vector * [m_rows - 1] {} };
				mx.m_rows = 2;
				mx.m_columns = 2;
				// заполняем новую матрицу числами, которые не стоят на пересечении
				for (auto j = 1; j < m_rows; j++) {									// цикл на число итераций = m_rows-1
					mx.m_matrix[IA] = new Vector(0);								// создание пустой строки в новой матрице
					for (auto k = 0; k < m_columns; k++) {
						if (k != i) mx.m_matrix[IA]->push_back((m_matrix[j]->getElement(k)));	// заполнение пустой строки числами, не стоящими на пересечении
					}
					IA++;
				}
				mx.getInfo();
				deter += pow((-1),i) * (m_matrix[0]->getElement(i)) * mx.determinant();	
			}
			return deter;
		}
	}
	pair<int, int> find(int value) {
		for (auto i = 0; i < m_rows; i++) {
			for (auto j = 0; j < m_columns; j++) {
				if (m_matrix[i]->getElement(j) == value) return pair<int, int>(i, j);
			}
		}
		return pair<int, int> (-1, -1);
	}
};