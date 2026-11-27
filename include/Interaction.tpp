#ifndef SEM2LAB3_INTERACTION_TPP
#define SEM2LAB3_INTERACTION_TPP
#include "Interaction.h"
#include "Input.h"
#include <iostream>

// Выполнение действия меню
template<typename T>
void Interaction<T>::run(int action)
{
    if (action == 1)
    {
        this->print_table();
        return;
    }

    if (action == 2)
        this->add_object();
    else
    {
        this->print_table();
        int count = this->tree.size();
        if (count == 0)
            return;

        std::cout << "Номер объекта ";
        // int number = input::read_int(std::cin, 0, count - 1, "номер объекта");
        int number = input::read_index(std::cin, count, "номер объекта");
        if (action == 3)
            this->edit_object(number);
        else
            this->remove_object(number);
    }

    std::cout << '\n';
    this->print_table();
}

// Вывод таблицы
template<typename T>
void Interaction<T>::print_table() const
{
    this->tree.print_header(std::cout);
    std::cout << this->tree;
}

// Ввод и добавление объекта
template<typename T>
void Interaction<T>::add_object()
{
    T* object = new T;
    try
    {
        std::cin >> *object;
        this->tree.add(object);
    }
    catch (...)
    {
        delete object;
        throw;
    }
}

// Изменение объекта
template<typename T>
void Interaction<T>::edit_object(int number)
{
    T* object = new T(this->tree[number]);
    BinaryTree<T>* original = nullptr;
    try
    {
        original = this->tree.find(*object);
        edit_field(*object);
        this->tree.add(object);
    }
    catch (...)
    {
        delete object;
        throw;
    }

    original->remove();
}

// Удаление объекта
template<typename T>
void Interaction<T>::remove_object(int number)
{
    T object = this->tree[number];
    this->tree.find(object)->remove();
}

#endif
