#include "dsets.h"



void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        vals.push_back(-1);
    }
}	

int DisjointSets::size(int elem) {
    return vals[find(elem)] * -1;
}


int DisjointSets::find(int elem) {
    if (vals[elem] < 0) {
        return elem;
    } 
    vals[elem] = find(vals[elem]);
    return find(vals[elem]);
}	


void DisjointSets::setunion(int a, int b) {
    int root1 = find(a);
    int root2 = find(b);
    int newSize = vals[root1] + vals[root2];
    if (vals[root1] < vals[root2]) {
        vals[root2] = root1;
        vals[root1] = newSize;
    } else {
        vals[root1] = root2;
        vals[root2] = newSize;
    }
}

