#include "bookTree.h"
BookTree::BookTree(){_root=nullptr;}

BookTree::~BookTree(){
	clear(_root);
}

BNode* BookTree::makeSplay(BNode* root, string key){
    BNode *c = root;
    BNode *p = nullptr;
    BNode *g = nullptr;
    string pKey = "";
    
    if((!(c->_parent)) or _root == c){ //if childs parent DNE or if child is root
        return c; //return child bc it is now root
    }
    p = c->_parent; //if parent exists, set parent

    if(p->_parent == nullptr){ //there is only one level after root
        if(p->_left == c){
            return rightRotate(c);
        }
        if(p->_right == c){
            return leftRotate(c);
        }
    }
    
    g = p->_parent;
    if(g->_right){ //if grandparents right exists
        if(g->_right == p){ //either RR or RL
            if(p->_right){
                if(p->_right == c){ //RR
                    p = leftRotate(p);
                    c = leftRotate(c);
                    return makeSplay(c, key);
                }
            }
            if(p->_left){
                if(p->_left == c){//RL
                    c = rightRotate(c);
                    c = leftRotate(c);
                    return makeSplay(c, key);
                }
            }
        }
    }
    if(g->_left){ //if grandparents right exists
        if(g->_left == p){ //either RR or RL
            if(p->_left){
                if(p->_left == c){ //LL
                    p = rightRotate(p);
                    c = rightRotate(c);
                    return makeSplay(c, key);
                }
            }
            if(p->_right){
                if(p->_right == c){//LR
                    c = leftRotate(c);
                    c = rightRotate(c);
                    return makeSplay(c, key);
                }
            }
        }
    }
    return nullptr;
}
BNode* BookTree::rightRotate(BNode* x){ //x is parent
    BNode *g = x -> _parent;
    BNode *p = x;
    BNode *pRight = x -> _right;
    if(g == _root){ //if its root, set root to grandparent
        _root = p;
    }
    else{
        BNode *gg = g -> _parent; //if its not root, set g's parent to great grandparent
        p -> _parent = gg;
        if(gg -> _right == g){ //figure out which side of gg points to g
            gg -> _right = p;
        }
        else{
            gg -> _left = p;
        }
    }
    g->_parent = p; //assign all lefts, rights, and parents accordingly
    p -> _right = g;
    g -> _left = pRight;
    if(pRight){ //if the original parent had a right node, set its parent as g
        pRight -> _parent = g;
    }
    return x;
}
BNode* BookTree::leftRotate(BNode* x){
    BNode *g = x -> _parent;
    BNode *p = x;
    BNode *pLeft = x -> _left;
    if(g == _root){ //if its root, set root to grandparent
        _root = p;
    }
    else{
        BNode *gg = g -> _parent; //if its not root, set g's parent to great grandparent
        p -> _parent = gg;
        if(gg -> _left == g){ //figure out which side of gg points to g
            gg -> _left = p;
        }
        else{
            gg -> _right = p;
        }
    }
    g->_parent = p; //assign all lefts, rights, and parents accordingly
    p -> _left = g;
    g -> _right = pLeft;
    if(pLeft){ //if the original parent had a left node, set its parent as g
        pLeft -> _parent = g;
    }
    return x;
}

bool BookTree::insert(const string& key, const string& author, const string& text){
    //do insert like in wordtree sorted by key, then splay it so it is _root
    if(!_root){
        _root = new BNode(key, author, text); //if there is no root, insert set node as _root
        _root->_parent = nullptr;
        return true;
    }
    else{
        return insert(key, author, text, _root); //if there is a root, insert node a c c o r d i n g l y
    }
    return false;
}

bool BookTree::insert(const string& key, const string& author, const string& text, BNode*& aNode){
    if(aNode->_key == key){ //returns false if node already exists
        return false;
    }
    else if(aNode->_key > key){ //element is to the left of current node
        if(aNode->_left){
            insert(key, author, text, aNode -> _left); //traverses left
        }
        else{
            aNode -> _left = new BNode(key, author, text); //inserts node
            aNode -> _left -> _parent = aNode;
            _root = makeSplay(aNode->_left, key);
            _root -> _parent = nullptr;
            return true;
        }
    }
    else{ //element is to the right of current node
        if(aNode -> _right){
            insert(key, author, text, aNode -> _right); //traverses right
        }
        else{
            aNode -> _right = new BNode(key, author, text); //inserts node
            aNode -> _right -> _parent = aNode;
            _root = makeSplay(aNode->_right, key);
            _root -> _parent = nullptr;
            return true;
        }
    }
    return true;
}
void BookTree::clear(BNode* root){
	if(root == nullptr){
        return;
    }
    clear(root -> _left);
    clear(root -> _right);
    
    delete root;
}

void BookTree::inorderHelp(BNode* root, bool verbose) const{
     /***********************************
     *      Do not modify
     * ********************************/
    if (root != nullptr){
        if (verbose){
            cout << "(";
            inorderHelp( root->_left, verbose );
            cout << root->_key << ":" << root->_author;
			root->_tree.dump();
            inorderHelp( root->_right, verbose );
            cout << ")";
        }
        else{
            inorderHelp( root->_left, verbose );
            cout << root->_key;
            inorderHelp( root->_right, verbose );
        }
    }
}

void BookTree::dump(bool verbose) const{
     /***********************************
     *      Do not modify
     * ********************************/
    inorderHelp(_root, verbose);
}

BNode* BookTree::findNode(string key){ //helper function so findNode can be used recursively
    return findNode(_root, key);
}

BNode* BookTree::findNode(BNode *aNode, string key){
    if(!aNode){
        return nullptr;         //first case, if tree is empty
    }
    if(aNode->_key == key){ // value matches, return node
        return aNode; 
    }
    else if(key < aNode->_key){
        if(aNode->_left){ //left node exists, call recursively
            return findNode(aNode->_left, key);
        }
    }
    else if(key > aNode->_key){
        if(aNode->_right){
            return findNode(aNode->_right, key);
        }
    }
    return nullptr;
}

void BookTree::dump(){
    dump2(_root);
}
void BookTree::dump2(BNode* aNode){
    if (aNode != nullptr){
        cout << "[";
        dump2(aNode->_left);
        cout << aNode->_key;
        //cout << aNode->_key << ":" << aNode->_author;
        dump2(aNode->_right);
        cout << "]";
    }
}

int BookTree::findFrequency(string title, string word){
    BNode *temp = findNode(title);
    if(temp){ //if the bnode exists, splay it
	    _root = makeSplay(temp, title);
        return _root->findFrequency(word); //access word frequency of the node
    }
    return 0;
}

void BookTree::dumpTitle(string title){
	BNode *temp = findNode(title);
    if(temp){ //if the bnode exists, splay it
	    _root = makeSplay(temp, title);
        return _root->_tree.dump(); //the wordtree
    }
}

int BookTree::searchCount(string title, string word){
	BNode *temp = findNode(title);
    if(temp){ //if the bnode exists, splay it
	    _root = makeSplay(temp, title);
        return _root->searchCount(word); //access search count of the node
    }
    return 0;
}

int BookTree::getTextTreeHeight(string title){
	BNode *temp = findNode(title);
    if(temp){ //if the bnode exists, splay it
	    _root = makeSplay(temp, title);
        return _root->getTextTreeHeight(); //access tree height of the node
    }
    return -1;
}
int BookTree::getWordHeight(string title, string word){
	BNode *temp = findNode(title);
    if(temp){ //if the bnode exists, splay it
	    _root = makeSplay(temp, title);
        return _root->getNodeHeight(word); //access node height of the node
    }
    return -1;
}

string BookTree::getRootKey(){
     /***********************************
     *      Do not modify
     * ********************************/
	return _root->_key;
}

void BookTree::loadData(string dataFile){
     /***********************************
     *      This function is implemented
     *      to help you. You should't need
     *      to modify it.
     * ********************************/
	//read the entire file at once
	std::ifstream t(dataFile);
	std::stringstream buffer;
	buffer << t.rdbuf();
	//time to parse the information
	string titleDelimiter = "<==>";
	string itemsDeleimiter = "<=>";
	string s = buffer.str();
	size_t pos = 0;
	string token;
	while ((pos = s.find(titleDelimiter)) != string::npos) {
		token = s.substr(0, pos);//token is complete data for one title
		//get the title
		int tempPos = token.find(itemsDeleimiter);
		string title = token.substr(0,tempPos);
		//convert title to lower case
		std::transform (title.begin(), title.end(), title.begin(), ::tolower);
		token.erase(0, tempPos + itemsDeleimiter.length()+1);
		//get the author
		tempPos = token.find(itemsDeleimiter);
		string author = token.substr(0,tempPos);
		//convert author to lower case
		std::transform (author.begin(), author.end(), author.begin(), ::tolower);
		token.erase(0, tempPos + itemsDeleimiter.length()+1);
		//get the text
		string text = token.substr(0,token.length() - 1);//remove last newline
		//clean up the text, remove all non-alphanumeric characters
          for( std::string::iterator iter = text.begin() ; iter != text.end() ; ){
               if( !std::isalnum(*iter) && *iter != ' ') 
                    iter = text.erase(iter) ;
               else 
                    ++iter ; // not erased, increment iterator
          }
		//convert text to lower case
		std::transform (text.begin(), text.end(), text.begin(), ::tolower);
		insert(title,author,text);

		//move to info for the next title
		s.erase(0, pos + titleDelimiter.length()+1);
	}
}