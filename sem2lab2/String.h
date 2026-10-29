#pragma once
#include <iostream>
#include <algorithm>

/*
Лабораторная работа 2 | Перегрузка операций

Реализовать класс String для работы со строками символов

конструктор без параметров
конструктор с параметрами
конструктор копирования

Перегрузить операции:
оператор присваивания
+ конкатенация строк (3 перегрузки: String+String, String + const char*, const char* + String)
- вычитание строк 
+= добавление к строке строки
++ увеличение последнего символа
-- уменьшение последнего символа
< 
> 
>=
<=
[] взятие индекса class method
()(int, int) выделение подстроки из строки 
<< >> перегрузка ввода/вывода 


Пример: d = "БГУИР" + a + b + c + "ФКСИС", где a, b, c - объекты String
=> отдельно const + объект, объект + const и объект + объект
*/

#define MAX_LENGTH 80

class String
{
private:
    int length = 0;
    char* data = nullptr;

    void allocate(int new_length);                    // Выделение памяти под строку длины new_length

    static bool is_a(char c);                         // Проверка символа на 'a' (для переноса в operator--)
    static bool is_z(char c);                         // Проверка символа на 'z' (для переноса в operator++)

public:
    String() : String("") {}                          // Конструктор без параметров
    explicit String(const char* str)                  // Конструктор с параметром
    {
        const char* end = std::find(str, str + MAX_LENGTH, '\0');
        int new_length = end - str;

        allocate(new_length);
        std::copy(str, str + new_length + 1, this->data);
    }
    explicit String(int new_length)                  // Конструктор пустой строки заданной длины
    {
        allocate(new_length);
    }
    String(const String& copy) : String(copy.data) {} // Конструктор копирования
    String(String&& other) noexcept                   // Конструктор перемещения
    {
        this->length = other.length;
        this->data = other.data;
        other.length = 0;
        other.data = nullptr;
    }

    String& operator=(const String& other);           // Оператор присваивания

    String operator-(const String& other) const;      // Удаление всех вхождений other из строки
    String& operator+=(const String& other);          // Добавление other к строке

    String& operator++();                             // Увеличение последнего символа
    String operator++(int);
    String& operator--();                             // Уменьшение последнего символа
    String operator--(int);

    char& operator[](int i);                          // Получение символа по индексу
    String operator()(int from, int count) const;     // Получение подстроки длины count с индекса from

    void read_correctly(std::istream& stream);        // Ввод строки, повторяя попытку, пока она не влезет в MAX_LENGTH

    //void* operator new(size_t size);                  
    //void operator delete(void* ptr);                  

    ~String()
    {
        delete[] this->data;
    }

    friend String operator+(const String& a, const String& b); // Сложение строк
    friend String operator+(const String& a, const char* b);
    //friend String operator+(const String& a, char b);
    friend String operator+(const char* a, const String& b);

    friend bool operator<(const String& a, const String& b);   // Сравнение строк
    friend bool operator>(const String& a, const String& b);
    friend bool operator<=(const String& a, const String& b);
    friend bool operator>=(const String& a, const String& b);

    friend std::istream& operator>>(std::istream& stream, String& s);       // Ввод строки
    friend std::ostream& operator<<(std::ostream& stream, const String& s); // Вывод строки
};
