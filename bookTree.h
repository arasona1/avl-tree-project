#ifndef BOOKTREE_H
#define BOOKTREE_H
#include "bNode.h"
class Grader;//for grading purposes
class BookTree{
    public:
        friend class Grader;//for grading purposes
        BookTree();
        ~BookTree();
        void dump(bool verbose=false) const;
        void loadData(string dataFile);//reads data from file and insert into data structure
        int findFrequency(string title, string word);//returns number of occurrences of a word in a book
        void dumpTitle(string title);//dumps all nodes in the word tree of a book
        int searchCount(string title, string word);//returns the number of operations for a search in word tree of a book
        int getTextTreeHeight(string title);//returns height of wrod tree for a book
        int getWordHeight(string title, string word);//returns height of a node in word tree of a book
        string getRootKey();//returns the book title at root
        /****************************************************************
        * your public member functions start here
        * *************************************************************/
        void dump();
        void dump2(BNode* aNode);
        bool insert(const string& key, const string& author, const string& text);
        bool insert(const string& key, const string& author, const string& text, BNode*& aNode);
        BNode* findNode(string key);
        BNode* findNode(BNode *aNode, string key);
        /****************************************************************
        * your public member functions end here
        * *************************************************************/
    private:
        BNode* _root;
        BNode* makeSplay(BNode* root, string key);
        BNode* rightRotate(BNode* x);
        BNode* leftRotate(BNode* x);
        void clear(BNode* root);
        void inorderHelp(BNode* root, bool verbose=false) const;
        /****************************************************************
        * your private member functions start here
        * *************************************************************/
        
        /****************************************************************
        * your private member functions end here
        * *************************************************************/
};
#endif