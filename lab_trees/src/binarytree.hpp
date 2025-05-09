/**
 * @file binarytree.hpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "InorderTraversal.h"
#include <iostream>
#include <vector>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy)
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    mirrorHelp(root);
}

template <typename T>
void BinaryTree<T>::mirrorHelp(Node* root) {
    if (root == NULL) {
        return;
    }

    Node* tmp = root -> left;
    root -> left = root -> right;
    root -> right = tmp;

    mirrorHelp(root -> left);
    mirrorHelp(root -> right);
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    std::vector<T> res;
    std::stack<typename BinaryTree<T>::Node*> stack;
    Node * curr = root;
    stack.push(curr);
    curr = curr -> left;
    while (curr != NULL && !stack.empty()) {
        while (curr != NULL) {
            stack.push(curr);
            curr = curr -> left;
        }
        if (curr == NULL and !stack.empty()) {
            auto s = stack.top() -> elem;
            res.push_back(s);
            curr = stack.top() -> right;
            stack.pop();
        }
    }
    for (unsigned i = 1; i < res.size(); i++) {
        if (res[i] < res[i - 1]) {
            return false;
        }
    }
    return res.size() != 1;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const{
    // your code here
    std::vector<T> res;
    recursiveHelp(root, res);
    for (unsigned i = 1; i < res.size(); i++) {
        if (res[i] < res[i - 1]) {
            return false;
        }
    }
    return true;

}

template <typename T>
void BinaryTree<T>::recursiveHelp(Node * root, std::vector<T> &vals) const{
    if (root == NULL) {
        return;
    }
    recursiveHelp(root -> left, vals);
    vals.push_back(root -> elem);
    recursiveHelp(root -> right, vals);
}

