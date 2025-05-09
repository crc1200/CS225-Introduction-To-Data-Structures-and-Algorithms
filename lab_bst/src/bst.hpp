/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    auto f = find(root, key);
    if (f == NULL) {
        return 0;
    }
    return f -> value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    if (subtree == NULL || subtree -> key == key) {
        return subtree;
    }
    if (subtree -> key < key) {
        return find(subtree -> right, key);
    } else {
        return find(subtree -> left, key);
    }
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    insert(root,key,value);
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    Node *& loc = find(subtree, key);
    if (loc == NULL) {
        loc = new Node(key, value);
    }
}
template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second) {

    K sKey = second -> key;
    V sValue = second -> value;
    
    second -> key = first -> key;
    second -> value = first -> value;
    
    first -> key = sKey;
    first -> value = sValue;
   
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key) {
    Node *& toRemove = find(subtree, key);
    //two child
    if (toRemove -> left != NULL && toRemove -> right != NULL) {     
        //using IOP
        Node * iop = toRemove -> left;
        while (iop -> right != NULL) {
            iop = iop -> right;
        }  
        toRemove -> value = iop -> value;
        toRemove -> key = iop -> key;
        remove(toRemove -> left, iop -> key);
    } else {
        auto tmp = toRemove;
        if (toRemove -> left != NULL) {
            toRemove = toRemove -> left;
        } else {
            toRemove = toRemove -> right;
        }
        delete tmp;
        tmp = NULL;
    }
}
        

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    BST<K, V> res;
    for (std::pair pair : inList) {
        res.insert(pair.first, pair.second);
    }
    return res;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    sort(inList.begin(),inList.end());
    std::vector<int> res(inList.size());
    BST<K, V> x = listBuild(inList);
    int sHeight = x.height();
    res[sHeight] += 1;
    while (next_permutation(inList.begin(), inList.end())) {
        BST<K, V> r = listBuild(inList);
        res[r.height()] += 1;
    }
    

    return res;
}