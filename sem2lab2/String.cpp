#include "String.h"
#include <algorithm>
#include <cstdio>
#include <iterator>

// Выделение памяти под строку длины new_length
void String::allocate(int new_length)
{
    this->length = new_length;
    this->data = new char[this->length + 1];
}

bool String::is_a(char c)
{
    return c == 'a';
}

bool String::is_z(char c)
{
    return c == 'z';
}

// Ввод строки, повторяя попытку, пока она не влезет в MAX_LENGTH
void String::read_correctly(std::istream& stream)
{
    while (!(stream >> *this))
    {
        stream.clear();
        rewind(stdin);
    }
}

// Оператор присваивания
String& String::operator=(const String& other)
{
    if (this != &other)
    {
        delete[] this->data;
        allocate(other.length);
        std::copy(other.data, other.data + other.length + 1, this->data);
    }

    return *this;
}

// Удаление всех вхождений other из строки
String String::operator-(const String& other) const
{
    if (other.length == 0)
        return *this;

    const char* text_end = this->data + this->length;
    const char* pattern_begin = other.data;
    const char* pattern_end = other.data + other.length;

    String result(this->length);
    char* result_end = result.data;

    const char* current = this->data;
    const char* match;
    do
    {
        match = std::search(current, text_end, pattern_begin, pattern_end);
        result_end = std::copy(current, match, result_end);
        current = match + other.length;
    }
    while (match != text_end);
    *result_end = '\0';

    result.length = result_end - result.data;
    return result;
}

// Добавление other к строке
String& String::operator+=(const String& other)
{
    int new_length = this->length + other.length;
    char* new_data = new char[new_length + 1];

    std::copy(this->data, this->data + this->length, new_data);
    std::copy(other.data, other.data + other.length + 1, new_data + this->length);

    delete[] this->data;
    this->data = new_data;
    this->length = new_length;

    return *this;
}

// Увеличение последнего символа
String& String::operator++()
{
    std::reverse_iterator<char*> rbegin(this->data + this->length);
    std::reverse_iterator<char*> rend(this->data);

    auto it = std::find_if_not(rbegin, rend, is_z);  // первый (с конца) символ, не равный 'z'
    std::fill(rbegin, it, 'a');                      // все 'z' перед ним переносятся в 'a'

    if (it != rend)
        ++(*it);

    return *this;
}

String String::operator++(int)
{
    String old(*this);
    ++(*this);
    return old;
}

// Уменьшение последнего символа
String& String::operator--()
{
    std::reverse_iterator<char*> rbegin(this->data + this->length);
    std::reverse_iterator<char*> rend(this->data);

    auto it = std::find_if_not(rbegin, rend, is_a);  // первый (с конца) символ, не равный 'a'
    std::fill(rbegin, it, 'z');                      // все 'a' перед ним переносятся в 'z'

    if (it != rend)
        --(*it);

    return *this;
}

String String::operator--(int)
{
    String old(*this);
    --(*this);
    return old;
}

// Получение символа по индексу
char& String::operator[](int i)
{
    return this->data[i];
}

// Получение подстроки длины count с индекса from
String String::operator()(int from, int count) const
{
    String result(count);
    std::copy_n(this->data + from, count, result.data);
    result.data[count] = '\0';
    return result;
}


//void* String::operator new(size_t size)
//{
//    return ::operator new(size);
//}
//
//
//void String::operator delete(void* ptr)
//{
//    ::operator delete(ptr);
//}

// Сложение строк
String operator+(const String& a, const String& b)
{
    String result(a);
    result += b;
    return result;
}

String operator+(const String& a, const char* b)
{
    return a + String(b);
}

String operator+(const char* a, const String& b)
{
    return String(a) + b;
}

// Сравнение строк
bool operator<(const String& a, const String& b)
{
    return std::lexicographical_compare(a.data, a.data + a.length, b.data, b.data + b.length);
}

bool operator>(const String& a, const String& b)
{
    return b < a;
}

bool operator<=(const String& a, const String& b)
{
    return !(a > b);
}

bool operator>=(const String& a, const String& b)
{
    return !(a < b);
}

// Ввод строки
std::istream& operator>>(std::istream& stream, String& s)
{
    char buffer[MAX_LENGTH + 1];
    stream.getline(buffer, MAX_LENGTH + 1);

    if (stream)
        s = String(buffer);

    return stream;
}

// Вывод строки
std::ostream& operator<<(std::ostream& stream, const String& s)
{
    stream << s.data;
    return stream;
}
