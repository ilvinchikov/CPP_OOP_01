#include <string>
#include <iostream>
#pragma once
using namespace std;
class Book
{
	string m_Title, m_Author;
	int m_Year, m_Pages;

public: 
	// ����������� c �����������
	Book(string Title, string Author, int Year) : m_Title(Title), m_Author(Author), m_Year(Year), m_Pages(0) {}
	// ����������� �����������
	Book(const Book& bk) : m_Title(bk.m_Title), m_Author(bk.m_Author), m_Year(bk.m_Year), m_Pages(bk.m_Pages) {}
	// �������� ������������ ����������� // https://ustimov.org/posts/21/
	Book& operator=(const Book& bk) {
		if (this == &bk) return *this;  // ������ �� ����������������
		// �����������
		m_Title = bk.m_Title;
		m_Author = bk.m_Author;
		m_Year = bk.m_Year;
		m_Pages = bk.m_Pages;
		return *this;
	}
	void setPages(int pages) {		// ������ ��������
		this->m_Pages = pages;
	}
	void getDescription() {		// �������� ��������
		cout << "Title: " + this->m_Title + "; Author: " + this->m_Author + "; Year: " + to_string(this->m_Year) + "; Pages: " + to_string(this->m_Pages) + "\n";
	}

};