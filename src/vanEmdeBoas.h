
#ifndef INTRO_ALG_VANEMDEBOAS_H
#define INTRO_ALG_VANEMDEBOAS_H

#include <vector>
#include <cmath>

class vEB {

private:

    int u;

    int *min;
    int *max;

    vEB *summary;

    std::vector<vEB *> cluster;

public:

    // default construction
    vEB() : u(0), min(nullptr), max(nullptr), summary(nullptr), cluster(0) {};

    // construction
    vEB(int u) {

        this->u = u;

        min = nullptr;
        max = nullptr;
        summary = nullptr;

        cluster.resize(ceil(pow(2, log2(u) / 2)));
    }

    // min
    int *mini() {
        return min;
    }

    // max
    int *maxi() {
        return max;
    }

private:

    // high
    int high(int x) {
        int k = pow(2, floor(log2(u) / 2));
        return x / k;
    }

    // low
    int low(int x) {
        int k = pow(2, floor(log2(u) / 2));
        return x % k;
    }

    // index
    int index(int x, int y) {
        int k = pow(2, floor(log2(u) / 2));
        return x * k + y;
    }

    // member
    bool member(int x) {
        if (x == *this->min || x == *this->max)
            return true;
        else if (this->u == 2)
            return false;
        else
            return this->cluster[high(x)]->member(low(x));
    }

    // successor
    int successor(int x) {
        int offset;
        int succ_cluster;
        if (this->u == 2) {
            if (x == 0 && *this->max == 1)
                return 1;
            else
                return -1;
        } else if (this->min != nullptr && x < *this->min)
            return *this->min;
        else {
            int *max_low = cluster[high(x)]->maxi();
            if (max_low != nullptr && low(x) < *max_low) {
                offset = cluster[high(x)]->successor(low(x));
                return index(high(x), offset);
            } else {
                succ_cluster = this->summary->successor(high(x));
                if (succ_cluster == -1)
                    return -1;
                else {
                    offset = *this->cluster[succ_cluster]->mini();
                    return index(succ_cluster, offset);
                }
            }
        }
    }

    // predecessor
    int predecessor(int x) {
        int *min_low;
        int offset;
        int pred_cluster;
        if (this->u == 2) {
            if (x == 1 && *this->min == 0)
                return 0;
            else
                return -1;
        } else if (this->max != nullptr && x > *this->max)
            return *this->max;
        else {
            min_low = cluster[high(x)]->mini();
            if (min_low != nullptr && low(x) > *min_low) {
                offset = cluster[high(x)]->predecessor(low(x));
                return index(high(x), offset);
            } else {
                pred_cluster = this->summary->predecessor(high(x));
                if (pred_cluster == -1) {
                    if (this->min != nullptr && x > *this->min)
                        return *this->min;
                    else
                        return -1;
                } else {
                    offset = *cluster[pred_cluster]->maxi();
                    return index(pred_cluster, offset);
                }
            }
        }
    }

    // empty-insert
    void empty_insert(int x) {
        this->min = new int(x);
        this->max = new int(x);
    }

    // insert
    void insert(int x) {
        int swap;
        if (this->min == nullptr)
            empty_insert(x);
        else {
            if (x < *this->min) {
                swap = x;
                x = *this->min;
                *this->min = swap;
            }
            if (this->u > 2) {
                if (cluster[high(x)]->mini() == nullptr) {
                    summary->insert(high(x));
                    cluster[high(x)]->insert(low(x));
                } else
                    cluster[high(x)]->insert(low(x));
            }
            if (x > *this->max)
                *this->max = x;
        }
    }

    // delete
    void dele(int x) {
        int first_cluster;
        int *summary_max;

        if (*this->min == *this->max) {
            delete this->min;
            delete this->max;
            this->min = nullptr;
            this->max = nullptr;
        } else if (this->u == 2) {
            if (x == 0) {
                if (this->min == nullptr)
                    this->min = new int(1);
                else
                    *this->min = 1;
            } else {
                if (this->min == nullptr)
                    this->min = new int(0);
                else
                    *this->min = 0;
            }
            *this->max = *this->min;
        } else if (x == *this->min) {
            first_cluster = *summary->mini();
            x = index(first_cluster, *cluster[first_cluster]->mini());
            if (this->min == nullptr)
                this->min=new int(x);
            else
                *this->min=x;
            cluster[high(x)]->dele(low(x));
            if(cluster[high(x)]->mini()== nullptr){
                summary->dele(high(x));
                if(x==*this->max){
                    summary_max=summary->maxi();
                    if(summary_max==nullptr)
                        *this->max=*this->min;
                    else
                        *this->max=index(*summary_max,*cluster[*summary_max]->maxi
                        ());
                }
            }else if(x==*this->max){
                *this->max=index(high(x),*cluster[high(x)]->maxi());
            }
        }
    }

};

#endif //INTRO_ALG_VANEMDEBOAS_H
