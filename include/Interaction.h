#pragma once
#include "BinaryTree.h"
#include <iostream>

template<typename T>
class Interaction
{
private:
    BinaryTree<T>& tree;

    void print_table() const;                                     // Вывод таблицы
    void add_object();                                            // Ввод и добавление объекта
    void edit_object(int number);                                 // Изменение объекта
    void remove_object(int number);                               // Удаление объекта
    static void edit_field(T& object);                            // Выбор и ввод поля

public:
    explicit Interaction(BinaryTree<T>& tree) : tree(tree) {}

    void run(int action);                                         // Выполнение действия меню
};

#include "Interaction.tpp"
