#ifndef SEM2LAB3_BINARY_TREE_ITERATOR_H
#define SEM2LAB3_BINARY_TREE_ITERATOR_H
#include <generator>

template<typename T>
class BinaryTree;

template<typename T>
std::generator<const T&> iterate(const BinaryTree<T>& tree);          // Обход по порядку ключа

// template<typename T>
// std::generator<const T&> iterate_reverse(const BinaryTree<T>& tree);                              // Обход в обратном порядке

#include "BinaryTreeIterator.tpp"

#endif
