#include <string>
#include <iostream>
#include <sstream>
using namespace std;
class Grader;//for grading purposes
class Node {//stores a word from the text
    public:
    friend class Grader;//for grading purposes
    friend class WordTree;
    Node(const string& v) : _value(v), 
        _left(nullptr), _right(nullptr), _height(0), _count(0) { }
    void printValue(){
        if (this != nullptr) cout << _value << endl;
        else cout << "NULL" << endl;
    }
    int getFrequency(){return _count;}//returns number of occurrences of the word
    int getHeight(){return _height;}
    string getValue(){return _value;}
    private:
    string  _value;//the word in this node
    Node*   _left;
    Node*   _right;
    Node*   _parent;
    int     _height;
    int     _count;//stores number of occurrences for the word at this node
};
class WordTree{
    public:
    friend class Grader;//for grading purposes
    WordTree():_root(nullptr){};
    ~WordTree();
    void insert(const string& element);//insert, rebalance, update heights
    Node* find(const string& element);
    void dump(std::ostream& ostr = std::cout);
    int searchCount(string word);//returns the number of operations for a search
    int getRootHeight();//returns height of tree
    int getNodeHeight(string word);//returns height of a node with key value word
    /****************************************************************
     * your public member functions start here
     * *************************************************************/
    
    /****************************************************************
     * your public member functions end here
     * *************************************************************/
    private:
    Node* _root;
    Node* insert(const string& element, Node*& aNode);//insert helper function
    void inOrder(Node* aNode, std::ostream& ostr);;//inOrder helper
    Node* find(Node* aNode, const string& element);//find helper
    void clearTree(Node* aNode);//helper called by destructor
    void updateHeight(Node *aNode);
    Node* leftRotation(Node* aNode);
    Node* rightRotation(Node* aNode);
    int checkBalance(Node* aNode);
    Node* reBalance(Node* aNode);
    int searchCountHelp(Node* aNode, string word, int counter);
    int getNodeHeightHelp(Node* aNode, string word);
    /****************************************************************
     * your private member functions start here
     * *************************************************************/
    int getLeftHeight(Node *aNode);
    int getRightHeight(Node *aNode);
    Node* getBiggerChild(Node *aNode);
    bool hasChild(Node *aNode);
    /****************************************************************
     * your private member functions end here
     * *************************************************************/
};