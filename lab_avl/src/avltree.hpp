/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

#include <algorithm>

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}


template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    Node * y = t -> right;
    t -> right = y -> left;
    y -> left = t;
    t = y;
    t -> height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * y = t -> left;
    t -> left = y -> right;
    y -> right = t;
    t = y;
    t -> height = std::max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;

}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree) {
    if (subtree == NULL) {
        return;
    }
    int balance = heightOrNeg1(subtree -> right) - heightOrNeg1(subtree -> left);
    if (balance == -2) { // left is larger
        int l_balance = heightOrNeg1(subtree -> left -> right) - heightOrNeg1(subtree -> left ->left);
        if (l_balance == -1) {
            rotateRight(subtree);
        } else {
            rotateLeftRight(subtree);
        }
        subtree -> right -> height = std::max(heightOrNeg1(subtree->left -> left), heightOrNeg1(subtree -> left -> right)) + 1;
    } else if (balance == 2) {  //right is larger
        int r_balance = heightOrNeg1(subtree -> right -> right) - heightOrNeg1(subtree -> right ->left);
        if (r_balance == 1) {
            rotateLeft(subtree);
        } else {
            rotateRightLeft(subtree);
        }
        subtree -> left -> height = std::max(heightOrNeg1(subtree->right -> left), heightOrNeg1(subtree -> right -> right)) + 1;
    } 
    subtree -> height = std::max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right)) + 1;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (subtree == NULL) {
        subtree = new Node(key, value);
    } else if (key < subtree -> key) {
        insert(subtree -> left, key, value);
    } else {
        insert(subtree -> right, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key) {
    if (subtree == NULL)
        return;
    if (key < subtree->key) {
        remove(subtree -> left, key);
    } else if (key > subtree->key) {
        remove(subtree -> right, key);
    } else {
        if (subtree -> left != NULL && subtree -> right != NULL) {     
        Node * iop = subtree -> left;
        while (iop -> right != NULL) {
            iop = iop -> right;
        }  
        subtree -> value = iop -> value;
        subtree -> key = iop -> key;
        remove(subtree -> left, iop -> key);
    } else {
        auto tmp = subtree;
        if (subtree -> left != NULL) {
            subtree = subtree -> left;
        } else {
            subtree = subtree -> right;
        }
        delete tmp;
        tmp = NULL;
        }
    }
    rebalance(subtree);
}






