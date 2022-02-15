/*
 * Node example rescursive search
 */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::cerr;

#define _DEBUG

namespace algo {
    class node {
        private:
            node *_parent;
            vector <node *> _children;
            int _value = 0;
            unsigned int _largestHeight = 0;

        public:
            unsigned int height = 0;

            node(node *parent, int value);
            node(int value);
            ~node();
            void AddChild(int value);
            vector<node *> *GetChildren();
            node *GetParent();
            bool Search(int value);
            unsigned int TreeHeight();
    };

    node::node(node *parent, int value) {
        // Copy parent
        _parent = parent;
        _value = value;
        if(_parent != nullptr)
            height = _parent->height + 1;
        _largestHeight = static_cast<unsigned int>(height);
    }

    // Constructor for parent node
    node::node(int value) {
        _value = value;
        _parent = nullptr;
        _largestHeight = height;
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

    // Search for value in tree
    bool node::Search(int value) {
        bool ret = false; 
        
#ifdef _DEBUG
    cout << "Searching node with a value of " << _value << " for " << value << endl;
#endif

        // current node is the value, return
        if(value == _value)
            return true;

        // Go down the list...
        for(long unsigned i = 0; i < _children.size(); i++) {
            if((ret = _children[i]->Search(value))) // Break and return true if value is found
                break;
        }

        return ret;
    }

    unsigned int node::TreeHeight() {
        // Go down the list...
        for(long unsigned i = 0; i < _children.size(); i++) {
            auto ret = _children[i]->TreeHeight();
            if(ret > _largestHeight)
                _largestHeight = ret;
        }

        return _largestHeight;
    }
}

// namespace for working on cstrings...
namespace cstring {
    // Check if string only contains numbers
    bool IsNumber(const char *str) {
        auto len = strlen(str); 
        
        for(decltype(len) i = 0; i < len; i++) {
            if(str[i] < 48 || str[i] > 57)
                return false;
        }

        return true;
    }
}

void usage(char *) __attribute__((noreturn));
void usage(char *arg1) {
    cout << "Usage: " << arg1 << " [SEARCH_VALUE]" << endl;
    exit(EXIT_FAILURE); 
}

int main(int argc, char **argv) {
    cout << "Node Tree Tester!" << endl;
   
    // User input check 
    if(argc < 2 || !cstring::IsNumber(argv[1]))
        usage(argv[0]);

    // Convert user input
    auto sVal = atoi(argv[1]);

    // Create parent node
    auto parent = new algo::node(0);

    // Create 3 children of parent node  
    parent->AddChild(1);
    parent->AddChild(2);
    parent->AddChild(3);

    // Create 2 children of child nodes of parent
    (*(parent->GetChildren()))[0]->AddChild(4);
    (*(parent->GetChildren()))[1]->AddChild(5);

    // Another child of child of child...
    (*(*(parent->GetChildren()))[0]->GetChildren())[0]->AddChild(6);
    (*(*(parent->GetChildren()))[1]->GetChildren())[0]->AddChild(7);

    // You get it...
    (*(*(*(parent->GetChildren()))[1]->GetChildren())[0]->GetChildren())[0]->AddChild(8);
    (*(*(*(parent->GetChildren()))[0]->GetChildren())[0]->GetChildren())[0]->AddChild(9);

    // Ok fine i'll stop
    (*(*(*(*(parent->GetChildren()))[1]->GetChildren())[0]->GetChildren())[0]->GetChildren())[0]->AddChild(10);

    // Start search
    if(parent->Search(sVal) == true)
        cout << sVal << " Found!" << endl;
    else
        cout << sVal << " Not Found!" << endl;

    // Calculate tree height
    cout << "Tree Height: " << parent->TreeHeight() << endl;

    delete parent;

    return EXIT_SUCCESS;
}
