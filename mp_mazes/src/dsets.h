/* Your code here! */

#pragma once
#include <vector>

class DisjointSets {
    public:
        void addelements(int num);	
        int size(int elem);
        int find(int elem);
        void setunion(int a, int b);
    private:
        std::vector<int> vals;

};