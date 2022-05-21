#include <iostream>
#include <fstream>
#include <string>

//Sources:

using namespace std;
int stringCount = 0;

class Node
{
    private:
        char leadChar;
        bool IsWord;
        Node *rightSibling;
        Node *firstChild;
    public:
        void insert(Node *p, string s);
        void preorderMatch(Node *p, string prefix, string forbidden);
        void Query(Node *p, string qprefix, string forbidden);
        Node(char c);
        Node *search(Node *p, string qprefix);
        Node *findChild(Node *p, char c);
};

Node::Node(char c)
{
    leadChar = c;
    IsWord = false;
    rightSibling = nullptr;
    firstChild = nullptr;
}
void Node::insert(Node *p, string s)
{ // node's children are unordered in the linked list ...not sorted in this case
//assumes the character at p is already matched.
    if (s.empty()) 
    {
        p->IsWord = true;
        return;
    }
    char c = s[0];
    string ss = s.substr(1,s.length());
    Node *q = findChild(p,c);
    if (q == nullptr) 
    {
        Node *r = new Node(c);
        r->rightSibling = p->firstChild;  //insert as leftmost child
        p->firstChild = r;
        insert(r, ss);
    } else {
        insert(q, ss);
    }
}
void Node::Query(Node *p, string qprefix, string forbidden) 
{
    Node *q = search(p,qprefix);
    preorderMatch(q, qprefix, forbidden);
}
Node* Node::search(Node *p, string qprefix)
{
    if (qprefix.length() == 0) 
        return p;
    Node *q = findChild(p, qprefix[0]);
    if (q == nullptr) 
        return nullptr;
    return search(q, qprefix.substr(1,qprefix.length()));
}
void Node::preorderMatch(Node *p, string prefix, string forbidden)
{
    if(p == nullptr) return;
    if (p->IsWord) stringCount++;
    Node *q = p->firstChild;
    while(q != nullptr) 
    {
        if(forbidden.find(q->leadChar) == string::npos) preorderMatch(q, prefix + q->leadChar, forbidden);
        q = q->rightSibling;
    }
}

Node* Node::findChild(Node *p, char c)
{
    Node *q = p->firstChild;
    while (q != nullptr && q->leadChar != c) q = q->rightSibling;
    return q;
}


int main()
{
    Node *n = new Node('\0');
    fstream f("WORD.LST");
    string newString;
    while(f >> newString) {
        if(newString.length() == 5) n->insert(n, newString);
    }
    fstream g("inputFile.txt");
    string prefix, forbidden;
    g >> prefix >> forbidden;
    n->Query(n, prefix, forbidden);
    cout<<stringCount<<endl;
}