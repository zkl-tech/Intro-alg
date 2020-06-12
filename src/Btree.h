

#ifndef INTRO_ALG_BTREE_H
#define INTRO_ALG_BTREE_H

#include <vector>


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
    bNode(int sz_, bool leaf_) {
        this->sz = sz_;
        this->leaf = leaf_;
    }

    // construction
    bNode(bNode const &node_) {
        this->sz = node_.sz;
        this->key = node_.key;
        this->leaf = node_.leaf;
        this->data = node_.data;
        this->ptr = node_.ptr;
    }

    bNode &operator=(bNode node_) {
        this->leaf = node_.leaf;
        this->key = node_.key;
        this->sz = node_.sz;
        this->data = node_.data;
        this->ptr = node_.ptr;
    }

};


template<typename T1, typename T2>
struct Pair {
    bNode<T1, T2> node;
    int index;

    // default construction
    Pair() : index(0) {};

    // construction
    Pair(bNode<T1, T2> node_, int index_) {
        this->node = node_;
        this->index = index_;
    }

};


template<typename T1, typename T2>
class Btree {

private:
    bNode<T1, T2> *root;
    int t;

public:
    // default construction
    Btree() : t(0) {};

    // search
    Pair<T1, T2> *search(T1 key) {

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

private:
    void split_child(bNode<T1, T2> x_node, int index) {

        bNode<T1, T2> z_node;

        bNode<T1, T2> y_node = x_node.ptr[index];

        z_node.leaf = y_node.leaf;
        z_node.sz = t - 1;
        z_node.key.resize(z_node.sz);
        z_node.data.resize(z_node.sz);
        z_node.ptr.resize(z_node.sz + 1);

        for (int j = 0; j < t - 1; ++j) {
            z_node.key[j] = y_node.key[j + t];
            z_node.data[j] = y_node.data[j + t];
        }
        if (!y_node.leaf) {
            for (int j = 0; j < t; ++j)
                z_node.ptr[j] = y_node.ptr[j + t];
        }

        y_node.sz = t - 1;

        x_node.ptr.resize(x_node.sz + 1);
        for (int j = x_node.sz - 1; j > index; --j) {
            x_node.ptr[j + 1] = x_node.ptr[j];
        }
        x_node.ptr[index] = new bNode<T1, T2>(z_node);

        x_node.key.resize(x_node.sz + 1);
        x_node.data.resize(x_node.sz + 1);
        for (int j = x_node.sz - 1; j > index; --j) {
            x_node.key[j + 1] = x_node.key[j];
            x_node.data[j + 1] = x_node.data[j];
        }
        x_node.key[index] = y_node.key[t - 1];
        x_node.data[index] = y_node.data[t - 1];

        x_node.sz += 1;

    }

    void nonfull(bNode<T1,T2> x_node,T1 key){

        int j=x_node.sz;

        if(x_node.leaf){
            while(j>=1 && key<x_node.key[j]){
                x_node
            }
        }
    }
};

#endif //INTRO_ALG_BTREE_H
