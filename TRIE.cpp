#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

class Node {
    private:
        char leadChar;
        bool isWord;
        Node *rightSibling;
        Node *firstChild;
    public:
        //Constructor
        Node() {    
            leadChar = ' ';
            isWord = false;
            rightSibling = nullptr;
            firstChild = nullptr;
        };
        Node(char value) {
            leadChar = value;
            isWord = false;
            rightSibling = nullptr;
            firstChild = nullptr;
        };
        //Desctructor
        ~Node() {
            delete rightSibling;
            delete firstChild;
        };
        void insert(Node *root, string string); //Insert Function
        int query(Node *root, string qprefix, string forbidden);   //Query Function
        Node *search(Node *root, string qprefix);   //Search Function
        int preorderMatch(Node *root, string prefix, string forbidden);    //Check all nodes under matched prefix
        Node *findChild(Node *root, char c);    //finds the child of a node that matches character

};

//Insert Function for BST
void Node::insert(Node *root, string s) {
    if(s.empty() == true) {
        root->isWord = true;
        return;
    } else {
        char c = s[0];
        string sub = s.substr(1, s.length());   //strip off prefix character
        Node *q = findChild(root, c);   //find the pointer of the child with stripped character
        if(q == nullptr || q == NULL) {
            Node *r = new Node(c);  //If node is empty, create new node here
            //Sort alphabetically
                if(root->firstChild != nullptr && c > root->firstChild->leadChar) {
                    Node *temp = root->firstChild;
                    while (temp->rightSibling != nullptr) {
                            if(temp->rightSibling->leadChar > c) {
                                break;
                            } else {
                                temp = temp->rightSibling;
                            }
                        }
                    r->rightSibling = temp->rightSibling;
                    temp->rightSibling = r;
                } else {
                    r->rightSibling = root->firstChild;
                    root->firstChild = r;
                }
            insert(r, sub); //Recurse down trie untill input string is empty
        } else {
            insert(q, sub); //Recurse down trie untill input string is empty
        }
    }
    return;
}

//
int Node::query(Node *root, string qprefix, string forbidden) {
    Node *q = search(root, qprefix);
    return preorderMatch(q, qprefix, forbidden);
}

//
int Node::preorderMatch(Node *root, string prefix, string forbidden) {
    if(root == NULL || root == nullptr) return 0;
    int count  = 0;
    if(root->isWord == true) {count++;}
    Node *q = root->firstChild;
    while(q != NULL || q != nullptr) {
        bool forbid = false;
        for(int i = 0; i < forbidden.length(); i++) {if(q->leadChar == forbidden[i]) forbid = true;}    //If lead Character is in forbidden string
        if(forbid == false) {
            count = count + preorderMatch(q, prefix+q->leadChar, forbidden);}
        q = q->rightSibling;
    }
    return count;
}

//
Node* Node::search(Node *root, string qprefix) {
    if(qprefix.empty() == true) return root;
    Node *q = findChild(root, qprefix[0]);
    if(q == NULL || q == nullptr) return NULL;
    return search(q, qprefix.substr(1, qprefix.length()));
}

//
Node* Node::findChild(Node *root, char c) {
    Node *q = root->firstChild;
    if(q != nullptr) {
        while(q != nullptr && q->leadChar != c) {q = q->rightSibling;}}
    return q;}

//Main Function
int main() {
    Node *n = new Node(); //Declare new BST
    fstream w("WORD.LST");
    fstream f("inputFile.txt");
    int queryCount = 0;
    string newString;
    //Insert WORD.LST into Trie
    while(w >> newString) {
        if(newString.length() == 5) {
            n->insert(n, newString);
        }
    }
    string prefix, forbidden;
    f >> prefix >> forbidden;
    queryCount = n->query(n, prefix, forbidden);
    cout<<queryCount<<endl;
};
