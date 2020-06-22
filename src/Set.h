
#ifndef INTRO_ALG_SET_H
#define INTRO_ALG_SET_H

template<typename T>
struct Elem {

    // variables
    Elem *front;
    T *data;
    Elem *back;

    // default construction
    Elem() : front(nullptr), data(nullptr), back(nullptr) {};

    // construction
    Elem(T value) {
        front = nullptr;
        data = new T(value);
        back = nullptr;
    }

    // construction
    Elem(Elem *front, T value, Elem *back) {
        this->front = front;
        data = new T(value);
        this->back = back;
    }

    ~Elem() {
        // free data;
        if (this->data != nullptr) {
            delete this->data;
            this->data = nullptr;
        }

    }

    // set value
    void set(T value) {
        this->front = nullptr;
        data = new T(value);
        this->back = nullptr;
    }

    // set value
    void set(Elem *front, T value, Elem *back) {
        this->front = front;
        this->data = new T(value);
        this->back = back;
    }
};

template<typename T>
class Set {

private:

    // variables
    unsigned int sz;
    Elem<T> *head;
    Elem<T> *tail;

public:

    // default construction
    Set() : sz(0), head(nullptr), tail(nullptr) {};

    // construction
    Set(T value) {
        head = new Elem<T>(value);

        tail = head;

        head->front = nullptr;
        head->back = nullptr;

        sz = 1;
    }

    // make set
    void Make_Set(T value) {
        head = new Elem<T>(value);

        tail = head;

        head->front = nullptr;
        head->back = nullptr;

        sz = 1;
    }

    // find set
    Elem<T> Find_Set() {
        return *head;
    }

    // union
    void Union(T value) {

        if (head == nullptr) {
            head = new Elem<T>(value);

            head = tail;

            head->front = nullptr;
            head->back = nullptr;

            sz = 1;

            return;
        }

        tail->back = new Elem<T>(value);

        tail->back->front = head;
        tail->back->back = nullptr;

        tail = tail->back;

        ++sz;

        return;
    }

    void Union(Set set) {

        tail->back = set.head;
        tail = set.tail;

        Elem<T> *tmp = set.head;
        while (tmp->back != nullptr) {
            tmp->back->front = head;
            tmp = tmp->back;
        }

    }
};

#endif //INTRO_ALG_SET_H
