#include <vector>
#include <set>
#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include "album.h"
using namespace std;

#ifndef BTREE_H
#define BTREE_H

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
           { return (p1.element < p2.element);  }
};

class BTree
{
 public:
	BTree();
	void insert (keyType key);
	void reset (char * filename);
	void printTree();
	int getHeight();

 private:
	BTNode root;
    int rootAddr;
	char treeFileName[80];
	fstream treeFile;
	int height;
	void printTree (int rootAddr);
	int read;
	int write;

    int getHeight(int index);
    BTNode sortNode(BTNode in);
    int findChildAddr (keyType key, BTNode t);
	int findAddr (keyType key, BTNode t, int tAddr);
	int findpAddr(keyType key, BTNode t, int tAddr);
    BTNode getNode (int recAddr);
	void printNode(int recAddr);
	bool isLeaf(BTNode t);
    void splitNode(keyType key, BTNode t, int index, int pindex);
    void leafSplit(BTNode t, keyType mid, int index, int pindex);
    void rootSplit(BTNode t, keyType mid, int index);
    void insert (keyType key, int index, int ch1addr, int ch2addr);
};

#endif
