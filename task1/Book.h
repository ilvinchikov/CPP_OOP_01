#include <string>
#include <iostream>
#pragma once
using namespace std;
class Book
{
	string m_Title, m_Author;
	int m_Year, m_Pages;

public: 
	// конструктор c параметрами
	Book(string Title, string Author, int Year) : m_Title(Title), m_Author(Author), m_Year(Year), m_Pages(0) {}
	// конструктор копирования
	Book(const Book& bk) : m_Title(bk.m_Title), m_Author(bk.m_Author), m_Year(bk.m_Year), m_Pages(bk.m_Pages) {}
	// оператор присваивания копирования // https://ustimov.org/posts/21/
	Book& operator=(const Book& bk) {
		if (this == &bk) return *this;  // Защита от самоприсваивания
		// Копирование
		m_Title = bk.m_Title;
		m_Author = bk.m_Author;
		m_Year = bk.m_Year;
		m_Pages = bk.m_Pages;
		return *this;
	}
	void setPages(int pages) {		// задаем страницы
		this->m_Pages = pages;
	}
	void getDescription() {		// получаем описание
		cout << "Title: " + this->m_Title + "; Author: " + this->m_Author + "; Year: " + to_string(this->m_Year) + "; Pages: " + to_string(this->m_Pages) + "\n";
	}

};