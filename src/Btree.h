

#ifndef INTRO_ALG_BTREE_H
#define INTRO_ALG_BTREE_H

#include <vector>
#include <iostream>
#include <stack>

template<typename T1, typename T2>
struct bNode {

    int sz;

    std::vector<T1> key;
    std::vector<T2> data;
    std::vector<bNode<T1, T2> *> ptr;

    bool leaf;

    // default construction
    bNode() : sz(0), leaf(true) {};

    // construction
    bNode(int sz_, bool leaf_);

    // construction
    bNode(bNode const &node_);

    // overload = operator
    bNode &operator=(bNode node_);

};


template<typename T1, typename T2>
struct Pair {
    bNode<T1, T2> node;
    int index;

    // default construction
    Pair() : index(0) {};

    // construction
    Pair(bNode<T1, T2> node_, int index_);

};


template<typename T1, typename T2>
class Btree {

private:
    bNode<T1, T2> *root;
    int t;

public:
    // default construction
    Btree() : root(nullptr), t(0) {};

    // construction
    Btree(int t_) : root(nullptr), t(t_) {};

    // destructor
    ~Btree() {

        bNode<T1, T2> *tmp_node = root;
        int *c;
        int count = 1;
        int l = 0;

        if (root == nullptr)
            return;

        while (tmp_node->ptr[0] != nullptr) {
            ++count;
            tmp_node = tmp_node->ptr[0];
        }

        c = new int[count];

        for (int j = 0; j < count; ++j)
            c[j] = 0;

        while (true) {
            tmp_node = root;

            while (true) {
                if (tmp_node->ptr[0] != nullptr) {
                    tmp_node = tmp_node->ptr[c[l]];
                    c[l]++;
                    l++;
                } else {
                    for (int j = 0; j < tmp_node->sz; ++j) {
                        delete tmp_node->ptr[j];
                        tmp_node->ptr[j] = nullptr;
                    }
                    break;
                }
            }

            l = 0;

            if (c[0] == tmp_node->sz)
                break;
        }

        delete[] c;
        delete tmp_node;

    }

    // search
    Pair<T1, T2> *search(T1 key);

private:

    // split child
    void split_child(bNode<T1, T2> *x_node, int index);

    // nonfull
    void nonfull(bNode<T1, T2> *x_node, T1 key, T2 data);

public:

    // insert
    void insert(T1 key, T2 data);

    // print
    void print();

};


// construction
template<typename T1, typename T2>
bNode<T1, T2>::bNode(int sz_, bool leaf_) {
    this->sz = sz_;
    this->leaf = leaf_;
}

// construction
template<typename T1, typename T2>
bNode<T1, T2>::bNode(const bNode<T1, T2> &node_) {
    this->sz = node_.sz;
    this->key = node_.key;
    this->leaf = node_.leaf;
    this->data = node_.data;
    this->ptr = node_.ptr;
}

// overload = operator
template<typename T1, typename T2>
bNode<T1, T2> &bNode<T1, T2>::operator=(bNode<T1, T2> node_) {
    this->leaf = node_.leaf;
    this->key = node_.key;
    this->sz = node_.sz;
    this->data = node_.data;
    this->ptr = node_.ptr;
}

// construction
template<typename T1, typename T2>
Pair<T1, T2>::Pair(bNode<T1, T2> node_, int index_) {
    this->node = node_;
    this->index = index_;
}

// search
template<typename T1, typename T2>
Pair<T1, T2> *Btree<T1, T2>::search(T1 key) {

    Pair<T1, T2> *pair;
    int j = 0;

    while (j < root->sz && key > root->key[j])
        j += 1;

    if (j <= root->sz && key == root->key[j]) {
        pair = new Pair<T1, T2>(root, j);
        return pair;
    } else if (root->leaf)
        return nullptr;
    else
        (root->ptr[j])->search(key);

}

// split child
template<typename T1, typename T2>
void Btree<T1, T2>::split_child(bNode<T1, T2> *x_node, int index) {

    bNode<T1, T2> *z_node;

    bNode<T1, T2> *y_node = x_node->ptr[index];

    z_node->leaf = y_node->leaf;
    z_node->sz = t - 1;
    z_node->key.resize(z_node->sz);
    z_node->data.resize(z_node->sz);
    z_node->ptr.resize(z_node->sz + 1);

    for (int j = 0; j < t - 1; ++j) {
        z_node->key[j] = y_node->key[j + t];
        z_node->data[j] = y_node->data[j + t];
    }
    if (!y_node->leaf) {
        for (int j = 0; j < t; ++j)
            z_node->ptr[j] = y_node->ptr[j + t];
    }

    y_node->sz = t - 1;

    x_node->ptr.resize(x_node->sz + 1);
    for (int j = x_node->sz - 1; j > index; --j) {
        x_node->ptr[j + 1] = x_node->ptr[j];
    }
    x_node->ptr[index] = new bNode<T1, T2>(*z_node);

    x_node->key.resize(x_node->sz + 1);
    x_node->data.resize(x_node->sz + 1);
    for (int j = x_node->sz - 1; j > index; --j) {
        x_node->key[j + 1] = x_node->key[j];
        x_node->data[j + 1] = x_node->data[j];
    }
    x_node->key[index] = y_node->key[t - 1];
    x_node->data[index] = y_node->data[t - 1];

    x_node->sz += 1;

}

// nonfull
template<typename T1, typename T2>
void Btree<T1, T2>::nonfull(bNode<T1, T2> *x_node, T1 key, T2 data) {

    int j = x_node->sz;

    if (x_node->leaf) {
        x_node->key.resize(x_node->sz + 1);
        while (j >= 0 && key < x_node->key[j]) {
            x_node->key[j] = x_node->key[j - 1];
            x_node->data[j] = x_node->data[j - 1];
            j = j - 1;
        }
        x_node->key[j] = key;
        x_node->data[j] = data;
        x_node->sz += 1;
    } else {
        while (j >= 0 && key < x_node->key[j])
            j -= 1;

        if ((x_node->ptr[j])->sz == 2 * t - 1) {
            split_child(x_node, j);
            if (key > x_node->key[j])
                ++j;
        }

        nonfull(x_node->ptr[j], key, data);
    }
}

//insert
template<typename T1, typename T2>
void Btree<T1, T2>::insert(T1 key, T2 data) {

    bNode<T1, T2> *node = this->root;

    if (root == nullptr) {

        root = new bNode<T1, T2>(1, true);
        root->key.resize(1);
        root->key[0] = key;
        root->data.resize(1);
        root->data[0] = data;
        root->ptr.resize(2);

    } else if (root->sz == 2 * t - 1) {

        this->root->leaf = false;
        this->root->sz = 0;
        this->root->ptr[0] = new bNode<T1, T2>(*node);

        split_child(this->root, 1);
        nonfull(this->root, key, data);
    } else {
        nonfull(node, key, data);
    }
}

// print
template<typename T1, typename T2>
void Btree<T1, T2>::print() {

    std::cout << "key : ";
    for (int j = 0; j < root->sz; ++j)
        std::cout << root->key[j] << "  ";
    std::cout << std::endl;
    std::cout << "data : ";
    for (int j = 0; j < root->sz; ++j)
        std::cout << root->data[j] << "  ";
    std::cout << std::endl;

}


#endif //INTRO_ALG_BTREE_H
