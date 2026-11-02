#pragma once
/*
Лабораторная работа 4 | Шаблоны | Бинарное дерево

...

Итераторы
*/
#include <ostream>

template<typename T>
class BinaryTree;

template<typename T>
std::ostream& operator<<(std::ostream& stream, const BinaryTree<T>& tree);                          // Вывод таблицы класса

template<typename T>
class BinaryTree
{
private:
    T* value = nullptr;                                                                             // Объект, принадлежащий дереву
    BinaryTree* left = nullptr;                                                                     // Левое поддерево
    BinaryTree* right = nullptr;                                                                    // Правое поддерево

    T* extract();                                                                                   // Извлечение объекта текущего узла
    BinaryTree* get_node(int number);                                                               // Получение узла по номеру строки
    BinaryTree* find_number(int& number);                                                           // Поиск узла по номеру строки
    BinaryTree* find_smallest();                                                                    // Поиск наименьшего узла
    void print_rows(std::ostream& stream, int& number) const;                                       // Вывод строк таблицы

public:
    BinaryTree() = default;                                                                         // Создание пустого дерева
    explicit BinaryTree(T* object) : value(object) {}                                               // Создание дерева с одним объектом

    ~BinaryTree()                                                                                   // Очистка дерева
    {
        this->clear();
    }

    BinaryTree(const BinaryTree&) = delete;                                                         // Запрет копирования владения узлами
    BinaryTree& operator=(const BinaryTree&) = delete;                                              // Запрет копирования владения узлами

    bool empty() const;                                                                             // Проверка пустого дерева
    void add(T* object);                                                                            // Добавление с передачей владения
    T operator[](int number);                                                                       // Копирование объекта по номеру строки
    bool remove();                                                                                  // Удаление элемента текущего узла
    BinaryTree* find(const T& object);                                                              // Поиск объекта по всем полям
    void clear();                                                                                   // Удаление объектов и поддеревьев

    friend std::ostream& operator<< <T>(std::ostream& stream, const BinaryTree& tree);              // Вывод таблицы класса
};
