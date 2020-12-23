#ifndef BNODE_H
#define BNODE_H
#include <string>
#include <iostream>
#include <fstream>
#include <streambuf>
#include <algorithm>
#include <iterator>
#include <vector>
#include "wordTree.h"
using namespace std;
class Grader;//for grading purposes
class BookTree;
class BNode{
    friend class BookTree;
    public:
        friend class Grader;//for grading purposes
        BNode();
        BNode(string key, string author, string text);
        ~BNode();
        int findFrequency(string word);//returns number of occurrences of the word
        int searchCount(string word);//returns the number of operations for a search in AVL tree
        int getTextTreeHeight();//returns the height of _tree
        int getNodeHeight(string word);//returns height of a node in _tree
    private:
        void createTextTree(string text);
        string _key;//stores the title of the book
        string _author;//stores the author's name
        WordTree _tree;//the AVL tree that stores the words from text
        BNode* _left;
        BNode* _right;
        BNode* _parent;
        bool _flag;
};

#endif