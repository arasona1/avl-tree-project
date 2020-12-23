#include "bNode.h"
BNode::BNode(){}
BNode::BNode(string key, string author, string text){
            _key = key;
            _author = author;
            _left = nullptr;
            _right = nullptr;
            _flag = false;
            _parent == nullptr;
            createTextTree(text);
        }
BNode::~BNode(){
    _key = "";
    _author = "";
    _left = nullptr;
    _right = nullptr;
    _parent = nullptr;
    _flag = false;
    
}

void BNode::createTextTree(string text){
    istringstream iss(text);
    vector<string> tokens;
    copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(tokens));
    for (std::vector<string>::iterator it = tokens.begin() ; it != tokens.end(); ++it){
        _tree.insert(*it);
    }
}

int BNode::findFrequency(string word){ //_tree->find(word)
    Node *temp = _tree.find(word);
    if(temp){
        return(temp->getFrequency()); //finds word and returns count
    }
    return 0;
}

int BNode::searchCount(string word){
    return _tree.searchCount(word); //returns search count of word
}

int BNode::getTextTreeHeight(){
    return _tree.getRootHeight(); //returns root height of bnode
}

int BNode::getNodeHeight(string word){
    return _tree.getNodeHeight(word); //returns node height of word
}