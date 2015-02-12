// File FHlazySearchTree.h
// Template definitions for FHsearchTrees, which are general trees
#ifndef FHLAZYSEARCHTREE_H
#define FHLAZYSEARCHTREE_H

// ---------------------- FHlazySearchTreeNode Prototype --------------------------
template <class Comparable>
class FHlazySearchTreeNode
{
public:
    FHlazySearchTreeNode(const Comparable & d = Comparable(),
        FHlazySearchTreeNode *lt = NULL,
        FHlazySearchTreeNode *rt = NULL,
        bool del = false)
        : lftChild(lt), rtChild(rt), deleted(del), data(d)
    { }

    FHlazySearchTreeNode *lftChild, *rtChild;
    Comparable data;
    bool deleted;

    // for use only with AVL Trees
    virtual int getHeight() const { return 0; }
    virtual bool setHeight(int height) { return true; }
};

// ---------------------- FHlazySearchTree Prototype --------------------------
template <class Comparable>
class FHlazySearchTree
{
protected:
    int mSize;
    int mSizeHard;
    FHlazySearchTreeNode<Comparable> *mRoot;

public:
    FHlazySearchTree() { mSize = 0; mSizeHard = 0; mRoot = NULL; }
    FHlazySearchTree(const FHlazySearchTree &rhs)
    {
        mRoot = NULL; mSize = 0; mSizeHard = 0; *this = rhs;
    }
    ~FHlazySearchTree() { clear(); }

    const Comparable &findMin() const;
    const Comparable &findMax() const;
    const Comparable &find(const Comparable &x) const;

    bool empty() const { return (mSize == 0); }
    int size() const { return mSize; }
    void clear() { makeEmpty(mRoot); }
    const FHlazySearchTree & operator=(const FHlazySearchTree &rhs);
    int sizeHard() const { return mSizeHard; }

    bool insert(const Comparable &x);
    bool remove(const Comparable &x);
    bool contains(const Comparable &x) const { return find(mRoot, x) != NULL; }

    template <class Processor>
    void traverse(Processor func) const {
        if (mSize != 0)
            traverse(mRoot, func);
        return;
    }
    int showHeight() const { return findHeight(mRoot); }
    void collectGarbage();

protected:
    FHlazySearchTreeNode<Comparable> *clone(FHlazySearchTreeNode<Comparable> *root) const;
    FHlazySearchTreeNode<Comparable> *findMin(FHlazySearchTreeNode<Comparable> *root) const;
    FHlazySearchTreeNode<Comparable> *findMax(FHlazySearchTreeNode<Comparable> *root) const;
    FHlazySearchTreeNode<Comparable> *find(FHlazySearchTreeNode<Comparable> *root,
        const Comparable &x) const;
    bool insert(FHlazySearchTreeNode<Comparable> * &root,
        const Comparable &x);
    bool remove(FHlazySearchTreeNode<Comparable> * &root, const Comparable &x);
    void makeEmpty(FHlazySearchTreeNode<Comparable> * &subtreeToDelete);
    template <class Processor>
    void traverse(FHlazySearchTreeNode<Comparable> *treeNode,
        Processor func, int level = -1) const;
    int findHeight(FHlazySearchTreeNode<Comparable> *treeNode, int height = -1) const;

    //hard remove
    void collectGarbage(FHlazySearchTreeNode<Comparable> * &root);
    void removeHard(FHlazySearchTreeNode<Comparable> * &root);

public:
    // for exception throwing
    class EmptyTreeException {};
    class NotFoundException {};
};

// FHlazySearchTree public method definitions -----------------------------
template <class Comparable>
const Comparable & FHlazySearchTree<Comparable>::findMin() const{
    if (mRoot == NULL)
        throw EmptyTreeException();
    if (mSizeHard == 0){
        cout << "No minimum value, everything has been hard deleted. ";
        return NULL;
    }
    if (mSize == 0){
        cout << "No minimum value, everything has been soft deleted. ";
        return NULL;
    }
    return findMin(mRoot)->data;
}

template <class Comparable>
const Comparable & FHlazySearchTree<Comparable>::findMax() const{
    if (mRoot == NULL)
        throw EmptyTreeException();
    if (mSizeHard == 0){
        cout << "No minimum value, everything has been hard deleted. ";
        return NULL;
    }
    if (mSize == 0){
        cout << "No max value, everything has been soft deleted. ";
        return NULL;
    }
    else
        return findMax(mRoot)->data;
}

template <class Comparable>
const Comparable &FHlazySearchTree<Comparable>::find(const Comparable &x) const{
    FHlazySearchTreeNode<Comparable> *resultNode;

    resultNode = find(mRoot, x);
    if (resultNode == NULL || mSizeHard = 0)
        throw NotFoundException();
    return resultNode->data;
}

template <class Comparable>
const FHlazySearchTree<Comparable> &FHlazySearchTree<Comparable>::operator=
(const FHlazySearchTree &rhs)
{
    if (&rhs != this)
    {
        clear();
        mRoot = clone(rhs.mRoot);
        mSize = rhs.size();
        mSizeHard = rhs.sizeHard();
    }
    return *this;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::insert(const Comparable &x)
{
    if (insert(mRoot, x))
    {
        mSize++;
        mSizeHard++;
        return true;
    }
    return false;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::remove(const Comparable &x)
{
    if (remove(mRoot, x)){
        mSize--;
        return true;
    }
    return false;
}

template <class Comparable>
template <class Processor>
void FHlazySearchTree<Comparable>::traverse(FHlazySearchTreeNode<Comparable> *treeNode,
    Processor func, int level) const
{
    if (treeNode == NULL)
        return;
    // we're not doing anything with level but its there in case we want it
    traverse(treeNode->lftChild, func, level + 1);
    if (treeNode->deleted == false)
        func(treeNode->data);
    traverse(treeNode->rtChild, func, level + 1);
}

template <class Comparable>
void FHlazySearchTree<Comparable>::collectGarbage()
{
    if (mSize != 0)
        collectGarbage(mRoot);
    else
        removeHard(mRoot);

    return;
}


//// FHlazySearchTree private method definitions -----------------------------
template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::clone(
    FHlazySearchTreeNode<Comparable> *root) const
{
    FHlazySearchTreeNode<Comparable> *newNode;
    if (root == NULL)
        return NULL;

    newNode = new FHlazySearchTreeNode<Comparable>(
        root->data,
        clone(root->lftChild), clone(root->rtChild),
        root->deleted);
    return newNode;
}

template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::findMin(
    FHlazySearchTreeNode<Comparable> *root) const
{

    FHlazySearchTreeNode<Comparable> *result;
    if (root == NULL)
        return NULL;

    if (root->deleted && root->lftChild != NULL)
        if (result = findMin(root->lftChild))
            return result;
        else
            return findMin(root->rtChild);
    if (root->deleted && root->lftChild == NULL){
        if (result = findMin(root->rtChild))
            return result;
    }

    if (root->lftChild == NULL && !root->deleted)
        return root;
    if (root->lftChild != NULL && !root->deleted)
        if (result = findMin(root->lftChild))
            return result;
        else
            return root;

    if (root->lftChild == NULL && root->rtChild == NULL)
        return root;

    return NULL;
}

template <class Comparable>
FHlazySearchTreeNode<Comparable> *FHlazySearchTree<Comparable>::findMax(
    FHlazySearchTreeNode<Comparable> *root) const
{

    if (root == NULL)
        return NULL;

    FHlazySearchTreeNode<Comparable> *result;
    if (root->deleted && root->rtChild != NULL)
        if (result = findMax(root->rtChild))
            return result;
        else
            return findMax(root->lftChild);
    if (root->deleted && root->rtChild == NULL){
        if (result = findMax(root->lftChild))
            return result;
    }

    if (root->rtChild == NULL && !root->deleted)
        return root;
    if (root->rtChild != NULL && !root->deleted)
        if (result = findMax(root->rtChild))
            return result;
        else
            return root;

    return NULL;
}

template <class Comparable>
FHlazySearchTreeNode<Comparable>* FHlazySearchTree<Comparable>::find(
    FHlazySearchTreeNode<Comparable> *root, const Comparable &x) const
{

    if (root == NULL)
        return NULL;
    else if (x < root->data)
        return find(root->lftChild, x);
    else if (root->data < x)
        return find(root->rtChild, x);
    else if (root->deleted)
        return NULL;
    else
        return root;
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::insert(
    FHlazySearchTreeNode<Comparable> * &root, const Comparable &x)
{
    if (root == NULL){
        root = new FHlazySearchTreeNode<Comparable>(x, NULL, NULL, false);
        return true;
    }
    else if (x < root->data)
        return insert(root->lftChild, x);
    else if (root->data < x)
        return insert(root->rtChild, x);
    else{
        root->deleted = false;
        mSize++;
    }

    return false; // duplicate
}

template <class Comparable>
bool FHlazySearchTree<Comparable>::remove(
    FHlazySearchTreeNode<Comparable> * &root, const Comparable &x)
{

    if (root == NULL)
        return false;
    else if (x < root->data)
        return remove(root->lftChild, x);
    else if (root->data < x)
        return remove(root->rtChild, x);
    else{
        if (root->deleted == false){
            root->deleted = true;
            return true;
        }     // found the node
        else return false;
    }
}

template <class Comparable>
void FHlazySearchTree<Comparable>::makeEmpty(
    FHlazySearchTreeNode<Comparable> * &subtreeToDelete)
{
    if (subtreeToDelete == NULL || mSizeHard == 0)
        return;

    // remove children
    makeEmpty(subtreeToDelete->lftChild);
    makeEmpty(subtreeToDelete->rtChild);

    // clear client's pointer
    delete subtreeToDelete;
    subtreeToDelete = NULL;
    --mSize;
    --mSizeHard;

}

template <class Comparable>
int FHlazySearchTree<Comparable>::findHeight(FHlazySearchTreeNode<Comparable> *treeNode,
    int height) const
{
    int leftHeight, rightHeight;

    if (treeNode == NULL)
        return height;
    height++;
    leftHeight = findHeight(treeNode->lftChild, height);
    rightHeight = findHeight(treeNode->rtChild, height);
    return (leftHeight > rightHeight) ? leftHeight : rightHeight;
}

template<class Comparable>
void FHlazySearchTree<Comparable>::collectGarbage(FHlazySearchTreeNode<Comparable> * &root)
{
    if (root == NULL || mSizeHard == 0)
        return;

    if (root->deleted)
        removeHard(root);
    if (root->lftChild != NULL){
        return collectGarbage(root->lftChild);
    }
    if (root->rtChild != NULL)
        return collectGarbage(root->rtChild);

    return;
}

template <class Comparable>
void FHlazySearchTree<Comparable>::removeHard(FHlazySearchTreeNode<Comparable> * &root)
{
    if (root == NULL)
        return;

    if (mSize == 0){             //This means we are going to be removing every node, avoids resetting values
        removeHard(root->lftChild);
        removeHard(root->rtChild);
        delete root;
        mSizeHard--;
    }
    else{
        if (root->lftChild != NULL && root->rtChild != NULL)
        {
            FHlazySearchTreeNode<Comparable> *minNode = findMin(root->rtChild);
            root->data = minNode->data;
            root->deleted = minNode->deleted;
            return removeHard(root->rtChild);
        }
        else
        {
            FHlazySearchTreeNode<Comparable> *nodeToRemove = root;
            root = (root->lftChild != NULL) ? root->lftChild : root->rtChild;
            delete nodeToRemove;
            mSizeHard--;
        }
    }

    return;
}

#endif