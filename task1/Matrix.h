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
	// ������. � �����.
	Matrix(size_t rows, size_t columns) : m_rows(rows), m_columns(columns) {
		if (rows > 0 && columns > 0) {
			m_matrix = { new Vector* [rows] {} };
			for (auto i = 0; i < rows; i++) {
				m_matrix[i] = new Vector(columns);
			}
		}
		else m_matrix = nullptr;
	}
	// ������. �����. ????
	Matrix(const Matrix& mx) : m_rows(mx.m_rows), m_columns(mx.m_columns) {
		m_matrix = new Vector* [mx.m_rows];
		for (auto i = 0; i < m_rows; i++) {
			// �������� �������
			m_matrix[i] = new Vector(mx.m_columns);
			*m_matrix[i] = *mx.m_matrix[i];	// ����. ������� �������� � �������
		}
	}
	// ������. �������.
	Matrix(Matrix&& mx) noexcept : m_rows(mx.m_rows), m_columns(mx.m_columns), m_matrix(mx.m_matrix) {
		mx.m_matrix = nullptr;
		mx.m_rows = 0;
		mx.m_columns = 0;
	}
	// ����. �����. �����.
	Matrix& operator=(const Matrix& mx) {
		if (this == &mx) return *this;  // ������ �� ����������������
		// �������� ������ ������
		for (auto i = 0; i < m_rows; i++) {
			delete m_matrix[i];
		}
		delete[] m_matrix;
		// �����������
		m_rows = mx.m_rows;
		m_columns = mx.m_columns;
		m_matrix = new Vector*[mx.m_rows];
		for (auto i = 0; i < m_rows; i++) {
			// �������� �������
			m_matrix[i] = new Vector(mx.m_columns);
			*m_matrix[i] = *mx.m_matrix[i];
		}
		return *this;
	}
	// ����. �����. �������.
	Matrix& operator=(Matrix&& mx) noexcept {
		if (this == &mx) return *this;
		// �������� ������ ������
		for (auto i = 0; i < m_rows; i++) {
			delete m_matrix[i];
		}
		delete[] m_matrix;
		// ����������� ������
		m_matrix = mx.m_matrix;  
		m_rows = mx.m_rows;
		m_columns = mx.m_columns;
		// ������� �������� ������
		mx.m_matrix = nullptr;
		mx.m_rows = 0;
		mx.m_columns = 0;
		return *this;
	}
	// ����������
	~Matrix() {
		// ������������ ������������ ������
		for (auto i = 0; i < m_rows; i++) {
			delete m_matrix[i];
		}
		delete[] m_matrix;
		m_matrix = nullptr;
		cout << "������� ���������������." << endl;
	}
	void transpose() {
		// �������� ��������� �������
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
		// ������������ ������������ ������
		for (auto i = 0; i < m_rows; i++) {
			delete m_matrix[i];
		}
		delete[] m_matrix;
		// ������� ��������� ������� � ��������
		m_matrix = temp_mtrx.m_matrix;	// ������� ��������� �� �������
		m_rows += m_columns;			// ������ ������� � ������ ������� � ���������
		m_columns = m_rows - m_columns;
		m_rows = m_rows - m_columns;
		temp_mtrx.m_matrix = nullptr;	// ����������� �� ��������� ��������� �������, �.� �������� ��������� ��� ��������� �� ��������� �������.
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
		if (new_rows == m_rows && new_cols == m_columns) return;	// ���� ������
		else if (new_rows == 0 || new_cols == 0) {
			// ������������ ������������ ������
			for (auto i = 0; i < m_rows; i++) {
				delete m_matrix[i];
			}
			delete[] m_matrix;
			m_matrix = nullptr;
		}
		else if (new_rows >= m_rows) {
			// ������������ ������������ ������
			for (auto i = 0; i < m_rows; i++) {
				delete m_matrix[i];
			}
			delete[] m_matrix;
			// �������� ������� ������
			m_matrix = { new Vector * [new_rows] {} };
			for (auto i = 0; i < m_rows; i++) {
				m_matrix[i] = new Vector(m_columns);	// �������� ������� �������� ������� ��� 1 � ��� ������������ ���������������
				m_matrix[i]->resize(new_cols);			// ���������� ��� ���������� ������� (+ ���������� 0, �.� ������ ������)
			}
			for (auto i = m_rows; i < new_rows; i++) {
				m_matrix[i] = new Vector(0);			// �������� ������� �������, ����� ��� ��������� ������
				m_matrix[i]->resize(new_cols);			// ���������� ������
			}	
		}
		else {	// (new_rows < m_rows)
			// ��������� ��������� ��������
			for (auto i = 0; i < new_rows; i++) {
				m_matrix[i]->resize(new_cols);				// ��������� �������� ��������
			}
			// ������� ��, ������� ������� �� ����� �������
			for (auto i = new_rows; i < m_rows; i++) {
				delete m_matrix[i];
			}
		}
		m_rows = new_rows;
		m_columns = new_cols;
	}
	Matrix slice(size_t row_start, size_t row_end, size_t col_start, size_t col_end) {
		if (row_start >= m_rows || row_end >= m_rows) {
			cout << "������. ���� ������� ���������� ���������, �.� ������ ��� ����� ������ ����������� ������ ���������� ��������." << endl;
			Matrix mtrx_return(0,0);
			return mtrx_return;
		}
		else if (col_start >= m_columns || col_end >= m_columns) {
			cout << "������. ���� ������� ���������� ���������, �.� ������ ��� ����� ������� ����������� ������ ���������� ��������." << endl;
			Matrix mtrx_return(0, 0);
			return mtrx_return;
		}
		// ���� ����� ��� �����, � ����� - ��� ������	// ������
		if ((row_end - row_start) < 0) {
			row_start += row_end;
			row_end = row_start - row_end;
			row_start = row_start - row_end;
		}
		// ���� ����� ��� �����, � ����� - ��� ������	// �������
		if ((col_end - col_start) < 0) {
			col_start += col_end;
			col_end = col_start - col_end;
			col_start = col_start - col_end;
		}
		long cnt = 0;
		Matrix mtrx_return(0,0);
		delete[] mtrx_return.m_matrix;
		// ���������� ������������ ������� ������� �� �������� �������
		mtrx_return.m_rows = (row_end - row_start) + 1;
		mtrx_return.m_columns = (col_end - col_start) + 1;
		mtrx_return.m_matrix = { new Vector* [(row_end - row_start)+1] {} };
		for (auto i = row_start; i <= row_end; i++) {
			mtrx_return.m_matrix[cnt] = new Vector(m_matrix[i]->slice(col_start, col_end));
			cnt++;
		}
		// ���-�� ��� ������ ������
		//mtrx_return.getInfo();
		return mtrx_return;
	}
	long determinant() {	// ����������� �����������
		if (m_rows != m_columns && (m_rows != 0 || m_columns != 0)) return 0; // ������ ��� ���������� ������ � �� ������
		else if (m_rows == 1) {
			return m_matrix[0]->getElement(0);
		}
		else if (m_rows == 2) {
			return ((m_matrix[0]->getElement(0)) * (m_matrix[1]->getElement(1))) - ((m_matrix[0]->getElement(1)) * (m_matrix[1]->getElement(0)));
		}
		else {
			long deter = 0;
			for (auto i = 0; i < m_columns; i++) {	// ����� ���������� ������������ - ������ ������� �������
				// ������� ����� ������� � ���� ������� �������� (�� -1)
				Matrix mx(0, 0);
				long IA = 0;	// �������
				mx.m_matrix = { new Vector * [m_rows - 1] {} };
				mx.m_rows = 2;
				mx.m_columns = 2;
				// ��������� ����� ������� �������, ������� �� ����� �� �����������
				for (auto j = 1; j < m_rows; j++) {									// ���� �� ����� �������� = m_rows-1
					mx.m_matrix[IA] = new Vector(0);								// �������� ������ ������ � ����� �������
					for (auto k = 0; k < m_columns; k++) {
						if (k != i) mx.m_matrix[IA]->push_back((m_matrix[j]->getElement(k)));	// ���������� ������ ������ �������, �� �������� �� �����������
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