#ifndef BTREE_CPP
#define BTREE_CPP

#include <vector>
#include <set>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <fstream>

#include "btree.h"

using namespace std;

BTree::BTree()
{ }

void BTree::insert (keyType key)
{
    // start at 1st node
    // if 1st node is leaf then check current size
    int pindex = rootAddr;      // parent node address
    int index = root.child[0];  // current node address
    BTNode tmp;

loop1:
    tmp = getNode(index);

    if(isLeaf(tmp))   // check for leaf
    {
        cout << "Now inserting " << key;
        if(tmp.currSize < ORDER-1)    // check for space in node
        {
            // insert key into node
            tmp.contents[tmp.currSize] = key;
            tmp.currSize++;

            // sort node
            tmp = sortNode(tmp);

            // place node in btree file
            treeFile.seekg(index, ios::beg);
            treeFile.write((char *) &tmp, sizeof(BTNode));
        }
        else    // split node
        {
            cout << "[SPLIT]" << endl;
            splitNode(key, tmp, index, pindex);
        }
    }
    else    // move to next child node
    {
        pindex = index;
        index = findChildAddr(key, tmp);
        goto loop1;
    }
}

void BTree::reset (char *filename)
{
    // clear out btree file, add root node and store info
    strcpy(treeFileName, filename);
    treeFile = fstream(filename, ios::in | ios::out | ios::binary);
    treeFile.clear();

    // create root node and assign root address
    rootAddr = treeFile.tellp();
    root.currSize = -1;
    root.child[0] = rootAddr;

    // insert root node
    treeFile.write((char *) &root, sizeof(BTNode));
    root.child[0] = treeFile.tellp();

    // insert 1st node
    BTNode tmp;
    tmp.currSize = 0;
    for(int i = 0; i < ORDER; i++)
        tmp.child[i] = -1;
    treeFile.write((char *) &tmp, sizeof(BTNode));
}

void BTree::printTree ()
{
    cout << "----- B-tree of height " << height << "-----" << endl;
    printTree(root.child[0]);
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

int BTree::getHeight ()
{
    //
    return 0;
}

keyType BTree::retrieve (string key)
{
    keyType tmp;
    return tmp;
}

BTNode BTree::sortNode(BTNode in)
{
    BTNode out;
    out.currSize = in.currSize;
    for(int i = 0; i < ORDER; i++)
        out.child[i] = -1;
 
    string test = "-1";
    char* test_p = &test[0];
    int mi = 0;
    for(int i = 0; i < in.currSize; i++)
    {
        for(int j = 0; j < in.currSize; j++)
        {
            // ignore sorted values
            if(strcmp(in.contents[j].getUPC().c_str(), test.c_str()) != 0)
            {
                // find min value
                if(in.contents[j] < in.contents[mi] || strcmp(in.contents[mi].getUPC().c_str(), test.c_str()) == 0)
                {
                    mi = j;
                }
            }
        }

        out.contents[i] = in.contents[mi];
        // mark node as sorted
        keyType tmp = Album(test_p, test_p, test_p);
        in.contents[mi] = tmp;
        mi = 0;
    }

    return out;
}

int BTree::findChildAddr (keyType key, BTNode t)
{
    int index = -1;
    for(int i = 0; i < t.currSize; i++)
    {
        if(key < t.contents[i])
        {
            index = i;
            break;
        }
    }

    if(index == -1)
    {
        index = t.currSize;
    }

    return t.child[index];
}

int BTree::findAddr (keyType key, BTNode t, int tAddr)
{
    return 0;
}

int BTree::findpAddr(keyType key, BTNode t, int tAddr)
{
    return 0;
}

BTNode BTree::getNode (int recAddr)
{
    BTNode tmp;
    treeFile.seekg(recAddr, ios::beg);     // put in get node function
    treeFile.read((char *) &tmp, sizeof(BTNode));
    return tmp;
}

void BTree::printNode(int recAddr)
{
    BTNode tmp = getNode(recAddr);
    cout << "    *** node of size " << tmp.currSize << " ***" << endl;
    for(int i = 0; i < tmp.currSize; i++)
    {
        cout << tmp.contents[i];
    }
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

void BTree::splitNode(keyType key, BTNode t, int index, int pindex)
{
    // find middle key and sort node
    keyType mid, tmp1, tmp2;
    tmp1 = key;
    for(int i = 0; i < ORDER-1; i++)
    {
        if(tmp1 < t.contents[i])   // place key into node
        {
            tmp2 = t.contents[i];
            t.contents[i] = tmp1;
            tmp1 = tmp2;
        }
    }
    mid = t.contents[ORDER/2];
    // move keys down
    for(int i = ORDER/2; i < ORDER-2; i++)
    {
        t.contents[i] = t.contents[i+1];
    }
    t.contents[ORDER-2] = tmp1;

    // *** check for norm-split or root-split
    if(pindex != rootAddr)   // check parent is not root
    {
        // place node in btree file
        treeFile.clear();
        treeFile.seekp(index, ios::beg);
        treeFile.write((char *) &t, sizeof(BTNode));

        // try to insert mid into parent node
        //insert(mid, pindex, index, -1);
    }
    else    // handle parent is root
    {
        // create 2 new child nodes
        int ch1addr, ch2addr;
        BTNode child1, child2;
        child1.currSize = 2;
        child2.currSize = 2;
        for(int i = 0; i < ORDER; i++)
            child1.child[i] = -1;
        for(int i = 0; i < ORDER; i++)
            child2.child[i] = -1;
        for(int i = 0; i < ORDER/2; i++)
            child1.contents[i] = t.contents[i];
        for(int i = ORDER/2; i < ORDER-1; i++)
            child2.contents[i-(ORDER/2)] = t.contents[i];

        treeFile.clear();
        treeFile.seekp(0, ios::end);
        ch1addr = treeFile.tellp();
        treeFile.write((char *) &child1, sizeof(BTNode));
        treeFile.clear();
        treeFile.seekp(0, ios::end);
        ch2addr = treeFile.tellp();
        treeFile.write((char *) &child2, sizeof(BTNode));

        // place mid in current node / parent of 2 childs
        BTNode parent;
        parent.currSize = 1;
        for(int i = 0; i < ORDER; i++)
            parent.child[i] = -1;
        parent.contents[0] = mid;
        parent.child[0] = ch1addr;
        parent.child[1] = ch2addr;

        treeFile.clear();
        treeFile.seekp(index, ios::beg);
        treeFile.write((char *) &parent, sizeof(BTNode));
    }
}

void BTree::leafSplit(keyType key, BTNode t, int index, int pindex)
{
    // if enough space -> place key with child adresses
    
    // if secondary split detected -> recursive call back to splitNode
}

void BTree::rootSplit()
{
    int ch1addr, ch2addr;
    BTNode child1, child2;
    child1.currSize = 2;
    child2.currSize = 2;
    for(int i = 0; i < ORDER; i++)
        child1.child[i] = -1;
    for(int i = 0; i < ORDER; i++)
        child2.child[i] = -1;
    for(int i = 0; i < ORDER/2; i++)
        child1.contents[i] = t.contents[i];
    for(int i = ORDER/2; i < ORDER-1; i++)
        child2.contents[i-(ORDER/2)] = t.contents[i];

}

#endif
