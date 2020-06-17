
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
    int mini(){
        return *min;
    }

    // max
    int maxi(){
        return *max;
    }

private:

    // high
    int high(int x){
        int k=pow(2,floor(log2(u)/2));
        return x/k;
    }

    // low
    int low(int x){
        int k=pow(2,floor(log2(u)/2));
        return x%k;
    }

    // index
    int index(int x,int y){
        int k=pow(2,floor(log2(u)/2));
        return x*k+y;
    }

    // member
    bool member(int x){
        if(x==*this->min || x==*this->max)
            return true;
        else if(this->u==2)
            return false;
        else
            return this->cluster[high(x)]->member(low(x));
    }



};

#endif //INTRO_ALG_VANEMDEBOAS_H
