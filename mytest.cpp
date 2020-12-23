using namespace std;
#include <iostream>
#include "bookTree.h"

int main(){    
    BookTree aTree;
    aTree.insert("z", "rth", "rthrt");
    aTree.insert("x", "snfg", "agwg");
    aTree.insert("c", "ghsfgh", "sfgnfg"); //left left insert
    aTree.insert("v", "aergg", "bnnf");
    aTree.insert("w", "aergg", "bnnf"); //right right insert
    aTree.insert("b", "dfgnth", "dfgngn"); //right left insert
    aTree.insert("n", "dfgnstn", "dfgndfg");
    aTree.insert("m", "dfgnfg", "fdgndfgn");
    aTree.insert("d", "dfgnstn", "dfgndfg"); //right right insert
    cout << "aTree contains: ";
    aTree.dump();
    cout << endl << endl;
    cout << "inserting a new node, such as \"Henry Ford\" will splay it to the root: ";
    aTree.insert("my life and work", "henry ford", "we have only started on our development of our country we have not as yet with all our talk of wonderful progress done more than scratch the surface the progress has been wonderful enough but when we compare what we have done with what there is to do then our past accomplishments are as nothing");
    //the text is inputted in all lowercase and has no punctuation in the same way that loadTree would convert it
    aTree.dump();
    cout << endl << endl;
    cout << "inserting a few more random nodes... duplicates will not be added: ";
    aTree.insert("b", "dfgnth", "dfgngn"); //duplicate
    aTree.insert("y", "ergestn", "dfegjng"); //new entry
    aTree.insert("m", "dfgnfg", "fdgndfgn"); //duplicate
    aTree.dump();
    cout << endl << endl << "_root is currently " << aTree.getRootKey();
    cout << endl << endl;

    cout << "Frequency of \"we\" in My Life and Work by Henry Ford: " << endl;
    cout << "\t" << aTree.findFrequency("my life and work","we") << endl << endl;
    cout << "Count of search operation for \"we\" in My Life and Work by Henry Ford: " << endl;
    cout << "\t" << aTree.searchCount("my life and work","we") << endl << endl;
    cout << "Height of the node containing \"we\" in My Life and Work by Henry Ford: " << endl;
    cout << "\t" << aTree.getWordHeight("my life and work","we") << endl << endl;
    cout << "Height of word tree for My Life and Work by Henry Ford: " << endl;
    cout << "\t" << aTree.getTextTreeHeight("my life and work") << endl << endl;
    cout << "Dumping the word tree for My Life and Work by Henry Ford:" << endl << endl;
    aTree.dumpTitle("my life and work");
    cout << endl;
    return 0;    
  }