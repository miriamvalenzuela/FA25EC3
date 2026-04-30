//
// Created by Manju Muralidharan on 11/22/25.
//

#ifndef FA25EC3_TREE_H
#define FA25EC3_TREE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

/*
   TEMPLATE TREE CLASS
   Multiple parents may point to the same child.

   Design note (simple + safe approach):
   - Will store every dynamically allocated node pointer in a vector (allNodes).
   - That way, the destructor can delete each node exactly once.
   - Parents store child pointers, so children can appear under multiple parents.
*/

template <typename U>
class Node {
public:
    string id;
    U data;
    vector<Node<U>*> children;

    // Constructor
    Node(const string& nodeID, const U& value) {
        id = nodeID;
        data = value;
        // children starts empty automatically
    }
};

template <typename T>
class Tree {
private:
    Node<T>* root;

    // Stores ALL nodes we dynamically allocate (for safe deletion later)
    vector<Node<T>*> allNodes;

public:
    // Constructor
    Tree() {
        root = nullptr;
    }

    void createRoot(const string& id, const T& value);
    void addNode(const string& parentID, const string& childID, const T& value);
    Node<T>* findNode(const string& id);
    void printAll();

    ~Tree() {
        // Placeholder so the project links successfully.
        // Will implement real cleanup later once nodes are allocated.
    }
};

#endif //FA25EC3_TREE_H