
#ifndef INTRO_ALG_FIBHEAP_H
#define INTRO_ALG_FIBHEAP_H

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
    FibNode() : key(0), value(0), mark(false), degree(0),child(nullptr),
        parent(nullptr),left(nullptr),right(nullptr){};

    // construction
    FibNode(T1 key,T2 value,bool mark,int degree,FibNode *child,FibNode *parent){

        this->key=key;
        this->value=value;
        this->mark=mark;
        this->degree=degree;

        this->child=child;
        this->parent=parent;
    }

};

// fib heap
template<typename T1, typename T2>
class FibHeap {

private:
    FibNode<T1,T2> *begin;
    FibNode<T1,T2> *hmin;

public:

    // default construction
    FibHeap():begin(nullptr),hmin(nullptr){};

    // construction
    FibHeap(T1 key,T2 value){
        this->begin=new FibNode<T1,T2>(key,value,false,0, nullptr, nullptr);
        this->hmin=this->begin;
    }







};

#endif //INTRO_ALG_FIBHEAP_H
