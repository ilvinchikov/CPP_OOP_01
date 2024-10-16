#pragma once
#include <iostream>
using namespace std;
class Vector
{
	size_t m_size;	// size
	long* m_ArrVec;	// array (vector)
public:
	// ����������� c �����������
	Vector(size_t Size) : m_size(Size) {
		if (Size > 0) {
			m_ArrVec = { new long[Size] {} }; // long* ArrVec = { new long[Size] {} }; - ������ (����): ArrVec �������� ����� ���������� ������������ + ������ ������.
			for (auto i = 0; i < Size; i++) {
				m_ArrVec[i] = 1;
			}
		}
		else m_ArrVec = nullptr;
	}
	// ����������� �����������
	Vector(const Vector& vc) : m_size(vc.m_size) {
		m_ArrVec = new long[m_size];
		if (m_ArrVec != nullptr) {
			for(auto i=0; i<vc.m_size; i++) {
				m_ArrVec[i] = vc.m_ArrVec[i];
			}
		}
	}
	// ����������� �����������
	Vector(Vector&& vc) noexcept : m_size(vc.m_size), m_ArrVec(vc.m_ArrVec) {
		vc.m_ArrVec = nullptr;	// m_ArrVec ������ ������ ������ �����
		vc.m_size = 0;
	}
	// �������� ������������ �����������
	Vector& operator=(const Vector& vc) {
		if (this == &vc) return *this;  // ������ �� ����������������
		delete[] m_ArrVec;
		// �����������
		m_size = vc.m_size;
		if (vc.m_size > 0) {
			m_ArrVec = new long[vc.m_size];
			for (auto i = 0; i < m_size; i++) {
				m_ArrVec[i] = vc.m_ArrVec[i];
			}
		}
		else m_ArrVec = nullptr;
		return *this;
	}
	// �������� ������������ �����������
	Vector& operator=(Vector&& vc) noexcept {
		if (this == &vc) return *this;
		delete[] m_ArrVec;  // ������� ���������� ������
		m_ArrVec = vc.m_ArrVec;  // ����������� ������
		m_size = vc.m_size;
		vc.m_ArrVec = nullptr;  // ������� �������� ������
		vc.m_size = 0;
		return *this;
	}
	// ����������
	~Vector() {
		cout << "--[dev: vec_deleted]:" << endl;
		getInfo();
		delete[] m_ArrVec;  // ������������ ������������ ������
		cout << "������ �������������." << endl;
	}
	void getInfo() {
		cout << "Size of vector: " << m_size << endl << "Vector: ";
		if (m_size > 0) {
			for (auto i = 0; i < m_size; i++) {
				cout << "[" << m_ArrVec[i] << "] ";
			}
		}
		else cout << "empty;";
		cout << endl;
	}
	// ����� ���� ��������� �������
	long sum() {
		long answ_sum = 0;
		if (m_size > 0) {
			for (auto i = 0; i < m_size; i++) {
				answ_sum += m_ArrVec[i];
			}
		}
		return answ_sum;
	}
	// ��������� ������� �������
	void resize(size_t new_size) {
		if (new_size == m_size) return;	// ���� ������
		else if (m_size == 0) {
			delete[] m_ArrVec;
			m_ArrVec = { new long[new_size] {} };
			for (auto i = 0; i < new_size; i++) {
				m_ArrVec[i] = 0;
			}
		}
		else if (new_size == 0) {
			delete[] m_ArrVec;
			m_ArrVec = nullptr;
		}
		else {
			long* temp_Arr = { new long[m_size] {} };
			for (auto i = 0; i < m_size; i++) {
				temp_Arr[i] = m_ArrVec[i];
			}
			delete[] m_ArrVec;
			m_ArrVec = { new long[new_size] {} };
			if (m_size < new_size) {
				for (auto i = 0; i < m_size; i++) {
					m_ArrVec[i] = temp_Arr[i];
				}
				for (auto i = m_size; i < new_size; i++) {
					m_ArrVec[i] = 0;
				}
			}
			else {
				for (auto i = 0; i < new_size; i++) {
					m_ArrVec[i] = temp_Arr[i];
				}
			}
			delete[] temp_Arr;
		}
		m_size = new_size;
	}
	// ���� �������
	Vector slice(size_t start, size_t end) {
		if (start >= m_size || end >= m_size) {
			cout << "������. ���� ������� ���������� ���������, �.� ������ ��� ����� ����������� ������ ���������� ��������." << endl;
			Vector vec_return(0);
			return vec_return;
		}
		// ���� ����� ��� �����, � ����� - ��� ������
		else if ((end - start) < 0) {
			start += end;
			end = start - end;
			start = start - end;
		}
		long cnt = 0;
		Vector vec_return((end - start) + 1);
		for (auto i = start; i <= end; i++) {
			vec_return.m_ArrVec[cnt] = m_ArrVec[i];
			cnt++;
		}
		// ���-�� ��� ������ ������
		//vec_return.getInfo();
		return vec_return;
	}
	// ���������� � �����
	void push_back(int value) {
		long* temp_Arr = { new long[m_size+1] {} };
		for (auto i = 0; i < m_size; i++) {
			temp_Arr[i] = m_ArrVec[i];
		}
		temp_Arr[m_size] = value;
		delete[] m_ArrVec;
		
		m_ArrVec = { new long[m_size + 1] {} };
		for (auto i = 0; i < m_size+1; i++) {
			m_ArrVec[i] = temp_Arr[i];
		}
		delete[] temp_Arr;
		m_size += 1;	
	}
	long find(int value) {
		for (auto i = 0; i < m_size; i++) {
			if (m_ArrVec[i] == value) return i;
		}
		return -1;
	}
	long getElement(long index) {
		return m_ArrVec[index];
	}
};