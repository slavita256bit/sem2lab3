#include "BinaryTree.h"
#include "DumpTruck.h"
#include "Bus.h"
#include "Trolleybus.h"
#include <format>
#include <stdexcept>
#include <utility>

// Добавление с передачей владения
template<typename T>
void BinaryTree<T>::add(T* object)
{
    if (!object)
        return;

    if (this->empty())
    {
        this->value = object;
        return;
    }

    BinaryTree*& node = *object < *this->value ? this->left : this->right;
    if (node)
        node->add(object);
    else
        node = new BinaryTree(object);
}

// Поиск наименьшего узла
template<typename T>
BinaryTree<T>* BinaryTree<T>::find_smallest()
{
    BinaryTree* node = this;
    while (node->left && !node->left->empty())
        node = node->left;

    return node;
}

// Извлечение объекта текущего узла
template<typename T>
T* BinaryTree<T>::extract()
{
    if (this->empty())
        return nullptr;

    T* object = std::exchange(this->value, nullptr);
    bool has_left = this->left && !this->left->empty();
    bool has_right = this->right && !this->right->empty();
    if (has_left && has_right)
    {
        BinaryTree* smallest_right = this->right->find_smallest();
        this->value = smallest_right->extract();
    }
    else
    {
        BinaryTree* replacement = has_left ? this->left : (has_right ? this->right : nullptr);
        T* next_value = nullptr;
        BinaryTree* next_left = nullptr;
        BinaryTree* next_right = nullptr;
        if (replacement)
        {
            next_value = std::exchange(replacement->value, nullptr);
            next_left = std::exchange(replacement->left, nullptr);
            next_right = std::exchange(replacement->right, nullptr);
        }

        this->clear();
        this->value = next_value;
        this->left = next_left;
        this->right = next_right;
    }

    return object;
}

// Удаление элемента текущего узла
template<typename T>
bool BinaryTree<T>::remove()
{
    if (this->empty())
        return false;

    delete this->extract();

    return true;
}

// Поиск узла по номеру строки
template<typename T>
BinaryTree<T>* BinaryTree<T>::find_number(int& number)
{
    if (this->empty())
        return nullptr;

    if (this->left)
    {
        if (auto* node = this->left->find_number(number))
            return node;
    }

    number--;
    if (number == 0)
        return this;

    return this->right ? this->right->find_number(number) : nullptr;
}

// Получение узла по номеру строки
template<typename T>
BinaryTree<T>* BinaryTree<T>::get_node(int number)
{
    return number > 0 ? this->find_number(number) : nullptr;
}

// Копирование объекта по номеру строки
template<typename T>
T BinaryTree<T>::operator[](int number)
{
    auto* node = this->get_node(number);
    if (!node)
        throw std::out_of_range("Нет объекта с таким номером.");

    return *node->value;
}

// Поиск объекта по всем полям
template<typename T>
BinaryTree<T>* BinaryTree<T>::find(const T& object)
{
    BinaryTree* node = this;
    while (node && !node->empty())
    {
        if (*node->value == object)
            return node;

        node = object < *node->value ? node->left : node->right;
    }

    return nullptr;
}

// Вывод строк таблицы
template<typename T>
void BinaryTree<T>::print_rows(std::ostream& stream, int& number) const
{
    if (this->empty())
        return;

    if (this->left)
        this->left->print_rows(stream, number);

    stream << std::format("{:<3}  ", number++) << *this->value << '\n';

    if (this->right)
        this->right->print_rows(stream, number);
}

// Вывод таблицы класса
template<typename T>
std::ostream& operator<<(std::ostream& stream, const BinaryTree<T>& tree)
{
    if (tree.empty())
    {
        stream << "Нет объектов для вывода.\n";
        return stream;
    }

    stream << std::format("{:<3}  ", "№");
    tree.value->print_header(stream);
    stream << '\n';
    int number = 1;
    tree.print_rows(stream, number);

    return stream;
}

// Проверка пустого дерева
template<typename T>
bool BinaryTree<T>::empty() const
{
    return this->value == nullptr;
}

// Удаление объектов и поддеревьев
template<typename T>
void BinaryTree<T>::clear()
{
    delete this->left;
    delete this->right;
    delete this->value;
    this->value = nullptr;
    this->left = nullptr;
    this->right = nullptr;
}

// Типы деревьев текущего проекта
template class BinaryTree<DumpTruck>;
template class BinaryTree<Bus>;
template class BinaryTree<Trolleybus>;

// Вывод деревьев текущего проекта
template std::ostream& operator<<(std::ostream& stream, const BinaryTree<DumpTruck>& tree);
template std::ostream& operator<<(std::ostream& stream, const BinaryTree<Bus>& tree);
template std::ostream& operator<<(std::ostream& stream, const BinaryTree<Trolleybus>& tree);
