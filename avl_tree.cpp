#include <iostream>
#include "SearchTree.h"

template <typename E>  class AVLTree;


template <typename E>
  class AVLEntry : public E {				// an AVL entry
  private:
    int ht;						// node height
  protected:						// local types
    typedef typename E::Key K;				// key type
    typedef typename E::Value V;			// value type
    int height() const { return ht; }			// get height
    void setHeight(int h) { ht = h; }			// set height
  public:						// public functions
    AVLEntry(const K& k = K(), const V& v = V())	// constructor
        : E(k,v), ht(0) { }	
    friend class AVLTree<E>;				// allow AVLTree access
  };

//
// AVL Tree class
//  
template <typename E>					// an AVL tree
  class AVLTree : public SearchTree< AVLEntry<E> > {
  public:						// public types
    typedef AVLEntry<E> Entry;			// an entry
    typedef typename SearchTree<Entry>::Iterator Iterator; // an iterator
  protected:						// local types
    typedef typename Entry::Key K;			// a key
    typedef typename Entry::Value V;			// a value
    typedef SearchTree<Entry> ST;			// a search tree
    typedef typename ST::TPos TPos;			// a tree position
  public:						// public functions
    AVLTree();						// constructor
    Iterator insert(const K& k, const V& x);		// insert (k,x)
    void erase(const K& k);	// remove key k entry
    void erase(const Iterator& p);			// remove entry at p
  protected:						// utility functions 
    int height(const TPos& v) const;			// node height utility
    void setHeight(TPos v);				// set height utility
    bool isBalanced(const TPos& v) const;		// is v balanced?
    TPos tallGrandchild(const TPos& v) const;		// get tallest grandchild
    void rebalance(const TPos& v);			// rebalance utility
    TPos restructure(const TPos& v); 			// restructure
  };

//
// Implementation
//

template <typename E>					// constructor
AVLTree<E>::AVLTree() : ST() { }

template <typename E>					// node height utility
int AVLTree<E>::height(const TPos& v) const
    { return (v.isExternal() ? 0 : (*v).height()); }

template <typename E>					// set height utility
void AVLTree<E>::setHeight(TPos v) {
    int hl = height(v.left());
    int hr = height(v.right());
    (*v).setHeight(1 + std::max(hl, hr));			// max of left & right
}

template <typename E>					// is v balanced?
bool AVLTree<E>::isBalanced(const TPos& v) const {	
    int bal = height(v.left()) - height(v.right());
    return ((-1 <= bal) && (bal <= 1));
}

template <typename E>					// get tallest grandchild
typename AVLTree<E>::TPos AVLTree<E>::tallGrandchild(const TPos& z) const {
    TPos zl = z.left();
    TPos zr = z.right();
    if (height(zl) >= height(zr))			// left child taller
        if (height(zl.left()) >= height(zl.right()))
            return zl.left();
        else
            return zl.right();
    else 						// right child taller
        if (height(zr.right()) >= height(zr.left()))
            return zr.right();
        else
            return zr.left();
}


//
// ToDo
//

template <typename E>					// remove key k entry
void AVLTree<E>::erase(const K& k) {
    
// ToDo
    TPos v = ST::finder(k, ST::root());

    if (v.isExternal()) {
        throw "Erase of nonexistent";
    }

    TPos w = ST::eraser(v);
    rebalance(w);
}

template <typename E>					// insert (k, x)
typename AVLTree<E>::Iterator AVLTree<E>::insert(const K& k, const V& x) {
    
// ToDo
    TPos v = ST::inserter(k, x);
    setHeight(v);
    rebalance(v);
    return Iterator(v);
}
  
template <typename E>					// rebalancing utility
void AVLTree<E>::rebalance(const TPos& v) {
    
    // ToDo
    TPos z = v;

    while (z != ST::root()) {
        z = z.parent();
        setHeight(z);

        if (!isBalanced(z)) {
            TPos x = tallGrandchild(z);
            z = restructure(x);
            setHeight(z.left());
            setHeight(z.right());
            setHeight(z);
        }
    }
}
  
template <typename E>				// Binary Search Tree Rotation
typename AVLTree<E>::TPos AVLTree<E>::restructure(const TPos& v) {

    // ToDo
    TPos x = v;
    TPos y = v.parent();
    TPos z = v.parent().parent();

    TPos t0, t1, t2, t3;

    if (y == z.right() && x == y.right()) {
        t0 = x.left();
        t1 = y.left();
        t2 = z.left();
        t3 = z.right();

        t1.v->par = z.v;
        z.v->right = t1.v;
        y.v->par = z.v->par;

        if (z.parent().v->left == z.v)
            z.parent().v->left = y.v;
        else if (z.parent().v->right == z.v)
            z.parent().v->right = y.v;

        z.v->par = y.v;
        y.v->left = z.v;

        return y;
    }

    else if (y == z.left() && x == y.left()) {
        t0 = x.left();
        t1 = x.right();
        t2 = y.right();
        t3 = z.right();

        t2.v->par = z.v;
        z.v->left = t2.v;
        y.v->par = z.v->par;

        if (z.parent().v->left == z.v)
            z.parent().v->left = y.v;
        else if (z.parent().v->right == z.v)
            z.parent().v->right = y.v;
        
        z.v->par = y.v;
        y.v->right = z.v;

        return y;
    }

    else if (y == z.right() && x == y.left()) {
        t0 = z.left();
        t1 = x.left();
        t2 = x.right();
        t3 = y.right();

        t2.v->par = y.v;
        y.v->left = t2.v;
        x.v->par = z.v;
        z.v->right = x.v;
        y.v->par = x.v;
        x.v->right = y.v;
        t1.v->par = z.v;
        z.v->right = t1.v;
        x.v->par = z.v->par;

        if (z.parent().v->left == z.v)
            z.parent().v->left = x.v;
        else if (z.parent().v->right == z.v)
            z.parent().v->right = x.v;

        z.v->par = x.v;
        x.v->left = z.v;

        return x;
    }

    else if (y == z.left() && x == y.right()) {
        t0 = y.left();
        t1 = x.left();
        t2 = x.right();
        t3 = z.right();

        t1.v->par = y.v;
        y.v->right = t1.v;
        x.v->par = z.v;
        z.v->left = x.v;
        y.v->par = x.v;
        x.v->left = y.v;
        t2.v->par = z.v;
        z.v->left = t2.v;
        x.v->par = z.v->par;

        if (z.parent().v->left == z.v)
            z.parent().v->left = x.v;
        else if (z.parent().v->right == z.v)
            z.parent().v->right = x.v;

        z.v->par = x.v;
        x.v->right = z.v;

        return x;
    }
}
