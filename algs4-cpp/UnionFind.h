#pragma once
#include <iostream>
using namespace std;

const int nodeSize = 10;


class UnionFind {
private:
    int _nodes[nodeSize];

public:
    UnionFind(void) {
        for (int i=0; i<nodeSize; i++) {
            _nodes[i] = i;
        }
    }
    virtual ~UnionFind(void) { }

    inline void connect(int toIndex, int fromIndex) {

        bool connectReady = false;
        if (fromIndex >= 0 && fromIndex < nodeSize) {
            if (toIndex >=0 && toIndex < nodeSize) {
                connectReady = true;
            }
        }
        if (!connectReady) {
            return;
        }

        int currentValue = _nodes[toIndex];
        int targetValue = _nodes[fromIndex];

        _nodes[fromIndex] = targetValue;

        for (int i=0; i<nodeSize; i++) {
            if (_nodes[i] == currentValue) {
                _nodes[i] = targetValue;
            }
        }
    }
    inline bool find(int firstNodeIndex, int secondNodeIndex) {
        return _nodes[firstNodeIndex] == _nodes[secondNodeIndex];
    }
    inline void print() {
        // print index
        std::cout << "i       ";
        for (int i=0; i<nodeSize; i++) {
            std::cout << i << ' ';
        }
        std::cout << "\r\n";

        // print nodes
        std::cout << "nodes[] ";
        for (int i=0; i<nodeSize; i++) {
            std::cout << _nodes[i] << ' ';
        }
        std::cout << "\r\n";
    }

};

