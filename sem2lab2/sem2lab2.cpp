#include <cstdio>
#include <iostream>
#include <utility>
#include "String.h"

int main()
{
    setlocale(LC_ALL, "ru_RU.UTF-8");

    String a;
    String b;

    char action;
    do
    {
        std::cout << std::endl;
        std::cout << "a - Ввод A и B" << std::endl;
        std::cout << "o - Строковые операции: конкатенация, вычитание, A += B, B = A" << std::endl;
        std::cout << "r - Увеличение/уменьшение последнего символа A: ++A, A++, --A, A--" << std::endl;
        std::cout << "e - Извлечение: A[i], A(from, count)" << std::endl;
        std::cout << "m - Сравнение A и B" << std::endl;
        std::cout << "n - Конструкторы + new/delete" << std::endl;
        std::cout << "x - Выход" << std::endl;
        std::cout << "выберите действие: ";

        std::cin >> action;
        rewind(stdin);

        std::cout << std::endl;

        switch (action)
        {
        case 'a':
            std::cout << "введите A: ";
            std::cin >> a; 
            std::cin.clear();
            rewind(stdin);
            //a.read_correctly(std::cin);
            std::cout << "введите B: ";
            std::cin >> b;
            std::cin.clear();
            rewind(stdin);
            //b.read_correctly(std::cin);
            break;

        case 'o':
            std::cout << "\"BSUIR \" + A + B + \" FCSAN\" = " << ("BSUIR " + a + b + " FCSAN") << std::endl;
            std::cout << "A - B = " << (a - b) << std::endl;
            std::cout << "A += B -> " << (a += b) << std::endl;
            std::cout << "B = A -> " << (b = a) << std::endl;
            break;

        case 'r':
            cout << "++A -> " << ++a << " (A = " << a << ")" << std::endl;
            std::cout << "A++ -> " << a++ << " (A = " << a << ")" << std::endl;
            std::cout << "--A -> " << --a << " (A = " << a << ")" << std::endl;
            std::cout << "A-- -> " << a-- << " (A = " << a << ")" << std::endl;
            break;

        case 'e':
        {
            int index, from, count;

            std::cout << "Введите индекс i для A[i]: ";
            std::cin >> index;
            std::cout << "A[" << index << "] = " << a[index] << std::endl;

            std::cout << "Введите начальный индекс и длину подстроки для (): ";
            std::cin >> from >> count;
            std::cout << "A(" << from << ", " << count << ") = " << a(from, count) << std::endl;
            break;
        }

        case 'm':
            std::cout << "A < B: " << (a < b) << std::endl;
            std::cout << "A > B: " << (a > b) << std::endl;
            std::cout << "A <= B: " << (a <= b) << std::endl;
            std::cout << "A >= B: " << (a >= b) << std::endl;
            break;

        case 'n':
        {
            String a_copy;
            String* dynamic = new String(a);
            a_copy += a;

            std::cout << "Конструктор по умолчанию и += A -> \"" << a_copy << '"' << std::endl;
            std::cout << "Оператор new String(a) -> " << *dynamic << std::endl;

            String moved(std::move(a_copy));
            std::cout << "Конструктор перемещения -> " << moved << std::endl;

            delete dynamic;
            break;
        }

        case 'x':
            std::cout << "Выход" << std::endl;
            break;

        default:
            std::cout << "Неизвестное действие!" << std::endl;
            break;
        }

        std::cout << "A = " << a << std::endl;
        std::cout << "B = " << b << std::endl;
        std::cout << std::endl;
    }
    while (action != 'x');

    return 0;
}