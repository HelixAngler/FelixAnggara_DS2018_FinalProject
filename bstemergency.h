#ifndef AVLTREE
#define AVLTREE
#include <algorithm>
#include <iostream>
#include <string>
/* credit for Rosetta Code */
/* AVL node */
using namespace std;
template <class T>
class AVLnode {
public:
    T key;
    int balance;
    AVLnode *left, *right, *parent;

    AVLnode(T k, AVLnode *p) : key(k), balance(0), parent(p),
                        left(NULL), right(NULL) {}

    ~AVLnode() {
        delete left;
        delete right;
    }
};

/* AVL tree */
template <class T>
class AVLtree {
public:
    AVLtree(void);
    AVLtree(T key);
    ~AVLtree(void);
    bool insert(T key);
    void deleteKey(const T &key);
    void printBalance();
    T findin(const T &key);
    bool check(const T &key);
    void inorder();
private:
    void inordering(AVLnode<T> *temp);
    bool checking (const T &key, AVLnode<T> *traverse);
    T searchfor(const T &key, AVLnode<T> *traverse);
    AVLnode<T> *root = NULL;
    AVLnode<T>* rotateLeft          ( AVLnode<T> *a );
    AVLnode<T>* rotateRight         ( AVLnode<T> *a );
    AVLnode<T>* rotateLeftThenRight ( AVLnode<T> *n );
    AVLnode<T>* rotateRightThenLeft ( AVLnode<T> *n );
    void rebalance                  ( AVLnode<T> *n );
    int height                      ( AVLnode<T> *n );
    void setBalance                 ( AVLnode<T> *n );
    void printBalance               ( AVLnode<T> *n );
    void clearNode                  ( AVLnode<T> *n );
};

/* AVL class definition */
//balancing method
template <class T>
void AVLtree<T>::rebalance(AVLnode<T> *n) {
    setBalance(n);

    if (n->balance == -2) {
        if (height(n->left->left) >= height(n->left->right))
            n = rotateRight(n);
        else
            n = rotateLeftThenRight(n);
    }
    else if (n->balance == 2) {
        if (height(n->right->right) >= height(n->right->left))
            n = rotateLeft(n);
        else
            n = rotateRightThenLeft(n);
    }

    if (n->parent != NULL) {
        rebalance(n->parent);
    }
    else {
        root = n;
    }
}
//left rotation method
template <class T>
AVLnode<T>* AVLtree<T>::rotateLeft(AVLnode<T> *a) {
    AVLnode<T> *b = a->right;
    b->parent = a->parent;
    a->right = b->left;

    if (a->right != NULL)
        a->right->parent = a;

    b->left = a;
    a->parent = b;

    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}
//right rotation method
template <class T>
AVLnode<T>* AVLtree<T>::rotateRight(AVLnode<T> *a) {
    AVLnode<T> *b = a->left;
    b->parent = a->parent;
    a->left = b->right;

    if (a->left != NULL)
        a->left->parent = a;

    b->right = a;
    a->parent = b;

    if (b->parent != NULL) {
        if (b->parent->right == a) {
            b->parent->right = b;
        }
        else {
            b->parent->left = b;
        }
    }

    setBalance(a);
    setBalance(b);
    return b;
}
//left right rotation method
template <class T>
AVLnode<T>* AVLtree<T>::rotateLeftThenRight(AVLnode<T> *n) {
    n->left = rotateLeft(n->left);
    return rotateRight(n);
}
//right left rotation method
template <class T>
AVLnode<T>* AVLtree<T>::rotateRightThenLeft(AVLnode<T> *n) {
    n->right = rotateRight(n->right);
    return rotateLeft(n);
}
//height method
template <class T>
int AVLtree<T>::height(AVLnode<T> *n) {
    if (n == NULL)
        return -1;
    return 1 + std::max(height(n->left), height(n->right));
}
//set balance method
template <class T>
void AVLtree<T>::setBalance(AVLnode<T> *n) {
    n->balance = height(n->right) - height(n->left);
}
//print balance method
template <class T>
void AVLtree<T>::printBalance(AVLnode<T> *n) {
    if (n != NULL) {
        printBalance(n->left);
        std::cout << n->balance << " ";
        printBalance(n->right);
    }
}
//constructor
template <class T>
AVLtree<T>::AVLtree(void) : root(NULL) {}
//constructor with insert value (my own addition)
template <class T>
AVLtree<T>::AVLtree(T key) : root(NULL) {
    bool k = this->insert(key);
}
//destructor
template <class T>
AVLtree<T>::~AVLtree(void) {
    delete root;
}
//insert method
template <class T>
bool AVLtree<T>::insert(T key) {
    if (root == NULL) {
        root = new AVLnode<T>(key, NULL);
    }
    else {
        AVLnode<T>
            *n = root,
            *parent;

        while (true) {
            if (n->key == key)
                return false;

            parent = n;

            bool goLeft = n->key > key;
            n = goLeft ? n->left : n->right;

            if (n == NULL) {
                if (goLeft) {
                    parent->left = new AVLnode<T>(key, parent);
                }
                else {
                    parent->right = new AVLnode<T>(key, parent);
                }

                rebalance(parent);
                break;
            }
        }
    }

    return true;
}
//delete method
template <class T>
void AVLtree<T>::deleteKey(const T &delKey) {
    if (root == NULL)
        return;

    AVLnode<T>
        *n       = root,
        *parent  = root,
        *delNode = NULL,
        *child   = root;

    while (child != NULL) {
        parent = n;
        n = child;
        child = delKey >= n->key ? n->right : n->left;
        if (delKey == n->key)
            delNode = n;
    }

    if (delNode != NULL) {
        delNode->key = n->key;

        child = n->left != NULL ? n->left : n->right;

        if (root->key == delKey) {
            root = child;
        }
        else {
            if (parent->left == n) {
                parent->left = child;
            }
            else {
                parent->right = child;
            }

            rebalance(parent);
        }
    }
}
//my own implementation
//retrieval method
template<class T>
T AVLtree<T>::findin(const T &key){
    return this->searchfor(key, this->root);
}
template<class T>
T AVLtree<T>::searchfor(const T &key, AVLnode<T> *traverse){
    T result;
    if(traverse != nullptr){
        if(traverse->key == key){
            result = traverse->key;
        }
        else if(key < traverse->key){
            result = this->searchfor(key,traverse->left);
        }
        else if(key > traverse->key){
            result = this->searchfor(key,traverse->right);
        }
    }
    return result;
}
//search method
template<class T>
bool AVLtree<T>::check(const T &key){
    return this->checking(key, this->root);
}
template<class T>
bool AVLtree<T>::checking(const T &key, AVLnode<T> *traverse){
    bool result = false;
    if(traverse != nullptr){
        if(traverse->key == key){
            result = true;
        }
        else if(key < traverse->key){
            result = this->checking(key,traverse->left);
        }
        else if(key > traverse->key){
            result = this->checking(key,traverse->right);
        }
    }
    return result;
}
//in order method
template<class T>
void AVLtree<T>::inorder(){
    this->inordering(this->root);
}
template<class T>
void AVLtree<T>::inordering(AVLnode<T> *temp){
    if(temp!=NULL){
        this->inordering(temp->left);
        cout<<temp->key<<endl;
        this->inordering(temp->right);
    }
}
//end of my own implementation
//print balance
template <class T>
void AVLtree<T>::printBalance() {
    printBalance(root);
    std::cout << std::endl;
}
#endif // AVLTREE
