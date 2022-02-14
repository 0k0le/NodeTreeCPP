/*
 * Node example rescursive search
 */

#include <iostream>
#include <cstdlib>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

#define _DEBUG

namespace algo {
    class node {
        private:
            node *_parent;
            vector <node *> _children;
            int _value = 0;

        public:
            node(node *parent, int value);
            node(int value);
            ~node();
            void AddChild(int value);
            vector<node *> *GetChildren();
            node *GetParent();
            bool Search(int value);
    };

    node::node(node *parent, int value) {
        // Copy parent
        _parent = parent;
        _value = value;
    }

    // Constructor for parent node
    node::node(int value) {
        _value = value;
        _parent = nullptr;
    }
    
    node::~node() {
        // Free children data
        for(long unsigned i = 0; i < _children.size(); i++) {
            delete _children[i];
        }

#ifdef _DEBUG
        cout << "Node with a value of " << _value << " has been freed!" << endl;
#endif
    }

    void node::AddChild(int value) {
        // Create new child and add to vector
        _children.push_back(new node(this, value)); 
    }
    
    // Get list of pointers to children
    vector<node *> *node::GetChildren() { return &_children; }

    // Get parent node 
    node *node::GetParent() { return _parent; }

    bool node::Search(int value) {
        bool ret = false; 
        
#ifdef _DEBUG
    cout << "Searching node with a value of " << _value << " for " << value << endl;
#endif

        if(value == _value)
            return true;

        for(long unsigned int i = 0; i < _children.size(); i++) {
            if((ret = _children[i]->Search(value)))
                break;
        }

        return ret;
    }
}

int main(int argc, char **argv) {
    if(argc < 2)
        return EXIT_FAILURE;

    int sVal = atoi(argv[1]);

    cout << "Node tree tester" << endl;
   
    algo::node *parent = new algo::node(0);

    // Create 3 children of parent node  
    parent->AddChild(1);
    parent->AddChild(2);
    parent->AddChild(3);

    // Create 2 children of child nodes of parent
    vector<algo::node *> *child = parent->GetChildren();
    (*child)[0]->AddChild(4);
    (*child)[1]->AddChild(5);

    // Another child of child of child...
    child = (*child)[0]->GetChildren();
    (*child)[0]->AddChild(6);

    if(parent->Search(sVal) == true)
        cout << sVal << " Found!" << endl;
    else
        cout << sVal << " Not Found!" << endl;

    delete parent;

    return EXIT_SUCCESS;
}
