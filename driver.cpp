#include "bookTree.h"
using namespace std;

int main(){
    BookTree aTree;
    aTree.insert("j", "", "");
    aTree.insert("d", "", "");
    aTree.insert("g", "", "");
    aTree.insert("e", "", "");
    aTree.insert("o", "", "");
    aTree.insert("f", "", "");
    aTree.dump();
    return 0;
}