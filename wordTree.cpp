#include "wordTree.h"

WordTree::~WordTree(){ //done
    clearTree(_root);
}

void WordTree::updateHeight(Node *aNode) { //done
   if(hasChild(aNode)){ //if node exists and has at least one child
       aNode->_height = (getBiggerChild(aNode)->_height) + 1; //set its height to one more than its child's height
   }
   else if(aNode){ //if the node exists but has no children
       aNode->_height = 0; //set its height to zero
   }    
}

void WordTree::clearTree(Node* aNode){ //done
    if(aNode == nullptr){
        return;
    }
    clearTree(aNode -> _left); //recursively calls left node
    clearTree(aNode -> _right); //recursively calls right node
    
    delete aNode;
}

void WordTree::inOrder(Node* aNode, std::ostream& ostr){ //done
    if (aNode != nullptr){
        ostr << "[";
        inOrder(aNode->_left, ostr);
        ostr << aNode->_value << ":" << aNode->_count << ":" << aNode->_height;
        inOrder(aNode->_right, ostr);
        ostr << "]";
    }
}

Node* WordTree::find(Node* aNode, const string& element){ //done
    if(aNode == nullptr){
        return nullptr;         //first case, if tree is empty
    }
    if(aNode->_value == element){ // value matches, return node
        return aNode; 
    }
    else if(element < aNode->_value){
        if(aNode->_left){ //left node exists, call recursively
            return find(aNode->_left, element);
        }
        else{ //left node doesnt exist
            return nullptr;
        }
    }
    else{
        if(aNode->_right){ //right node exists, call recursively
            return find(aNode->_right, element);
        }
        else{ // right node doesnt exist
            return nullptr;
        }
    }
    return nullptr;
}

Node* WordTree::find(const string& element){
    return find(_root, element);
}

Node* WordTree::leftRotation(Node* aNode){
    Node *g = aNode -> _parent;
    Node *p = aNode;
    Node *pLeft = aNode -> _left;
    if(g == _root){ //if its root, set root to grandparent
        _root = p;
    }
    else{
        Node *gg = g -> _parent; //if its not root, set g's parent to great grandparent
        p -> _parent = gg;
        if(gg -> _left == g){ //figure out which side of gg points to g
            gg -> _left = p;
            _root -> _parent = nullptr;
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
    
    updateHeight(p);
    updateHeight(g);
    return aNode;
}

Node* WordTree::rightRotation(Node* aNode){
    Node *g = aNode -> _parent;
    Node *p = aNode;
    Node *pRight = aNode -> _right;
    if(g == _root){ //if its root, set root to grandparent
        _root = p;
        _root -> _parent = nullptr;
    }
    else{
        Node *gg = g -> _parent; //if its not root, set g's parent to great grandparent
        p -> _parent = gg;
        if(gg -> _right == g){
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

    updateHeight(p);
    updateHeight(g);
    return aNode;
}

int WordTree::checkBalance(Node* aNode){
    if(hasChild(aNode)){ //if node exists and has a child
       return(getLeftHeight(aNode)-getRightHeight(aNode)); //returns difference
    }
   else{ //if node DNE or has no children
       return 0;
    }
}

Node* WordTree::reBalance(Node* aNode){
    //if its here, the node has been through checkbalance, therefore it exists, as at least one child, and has a difference in child heights > 1
    Node *bigP = getBiggerChild(aNode);
    //bigP would have to have at least one child to cause a tree imbalance in the first place, considering it is the greater child of aNode
    Node* bigC = getBiggerChild(bigP);
    
    if(bigP == aNode->_right){ //either RR or RL
        if(bigC == bigP->_right){ //RR
            return leftRotation(bigP); //RR
        }
        else if(bigC == bigP->_left){ //RL
            bigP = rightRotation(bigC); //RL
            return leftRotation(bigP);
        }
        else{
            cout << "rb error 1" << endl;
            return nullptr;
        }
    }
    else if(bigP == aNode->_left){ //either RR or RL
        if(bigC == bigP->_left){ //LL
            return rightRotation(bigP); //LL
        }
        else if(bigC == bigP->_right){ //LR

            bigP = leftRotation(bigC); //LR
            return rightRotation(bigP);
        }
        else{
            cout << "error 2" << endl;
            return nullptr;
        }
    }
    cout << "rb error 3" << endl;
    return nullptr;
}

void WordTree::insert(const string& element){ //done
    if(!_root){
        _root = new Node(element); //if there is no root, insert set node as _root
        _root -> _count = 1;
    }
    else{
        insert(element, _root); //if there is a root, insert node a c c o r d i n g l y
    }
}
Node* WordTree::insert(const string& element, Node*& aNode){
    if(aNode->_value == element){ //increments counter if already in tree
        aNode->_count++;
        return aNode;
    }
    else if(aNode->_value > element){ //element is to the left of current node
        if(aNode->_left){
            insert(element, aNode -> _left); //traverses left
        }
        else{
            aNode -> _left = new Node(element); //inserts node
            aNode -> _left -> _parent = aNode;
            aNode -> _left -> _count++;
        }
        updateHeight(aNode);
    }
    else{ //element is to the right of current node
        if(aNode -> _right){
            insert(element, aNode -> _right); //traverses right
        }
        else{
            aNode -> _right = new Node(element); //inserts node
            aNode -> _right -> _parent = aNode;
            aNode -> _right -> _count++;
        }
        updateHeight(aNode);
    }
    if(abs(checkBalance(aNode)) > 1){ //if the nodes imbalance is greater than one, call rebalance
        aNode = reBalance(aNode);
    }
    updateHeight(aNode);
    return aNode;
}

void WordTree::dump(std::ostream& ostr){ //good
    inOrder(_root, ostr);
}

int WordTree::searchCount(string word){
    int counter = 0; //sets counter
    return searchCountHelp(_root, word, counter);
}

int WordTree::searchCountHelp(Node* aNode, string word, int counter){ //done
    if(aNode == nullptr){
        return counter;         //first case, if tree is empty
    }
    if(aNode -> getValue() == word){
        return(counter);          //second case, if _root is the node
    }
    else if(word < aNode -> getValue()){
        if(aNode -> _left){
            counter++; //increments counter if theres more to go
            return searchCountHelp(aNode -> _left, word, counter); //traverses recursively
        }
        else{
            return counter;
        }
    }
    else{
        if(aNode -> _right){
            counter++; //increments counter if theres more to go
            return searchCountHelp(aNode -> _right, word, counter); //traverses recursively
        }
        else{
            return counter;
        }
    }
    return -1;
}

int WordTree::getRootHeight(){ //good
    return(_root -> _height);
}

int WordTree::getNodeHeight(string word){
    Node *curr = find(word);
    if(curr != nullptr){ //if word exists in tree
        return(curr->_height); //returns height of word
    }
    else{
        return -1;
    }
}

int WordTree::getNodeHeightHelp(Node* aNode, string word){
    /***********************************
     *      To be implemented
     * Note: to avoid warnings, a
     * fictional return value is added,
     * your implementaion should return
     * a correct value.
     * ********************************/
    return 0;
}

int WordTree::getLeftHeight(Node* aNode){
    if(aNode){ 
        if(aNode->_left){
            return aNode->_left->_height; //if node and nodes left child exist, return left childs height
        }
        else{
            return -1;
        }
    }
    else{
        cout << "GLF error 2" << endl;
    }
    return -1;
}

int WordTree::getRightHeight(Node* aNode){
    if(aNode){
        if(aNode->_right){
            return aNode->_right->_height; //if node and nodes right child exist, return right childs height
        }
        else{
            return -1;
        }
    }
    else{
        cout << "GLF error 2" << endl;
    }
    return -1;
}

Node* WordTree::getBiggerChild(Node *aNode){ //only call if hasChild(aNode) == true
    if(aNode->_left and aNode->_right){ //if both children exist
        if(getLeftHeight(aNode) > getRightHeight(aNode)){ //left node is bigger
            return aNode->_left;
        }
        else if(getLeftHeight(aNode) < getRightHeight(aNode)){ //right node is bigger
            return aNode->_right;
        }
        else{ //childrens heights are equal
            return aNode->_right;
        }
    }
    else if(!(aNode->_left)){ //left doesnt exist CHECK HEIGHTS INSTEAD OF EXISTENCE
        return aNode->_right;
    }
    else{ //only left exists
        return aNode->_left;
    }

}

bool WordTree::hasChild(Node *aNode){ //checks if node exists and has at least one child
    if((aNode) and (aNode->_right or aNode->_left)){
        return true;
    }
    return false;
}