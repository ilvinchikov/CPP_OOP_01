#include <iostream>
#include "Book.h"
#include "Vector.h"
#include "Matrix.h"
#include <Windows.h>
using namespace std;
int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    cout << " << SAMOSTOYATELNIY TASK >>" << endl;
    // task 1
    cout << "Task 1: " << endl;
    Book book1("Война и мир", "Лев Толстой", 1869); // вызывается - конструктор с параметрами
    book1.setPages(1225);
    book1.getDescription();  // Ожидаемый вывод: Название: Война и мир, Автор: Лев Толстой, Год: 1869, Страниц: 1225
    Book book2 = book1;  // Копирование: вызывается - конструктор копирования
    book2.getDescription();  // Ожидаемый вывод: Название: Война и мир, Автор: Лев Толстой, Год: 1869, Страниц: 1225
    // task 2
    cout << endl << "Task 2: " << endl;
    Vector v1(5);   // конструктор с параметрами
    Vector v2(5);
    Vector v3 = v1; // конструктор копирования
    v2 = v1;    // оператор присваивания копирования
    cout << "v1-sum:" << v1.sum() << endl;  // ожидаемый вывод: 5
    cout << "v2-sum:" << v2.sum() << endl;  // ожидаемый вывод: 5
    cout << "v3-sum:" << v3.sum() << endl;  // ожидаемый вывод: 5
    Vector v6(6);
    v6.getInfo();           // ожидаемый вывод: [1] [1] [1] [1] [1] [1] 
    //v2 = v6.slice(3, 4);         
    v2.getInfo();           // ожидаемый вывод: [1] [1]
    v6.resize(10);
    v6.getInfo();           // ожидаемый вывод: [1] [1] [1] [1] [1] [1] [0] [0] [0] [0]
    cout << "v6) Find 0. the index is:" << v6.find(0) << endl; // ожидаемый вывод: 6
    v6.resize(1);           
    v6.getInfo();           // ожидаемый вывод: [1]
    v6.resize(0);
    v6.getInfo();           // ожидаемый вывод: Vector empty;
    Vector v0(0);
    v0.push_back(10);
    v0.getInfo();           // ожидаемый вывод: [10]
    cout << "v0) Find 0. the index is:" << v0.find(0) << endl; // ожидаемый вывод: -1
    // task 3
    cout << endl << "Task 3: " << endl;
    Matrix mx1(3,3);    // конструктор с параметрами
    mx1.getInfo();          //ожидаемый вывод : [3]*[3]
    Matrix mx2 = mx1;   // конструктор копирования
    mx2.getInfo();          //ожидаемый вывод : [3]*[3]
    Matrix mx3(5, 5);
    mx3 = mx1;          // оператор присваивания копирования
    mx3.getInfo();          //ожидаемый вывод : [3]*[3]
    Matrix mx4(2, 2);
    mx1 = mx4;
    cout << "========Check-back=======" << endl;
    mx1.getInfo();          //ожидаемый вывод : [2]*[2]
    mx2.getInfo();          //ожидаемый вывод : [3]*[3]
    mx3.getInfo();          //ожидаемый вывод : [3]*[3]
    mx1.resize(8, 8);
    mx2.resize(2, 2);
    mx3.resize(0, 2);
    cout << "========Check-back 2=======" << endl;
    mx1.getInfo();          //ожидаемый вывод : [8]*[8]
    mx2.getInfo();          //ожидаемый вывод : [2]*[2]
    mx3.getInfo();          //ожидаемый вывод : empty;
    cout << "========Check-back 3=======" << endl;
    mx2 = mx1.slice(0, 7, 0, 2);
    mx2.getInfo();          //ожидаемый вывод : [8]*[3]
    cout << "========Check-back 4=======" << endl;
    mx4.resize(3, 3);       // матрица [1] [1] [0] / [1] [1] [0] / [0] [0] [0]
    mx4.getInfo();          // ожидаемый вывод : 0
    cout << "determinant: " << mx4.determinant() << endl;
    cout << "========Check-back 4=======" << endl;
    mx2.transpose();
    mx2.getInfo();          //ожидаемый вывод : [3]*[8]
    pair<int, int> pos = mx2.find(0);  // ожидаемый вывод : 0,2
    cout << "finding element at: (" << pos.first << ";" << pos.second << ")" << endl;
    cout << "====================== END ======================" << endl;
    system("pause");
    return 0;
}

// https://student-labs.kernel-dev.ru/C++_OOP/lab1.html