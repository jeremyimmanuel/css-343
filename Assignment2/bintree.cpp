#include "bintree.h"

using namespace std;

BinTree::BinTree()
{
    root = nullptr;
}

BinTree::BinTree(const BinTree&)
{}

BinTree::~BinTree()
{}

bool getHeight()
{

}

bool BinTree::insert(NodeData* nd)
{
    Node* ptr = new Node();
    ptr->data = nd;
    ptr->left = nullptr;
    ptr->right = nullptr;

    delete nd;

    Node* curr = root;
    return insertHelper(curr, ptr)
}

bool BinTree::insertHelper(Node* curr, Node* nd)
{
    //base case
    if(curr == nullptr)
    {
        curr = nd;
        return true;
    }

    //recursive case
    if(curr->data < nd) //go left
        return insertHelper(curr->left, nd);
        
    if(curr->data > nd) //go right
        return insertHelper(curr->right, nd);   
}

bool BinTree::retrieve(const NodeData& key, NodeData*& ans) const
{
    retrieveHelper(root, key, ans);

    return ans != nullptr ? true : false;
}

void BinTree::retrieveHelper(Node* curr, const NodeData& key, NodeData*& ans) const
{
    if(curr == nullptr)
        ans = nullptr;
    else if(key == curr->data)
        ans = curr;
    else if(key < curr->data) //go left
        ans = retrieveHelper(curr->left, key, ans);
    else if(key > curr->data) //go right
        ans = retrieveHelper(curr->right, key, ans);
}
