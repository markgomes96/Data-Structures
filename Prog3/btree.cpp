#ifndef BTREE_CPP
#define BTREE_CPP

#include <vector>
#include <set>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
using namespace std;

class Album;
const int ORDER = 5;
typedef Album keyType;
typedef int IndexArray[ORDER];
typedef keyType ValueArray[ORDER-1];

struct BTNode
{
    int currSize;
    ValueArray contents;
    IndexArray child;
};

struct Pair
{
    Album element;
    int loffset;
    int roffset;
    friend bool operator < (const Pair& p1, const Pair& p2)
        { return (p1.element < p2.element); }
};

BTree::BTree()
{ }

void BTree::writeHeader (char *filename)
{
    //
}

void BTree::insert (keyType key)
{
    //
}

void BTree::reset (char *filename)
{
    //
}

void BTree::close ()
{
    //
}

void BTree::printTree ()
{
    //
}

void BTree::inorder ()
{
    //
}

void BTree::reverse ()
{
    //
}

void BTree::getHeight ()
{
    //
}

bool BTree::search ()
{
    //
}

keyType BTree::retrieve (string key)
{
    //
}

void BTree::totalio () const
{
    //
}

void BTree::countLeaves ()
{
    //
}

#endif
