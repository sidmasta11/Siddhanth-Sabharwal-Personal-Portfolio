// File FHsplayTree.h
// Template definitions for FHsplayTree
#ifndef FHSPLAYTREE_H
#define FHSPLAYTREE_H
#include "FHsearch_tree.h"

// ----------------------FHsplayTree Prototype--------------------------
template <class Comparable>
class FHsplayTree : public FHsearch_tree < Comparable >
{
public:
    //Overriding some base class methods
    bool insert(const Comparable &x);
    bool remove(const Comparable &x);

    //Overloading some base class methods
    bool contains(const Comparable &x);
    const Comparable &find(const Comparable &x);

    const Comparable &showRoot();

protected:
    bool insert(FHs_treeNode<Comparable> * &root, const Comparable &x);
    bool remove(FHs_treeNode<Comparable> * &root, const Comparable &x);
    void splay(FHs_treeNode<Comparable> * &root, const Comparable &x);
    FHs_treeNode<Comparable> *find(FHs_treeNode<Comparable> * root, const Comparable &x);
    void rotateWithLeftChild(FHs_treeNode<Comparable> * &k2);
    void rotateWithRightChild(FHs_treeNode<Comparable> * &k2);
};

// FHsplayTree method definitions -------------------
// protected utilities for member methods
template <class Comparable>
bool FHsplayTree<Comparable>::insert(FHs_treeNode<Comparable> * &root, const Comparable &x){
    FHs_treeNode<Comparable> *newRoot;

    if (root == NULL){
        root = new FHs_treeNode<Comparable>(x, NULL, NULL);
        return true;
    }

    splay(root, x);

    if (root->data != x){
        newRoot = new FHs_treeNode<Comparable>(x, NULL, NULL);
        newRoot->lftChild = root;
        newRoot->rtChild = root->rtChild;
        root->rtChild = NULL;
        root = newRoot;
        return true;
    }
    else
        return false;
}

template <class Comparable>
bool FHsplayTree<Comparable>::remove(FHs_treeNode<Comparable> * &root, const Comparable &x){
    FHs_treeNode<Comparable> *newRoot;

    splay(root, x);

    if (root->data != x)
        return false;

    if (root->lftChild == NULL)
        newRoot = root->rtChild;
    else{
        newRoot = root->lftChild;
        splay(newRoot, x);
        newRoot->rtChild = root->rtChild;
    }

    delete root;
    root = newRoot;

    return true;
}

template <class Comparable>
void FHsplayTree<Comparable>::splay(FHs_treeNode<Comparable> * & root, const Comparable & x){
    FHs_treeNode<Comparable> *rightTree = NULL;
    FHs_treeNode<Comparable> *leftTree = NULL;
    FHs_treeNode<Comparable> * rightTreeMin = NULL;
    FHs_treeNode<Comparable> * leftTreeMax = NULL;

    while (root != NULL){
        if (x < root->data){
            if (!root->lftChild)
                break;
            if (x < root->lftChild->data){
                rotateWithLeftChild(root);
                if (!root->lftChild)
                    break;
            }
            if (rightTree == NULL){
                rightTree = root;
                rightTreeMin = root;
                root = root->lftChild;
            }
            else{
                rightTreeMin->lftChild = root;
                rightTreeMin = rightTreeMin->lftChild;
                root = root->lftChild;
            }
        }
        else if (root->data < x){
            if (!root->rtChild)
                break;
            if (root->rtChild->data < x){
                rotateWithRightChild(root);
                if (!root->rtChild)
                    break;
            }
            if (leftTree == NULL){
                leftTree = root;
                leftTreeMax = root;
                root = root->rtChild;
            }
            else{
                leftTreeMax->rtChild = root;
                leftTreeMax = leftTreeMax->rtChild;
                root = root->rtChild;
            }
        }
        else
            break;
    }

    if (leftTree != NULL){
        leftTreeMax->rtChild = root->lftChild;
        root->lftChild = leftTree;
    }
    if (rightTree != NULL){
        rightTreeMin->lftChild = root->rtChild;
        root->rtChild = rightTree;
    }
}

template <class Comparable>
FHs_treeNode<Comparable> * FHsplayTree<Comparable>::find(FHs_treeNode<Comparable> * root, const Comparable &x){
    splay(root, x);
    return root;
}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithLeftChild(FHs_treeNode<Comparable> * & k2){
    FHs_treeNode<Comparable> *k1 = k2->lftChild;
    k2->lftChild = k1->rtChild;
    k1->rtChild = k2;
    k2 = k1;
}

template <class Comparable>
void FHsplayTree<Comparable>::rotateWithRightChild(FHs_treeNode<Comparable> * & k2){
    FHs_treeNode<Comparable> *k1 = k2->rtChild;
    k2->rtChild = k1->lftChild;
    k1->lftChild = k2;
    k2 = k1;
}

//public helper functions
template <class Comparable>
bool FHsplayTree<Comparable>::insert(const Comparable &x){
    if (insert(this->mRoot, x)){
        mSize++;
        return true;
    }
    return false;
}

template <class Comparable>
bool FHsplayTree<Comparable>::remove(const Comparable &x){
    if (this->mRoot == NULL)
        return false;

    if (remove(this->mRoot, x)){
        mSize--;
        return true;
    }
    return false;
}

template <class Comparable>
bool FHsplayTree<Comparable>::contains(const Comparable &x){
    if (this->mRoot == NULL)
        return false;

    try{
        find(x);
    }
    catch (...)
    {
        cout << x << " not contained in tree." << endl;
        return false;
    }
    return true;
}

template <class Comparable>
const Comparable &FHsplayTree<Comparable>::find(const Comparable &x){
    if (!this->mRoot)
        return NULL;

    this->mRoot = find(this->mRoot, x);
    if (this->mRoot->data < x || x < this->mRoot->data)
        throw typename FHsearch_tree<Comparable>::NotFoundException();
    return this->mRoot->data;
}

template <class Comparable>
const Comparable & FHsplayTree<Comparable>::showRoot(){
    if (this->mRoot == NULL){
        return NULL;             //default object
    }
    return this->mRoot->data;
}

#endif