#ifndef SEM2LAB3_BINARY_TREE_H
#define SEM2LAB3_BINARY_TREE_H
/*
Лабораторная работа 4 | Шаблоны | Бинарное дерево

...

Итераторы
*/
#include "BinaryTreeIterator.h"
#include <ostream>

template<typename T>
class BinaryTree;

template<typename T>
std::ostream& operator<<(std::ostream& stream, const BinaryTree<T>& tree);        // Вывод таблицы класса

template<typename T>
class BinaryTree
{
private:
    T* value = nullptr;                                          // Объект, принадлежащий дереву
    BinaryTree* left = nullptr;                                  // Левое поддерево
    BinaryTree* right = nullptr;                                 // Правое поддерево

    static bool has_child(const BinaryTree* child);              // Проверка непустого потомка

    T* extract();                                                // Извлечение объекта текущего узла
    void swap(BinaryTree& other) noexcept;                       // Поменять два поддерева местами
    BinaryTree* find_smallest();                                 // Поиск наименьшего узла
    BinaryTree*& get_target_child(const T& object);              // Выбор ветви по ключу
    BinaryTree* insertion_node(const T& object);                 // Поиск места для вставки

public:
    BinaryTree() = default;                               // Создание пустого дерева
    explicit BinaryTree(T* object) : value(object) {}     // Создание дерева с одним объектом

    ~BinaryTree()                                         // Очистка дерева
    {
        clear();
    }

    BinaryTree(const BinaryTree&) = delete;
    BinaryTree& operator=(const BinaryTree&) = delete;

    bool empty() const;                                  // Проверка пустого дерева
    int size() const;                                    // Получение количества объектов
    void add(T* object);                                 // Передача владения при успешном добавлении
    void add(const T& object);                           // Добавление копии объекта
    T operator[](int number);                            // Копирование объекта по номеру строки
    bool remove();                                       // Удаление элемента текущего узла
    BinaryTree* find(const T& object);                   // Поиск объекта по всем полям
    void clear();                                        // Удаление объектов и поддеревьев
    void print_header(std::ostream& stream) const;       // Вывод шапки таблицы

    friend std::generator<const T&> iterate<T>(const BinaryTree& tree);                // Обход по порядку ключа
    // friend std::generator<const T&> iterate_reverse<T>(const BinaryTree& tree);     // Обход в обратном порядке
    friend std::ostream& operator<< <T>(std::ostream& stream, const BinaryTree& tree); // Вывод таблицы класса
};

#include "BinaryTree.tpp"

#endif
