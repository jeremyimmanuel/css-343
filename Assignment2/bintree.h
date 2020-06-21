#ifndef _BIN_TREE_H_
#define _BIN_TREE_H_

#include "nodedata.h"
#include <iostream>

using namespace std;

class BinTree
{
    public:
        BinTree();
        BinTree(const BinTree&);
        ~BinTree();

        BinTree& operator=(const BinTree&);

        bool operator==(const BinTree&) const;
        bool operator!=(const BinTree&) const;
        
        bool retrieve(const NodeData&, NodeData*&) const;
        int getHeight(const NodeData&) const;
        bool insert(NodeData*);
    private:
        struct Node
        {
            NodeData* data;
            Node* left, right;
        }
        Node* root;
        bool insertHelper(Node* curr, Node* nd)
};
#endif