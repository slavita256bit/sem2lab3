#pragma once
#include <ranges>

// Обход по порядку ключа
template<typename T>
std::generator<const T&> iterate(const BinaryTree<T>& tree)
{
    if (tree.empty())
        co_return;

    if (tree.left)
        co_yield std::ranges::elements_of(iterate(*tree.left));

    co_yield *tree.value;

    if (tree.right)
        co_yield std::ranges::elements_of(iterate(*tree.right));
}

/*
// Обход в обратном порядке
template<typename T>
std::generator<const T&> iterate_reverse(const BinaryTree<T>& tree)
{
    if (tree.empty())
        co_return;

    if (tree.right)
        co_yield std::ranges::elements_of(iterate_reverse(*tree.right));

    co_yield *tree.value;

    if (tree.left)
        co_yield std::ranges::elements_of(iterate_reverse(*tree.left));
}
*/
