/*
Ex (seed = 549343)
Which of the following id[] array(s) could be the result of running the weighted quick union
algorithm on a set of 10 items? Check all that apply.

0 1 2 6 2 5 [6] 7 0 9 
4 9 [1] 5 1 1 4 1 4 6 
5 1 3 [1] 3 3 2 3 3 3 
5 7 8 7 9 6 6 [5] 0 9 
3 5 5 6 6 5 5 5 5 5 

Recall that our weighted quick union algorithm uses union by size (number of nodes)
(and not union by height).
*/

#pragma once
#include <iostream>
using namespace std;

const int weightedNodeSize = 10;

class WeightedQuickUnion
{
private:
    int _nodes[weightedNodeSize];
    int _weight[weightedNodeSize];

public:
    WeightedQuickUnion(void) {
        for (int i=0; i<weightedNodeSize; i++) {
            _nodes[i] = i;
            _weight[i] = 1;
        }
    }
    virtual ~WeightedQuickUnion(void) {

    }

    inline int root(int index) {
        if (index < 0 || index >= weightedNodeSize) {
            return -1; // error: out of array range
        }

        while (index != _nodes[index]) {
            index = root(_nodes[index]);
        }

        return index;
    }
    inline void connect(int toIndex, int fromIndex) {

        int toRoot = root(toIndex);
        int fromRoot = root(fromIndex);

        if (toRoot == fromRoot) {
            return;
        }

        const int toRootWeight = _weight[toRoot];
        const int fromRootWeight = _weight[fromRoot];

        if (toRootWeight >= fromRootWeight) {
                // TODO: one-pass compression here
            _nodes[fromRoot] = _nodes[toRoot];
            _weight[toRoot] += fromRootWeight;

            
        } else {
                // TODO: one-pass compression here
             _nodes[toRoot] = _nodes[fromRoot];
             _weight[fromRoot] += toRootWeight;
        }
    }
    inline bool find(int firstNodeIndex, int secondNodeIndex) {
        if ((firstNodeIndex < 0 || firstNodeIndex >= weightedNodeSize) ||
            (secondNodeIndex < 0 || secondNodeIndex >= weightedNodeSize)) {
                return false; 
        }
        return root(firstNodeIndex) == root(secondNodeIndex);
    }
    inline void print() {
        // print index
        std::cout << "i       ";
        for (int i=0; i<weightedNodeSize; i++) {
            std::cout << i << ' ';
        }
        std::cout << "\r\n";

        // print nodes
        std::cout << "nodes[] ";
        for (int i=0; i<weightedNodeSize; i++) {
            std::cout << _nodes[i] << ' ';
        }
        std::cout << "\r\n";
    }

};

