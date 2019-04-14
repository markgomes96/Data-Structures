#ifndef BTREE_CPP
#define BTREE_CPP

#include <vector>
#include <set>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>

#include "btree.h"

using namespace std;

BTree::BTree()
{ }

void BTree::writeHeader (char *filename)
{
    //
}

void BTree::insert (keyType key)
{
    // start at 1st node
    // if 1st node is leaf then check current size
    int index = root.child[0];
    BTNode tmp;
    tmp = getNode(index);

    treeFile.seekg(index, ios::cur);     // put in get node function
    treeFile.read((BTNode *) &tmp, sizeof(BTNode));

    if(isLeaf(tmp))
    {
        // insert the node
    }
    else
    {
        // move on to next potential insert point
        
    }
}

void BTree::reset (char *filename)
{
    // clear out btree file, add root node and store info
    strcpy(treeFileName, *filename);
    treeFile = fstream(*filename | ios::in | ios::out | ios::binary);
    treeFile.clear();

    // create root node and assign root address
    rootAddr = treeFile.tellp();
    root.curSize = -1;
    root.child[0] = rootAddr;

    // insert root node
    treeFile.write((BTNode *) &root, sizeof(BTNode));
    rootAddr = treeFile.tellp();
    root.child[0] = rootAddr;

    // insert 1st node
    BTNode tmp;
    tmp.curSize = 0;
    for(int i = 0; i < ORDER; i++)
        tmp.child[i] = -1;
    treeFile.write((BTNode *) &tmp, sizeof(BTNode));

    // record read and write file positions?
}

void BTree::close ()
{
    //
}

void BTree::printTree ()
{
    cout << "----- B-tree of height " << height << "-----" << endl;
    printTree(rootAddr);
}

void BTree::printTree(int recAddr)
{
    if(recAddr != -1)
    {
        BTNode dummy = getNode(recAddr);
        printNode(recAddr);
        for(int i = 0; i <= dummy.currSize; i++)
            printTree(dummy.child[i]);      // recursion
    }
}

void BTree::inorder ()
{
    //
}

void BTree::reverse ()
{
    //
}

int BTree::getHeight ()
{
    //
    return 0;
}

bool BTree::search (string key)
{
    //
    return false;
}

keyType BTree::retrieve (string key)
{
    keyType tmp;
    return tmp;
}

void BTree::totalio () const
{
    //
}

int BTree::countLeaves ()
{
    //
    return 0;
}

int BTree::findAddr (keyType key, BTNode t, int tAddr)
{
    return 0;
}

int BTree::findpAddr(keyType key, BTNode t, int tAddr)
{
    return 0;
}

void BTree::insert (keyType key, int recAddr, int oneAddr, int twoAddr)
{
    //
}

BTNode BTree::getNode (int recAddr)
{
    BTNode tmp;
    treeFile.seekg(recAddr, ios::cur);     // put in get node function
    treeFile.read((BTNode *) &tmp, sizeof(BTNode));
    return tmp;
}

void BTree::printNode(int recAddr)
{
    //
}

void BTree::placeNode (keyType k,int recAddr,int oneAddr,int twoAddr)
{
    //
}

bool BTree::isLeaf (int recAddr)
{
    //
    return false;
}

bool BTree::isLeaf(BTNode t)
{
    bool leaf = true;
    for(int i = 0; i < ORDER; i++)
    {
        if(t.child[i] != -1)  // found link to node
        {
            leaf = false;
        }
    }
    return leaf;
}

int BTree::countLeaves(int recAddr)
{
    //
    return 0;
}

void BTree::adjRoot (keyType rootElem, int oneAddr, int twoAddr)
{
    //
}

void BTree::splitNode (keyType& key,int recAddr,int& oneAddr,int& twoAddr)
{
    //
}

bool BTree::search (string key, BTNode t, int tAddr)
{
    //
    return false;
}

#endif
