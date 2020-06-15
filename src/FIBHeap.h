
#ifndef INTRO_ALG_FIBHEAP_H
#define INTRO_ALG_FIBHEAP_H

#include <algorithm>
#include <iostream>
#include <stack>

// Fib node
template<typename T1, typename T2>
struct FibNode {

    T1 key;
    T2 value;

    bool mark;
    int degree;

    FibNode *child;
    FibNode *parent;
    FibNode *left;
    FibNode *right;

    // default construction
    FibNode() : key(0), value(0), mark(false), degree(0), child(nullptr),
                parent(nullptr), left(nullptr), right(nullptr) {};

    // construction
    FibNode(T1 key, T2 value, bool mark, int degree, FibNode *child,
            FibNode *parent) {

        this->key = key;
        this->value = value;
        this->mark = mark;
        this->degree = degree;

        this->child = child;
        this->parent = parent;
    }

    // overload = operator
    FibNode &operator=(FibNode &node) {

        this->key = node.key;
        this->value = node.value;

        this->mark = node.mark;
        this->degree = node.degree;

        this->child = node.child;
        this->right = node.right;
        this->left = node.left;
        this->parent = node.parent;

    }

    // overload = operator
    const FibNode &operator=(const FibNode &node) {

        this->key = node.key;
        this->value = node.value;

        this->mark = node.mark;
        this->degree = node.degree;

        this->child = node.child;
        this->right = node.right;
        this->left = node.left;
        this->parent = node.parent;

    }
};

// fib heap
template<typename T1, typename T2>
class FibHeap {

private:
    int sz;
    FibNode<T1, T2> *begin;
    FibNode<T1, T2> *hmin;

public:

    // default construction
    FibHeap() : sz(0), begin(nullptr), hmin(nullptr) {};

    // construction
    FibHeap(T1 key, T2 value) {
        this->begin = new FibNode<T1, T2>(key, value, false, 0, nullptr, nullptr);
        this->hmin = this->begin;
        sz = 1;
    }

    // destructor
    ~FibHeap() {

        hmin = nullptr;

        if (this->sz == 0)
            return;

        while (this->sz > 0) {
            while (begin->child != nullptr)
                begin = begin->child;

            if (begin->right != nullptr) {
                this->begin = this->begin->right;
                delete this->begin->left;
                this->begin->left = nullptr;
                --this->sz;
            } else
                begin = begin->parent;
        }

    }

    // insert
    void insert(T1 key, T2 value) {

        if (hmin == nullptr) {
            this->begin = new FibNode<T1, T2>(key, value, false, 0, nullptr,
                                              nullptr);
            this->hmin = this->begin;
            sz = 1;
        } else {

            FibNode<T1, T2> *tmp;

            tmp = begin;
            while (tmp->right != nullptr)
                tmp = tmp->right;

            tmp->right = new FibNode<T1, T2>(key, value, false, 0, nullptr, nullptr);
            tmp->left = tmp->right;
            tmp->right->left = tmp;
            tmp->right->right = tmp;

            if (key < hmin->key)
                hmin = tmp->right;
        }

        ++sz;
    }

    // union
    void funion(FibHeap<T1, T2> *fib) {

        FibNode<T1, T2> *tmp, *tmpf;

        tmp = this->begin->left;
        tmpf = fib->begin->right;

        this->begin->left = fib->begin;
        fib->begin->right = this->begin;

        tmpf->left = tmp;
        tmp->right = tmpf;


        if ((this->hmin == nullptr) || (fib->hmin != nullptr && fib->hmin->key <
                                                                this->hmin->key))
            this->hmin = fib->hmin;

        this->sz += fib->sz;
    }

private:

    // link
    void link(FibNode<T1, T2> *y_node, FibNode<T1, T2> *x_node) {

        y_node->left->right = y_node->right;
        y_node->right->left = y_node->left;

        x_node->child->right = y_node;
        y_node->left = x_node->child;

        ++x_node->degree;
    }

    // consolidate
    void consolidate() {

        FibNode<T1, T2> *tmp = begin;
        int maxD = tmp->degree;

        tmp = tmp->right;
        while (tmp != begin) {
            if (maxD < tmp->degree)
                maxD = tmp->degree;
            tmp = tmp->right;
        }

        if (maxD > 0) {
            FibNode<T1, T2> *A[maxD];

            for (int j = 0; j < maxD; ++j)
                A[j] = nullptr;

            tmp = begin;

            FibNode<T1, T2> *x_node, *y_node;
            int d;

            x_node = tmp;
            d = x_node->degree;

            while (A[d] != nullptr) {
                y_node = A[d];
                if (x_node->key > y_node->key) {
                    T1 key;

                    key = x_node->key;
                    x_node->key = y_node->key;
                    y_node->key = key;

                    T2 value;

                    value = x_node->value;
                    x_node->value = y_node->value;
                    y_node->value = value;

                    bool mark;

                    mark = x_node->mark;
                    x_node->mark = y_node->mark;
                    y_node->mark = mark;

                    int degree;

                    degree = x_node->degree;
                    x_node->degree = y_node->degree;
                    y_node->degree = degree;

                    FibNode<T1, T2> *child;

                    child = x_node->child;
                    x_node->child = y_node->child;
                    y_node->child = child;

                    FibNode<T1, T2> *parent;

                    parent = x_node->parent;
                    x_node->parent = y_node->parent;
                    y_node->parent = parent;

                    FibNode<T1, T2> *left;

                    left = x_node->left;
                    x_node->left = y_node->left;
                    y_node->left = left;

                    FibNode<T1, T2> *right;

                    right = x_node->right;
                    x_node->right = y_node->right;
                    y_node->right = right;
                }
                link(y_node, x_node);
                A[d] = nullptr;
                d = d + 1;
            }
            A[d] = x_node;

            tmp = tmp->right;
            while (tmp != begin) {

                x_node = tmp;
                d = x_node->degree;

                while (A[d] != nullptr) {
                    y_node = A[d];
                    if (x_node->key > y_node->key) {
                        T1 key;

                        key = x_node->key;
                        x_node->key = y_node->key;
                        y_node->key = key;

                        T2 value;

                        value = x_node->value;
                        x_node->value = y_node->value;
                        y_node->value = value;

                        bool mark;

                        mark = x_node->mark;
                        x_node->mark = y_node->mark;
                        y_node->mark = mark;

                        int degree;

                        degree = x_node->degree;
                        x_node->degree = y_node->degree;
                        y_node->degree = degree;

                        FibNode<T1, T2> *child;

                        child = x_node->child;
                        x_node->child = y_node->child;
                        y_node->child = child;

                        FibNode<T1, T2> *parent;

                        parent = x_node->parent;
                        x_node->parent = y_node->parent;
                        y_node->parent = parent;

                        FibNode<T1, T2> *left;

                        left = x_node->left;
                        x_node->left = y_node->left;
                        y_node->left = left;

                        FibNode<T1, T2> *right;

                        right = x_node->right;
                        x_node->right = y_node->right;
                        y_node->right = right;
                    }
                    link(y_node, x_node);
                    A[d] = nullptr;
                    d = d + 1;
                }
                A[d] = x_node;

                tmp = tmp->right;
            }

            hmin = nullptr;
            for (int j = 0; j < maxD; ++j) {

                if (A[j] != nullptr) {
                    if (hmin == nullptr)
                        hmin = A[j];
                    else {
                        A[j]->right = begin;
                        begin->left = A[j];
                        begin = A[j];

                        if ((A[j])->key < hmin->key)
                            hmin = A[j];
                    }
                }
            }
        }

    }

public:

    // extract
    FibNode<T1, T2> *extract() {

        FibNode<T1, T2> *z_node = hmin;
        FibNode<T1, T2> *child;

        if (z_node != nullptr) {

            child = z_node->child;
            if (child != nullptr) {
                child->right = begin;
                begin->left = child;
                begin = child;
                begin->parent = nullptr;
                child = child->right;

                while (child != z_node->child) {
                    child->right = begin;
                    begin->left = child;
                    begin = child;
                    begin->parent = nullptr;
                    child = child->right;
                }
            }

            z_node->left = z_node->right->left;
            z_node->right = z_node->left->right;

            if (z_node == z_node->right)
                hmin = nullptr;
            else {
                hmin = z_node->right;
                consolidate();
            }

            --this->sz;
        }

        return z_node;
    }

private:

    // cut
    void cut(FibNode<T1, T2> *x_node, FibNode<T1, T2> *y_node) {

        if (y_node->degree == 1) {
            --y_node->degree;
            y_node->child = nullptr;
        } else {
            --y_node->degree;
            y_node->child = x_node->left;
            x_node->left = x_node->right->left;
            x_node->right = x_node->left->right;
        }

        x_node->right = begin;
        begin->left = x_node;
        begin = x_node;

        x_node->parent = nullptr;
        x_node->mark = false;
    }

    // cascading-cut
    void cascading_cut(FibNode<T1, T2> *y_node) {

        FibNode<T1, T2> *z_node = y_node->parent;

        if (z_node != nullptr) {
            if (y_node->mark == false)
                y_node->mark = true;
            else {
                cut(y_node, z_node);
                cascading_cut(z_node);
            }
        }
    }

public:
    // decrease-key
    void decrease_key(FibNode<T1, T2> *x_node, int key) {

        FibNode<T1, T2> *y_node;
        if (key > x_node->key)
            return;

        x_node->key = key;
        y_node = x_node->parent;
        if (y_node != nullptr && x_node->key < y_node->key) {
            cut(x_node, y_node);
            cascading_cut(y_node);
        }

        if (x_node->key < hmin->key)
            hmin = x_node;
    }

    void print() {

        FibNode<T1, T2> *node;
        node = begin;

        std::cout << node->key << "  " << node->value << std::endl;
        node = node->right;

        while (node != begin) {
            std::cout << node->key << "  " << node->value << std::endl;
            node = node->right;
        }


    }

};

#endif //INTRO_ALG_FIBHEAP_H