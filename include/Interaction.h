#pragma once
#include "BinaryTree.h"

class Vehicle;

namespace interaction
{
    void edit_field(Vehicle& object);                                                               // Выбор и ввод поля
}

template<typename T>
class Interaction
{
private:
    BinaryTree<T>& tree;

    void print_table() const;                                     // Вывод таблицы
    void add_object();                                            // Ввод и добавление объекта
    void edit_object(int number);                                 // Изменение объекта
    void remove_object(int number);                               // Удаление объекта

public:
    explicit Interaction(BinaryTree<T>& tree) : tree(tree) {}

    void run(int action);                                         // Выполнение действия меню
};

#include "Interaction.tpp"
