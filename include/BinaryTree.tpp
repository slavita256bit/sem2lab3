#pragma once
#include <format>
#include <ranges>
#include <utility>

// Добавление с передачей владения
template<typename T>
void BinaryTree<T>::add(T* object)
{
    if (!object)
        return;

    if (empty())
    {
        value = object;
        return;
    }

    BinaryTree*& node = *object < *value ? left : right;
    if (node)
        node->add(object);
    else
        node = new BinaryTree(object);
}

// Проверка непустого потомка
template<typename T>
bool BinaryTree<T>::has_child(const BinaryTree* child)
{
    return child && !child->empty();
}

// Поиск наименьшего узла
template<typename T>
BinaryTree<T>* BinaryTree<T>::find_smallest()
{
    BinaryTree* node = this;
    while (has_child(node->left))
        node = node->left;

    return node;
}

// Извлечение объекта текущего узла
template<typename T>
T* BinaryTree<T>::extract()
{
    if (empty())
        return nullptr;

    T* object = std::exchange(value, nullptr);
    bool has_left = has_child(left);
    bool has_right = has_child(right);
    if (has_left && has_right)
    {
        BinaryTree* smallest_right = right->find_smallest();
        value = smallest_right->extract();
    }
    else
    {
        BinaryTree* replacement = has_left ? left : (has_right ? right : nullptr);
        BinaryTree next;
        if (replacement)
            next.swap(*replacement);

        swap(next);
    }

    return object;
}

// Удаление элемента текущего узла
template<typename T>
bool BinaryTree<T>::remove()
{
    if (empty())
        return false;

    delete extract();

    return true;
}

// Поменять дваподдерева местами
template<typename T>
void BinaryTree<T>::swap(BinaryTree& other) noexcept
{
    std::swap(value, other.value);
    std::swap(left, other.left);
    std::swap(right, other.right);
}

// Копирование объекта по номеру строки
template<typename T>
T BinaryTree<T>::operator[](int number)
{
    auto objects = iterate(*this);

    return *std::ranges::next(objects.begin(), number - 1);
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

// Вывод шапки таблицы
template<typename T>
void BinaryTree<T>::print_header(std::ostream& stream) const
{
    if (empty())
        return;

    stream << std::format("{:<3}  ", "№");
    value->print_header(stream);
    stream << '\n';
}

// Вывод строк таблицы класса
template<typename T>
std::ostream& operator<<(std::ostream& stream, const BinaryTree<T>& tree)
{
    if (tree.empty())
    {
        stream << "Нет объектов для вывода.\n";
        return stream;
    }

    int number = 1;
    for (const T& object : iterate(tree))
        stream << std::format("{:<3}  ", number++) << object << '\n';

    return stream;
}

// Проверка пустого дерева
template<typename T>
bool BinaryTree<T>::empty() const
{
    return value == nullptr;
}

// Получение количества объектов
template<typename T>
int BinaryTree<T>::size() const
{
    return static_cast<int>(std::ranges::distance(iterate(*this)));
}

// Удаление объектов и поддеревьев
template<typename T>
void BinaryTree<T>::clear()
{
    delete left;
    delete right;
    delete value;
    value = nullptr;
    left = nullptr;
    right = nullptr;
}
